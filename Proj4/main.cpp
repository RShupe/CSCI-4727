///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Main.cpp
//	Description:                    This is the driver for the program
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Friday January 30, 2021
//  MODIFIED FOR PROJECT 4:         Thursday April 22, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <lastlog.h>
#include <thread>
#include <mutex>
#include <queue>
#include "lib/Logger.h"
#include "mob/Knight.h"
#include "mob/Rabbit.h"

//Struct for the message that gets sent across pipes
typedef struct
{
    int from;
    int to;
    int type;
    int damage;
} Message;

void CheckArguments(int argc, char *argv[]);
void LoggerProcess();
void MainProcess();
void KnightProcess(int KnightNums);
void RabbitProcess(int rabbitNums);
void Terminate();

int maxKnightNum = 0;   //The number of knights combatants for side 1;
int maxRabbitNum = 0;   //The number of rabbits combatants for side 2;
Logger logger;          //Logger object for outputting to the console and the log file.

queue<Message> loggerQueue;
queue<Message> mainQueue;
vector<queue<Message>> KnightQueues;
vector<queue<Message>> RabbitQueues;

pthread_mutex_t mutexLogger;
pthread_mutex_t mutexMain;
vector<pthread_mutex_t> mutexKnights;
vector<pthread_mutex_t> mutexRabbits;

string fileName = "";

bool childsRunning = true;
/**
 * Main
 *
 * The main function of the program.
 *
 * @param agc - count of arguments
 * @param argv - the value of the arguments
 */
int main(int argc, char *argv[])
{
    using namespace std;

    srand (time(NULL));
    CheckArguments(argc, argv); //check the arguments

    KnightQueues = vector<queue<Message>>(maxKnightNum);
    RabbitQueues = vector<queue<Message>>(maxRabbitNum);
    mutexKnights = vector<pthread_mutex_t>(maxKnightNum);
    mutexRabbits = vector<pthread_mutex_t>(maxRabbitNum);

    //LOGGER PROCESS
    thread loggerT(LoggerProcess);
    pthread_mutex_init(&mutexLogger, NULL);

    //KNIGHT PROCESS INIT
    thread knightThreads[maxKnightNum];
    for(int i = 0; i < maxKnightNum; i++)
    {
        //send struct as parameter in function
        knightThreads[i] = thread(KnightProcess, i);
        pthread_mutex_init(&mutexKnights[i], NULL);
    }

    //RABBIT PROCESS INIT
    thread rabbitThreads[maxRabbitNum];
    for(int i = 0; i < maxRabbitNum; i++)
    {
        //send struct as parameter in function
        rabbitThreads[i] = thread(RabbitProcess, i);
        pthread_mutex_init(&mutexRabbits[i], NULL);
    }

    ///////////////////////MAIN PROCESS///////////////////////
    pthread_mutex_init(&mutexMain, NULL);
    MainProcess();

    for(int i = 0; i < maxKnightNum; i ++)
    {
        knightThreads[i].join();
    }
    for(int i = 0; i < maxRabbitNum; i ++)
    {
        rabbitThreads[i].join();
    }
    loggerT.join();

    pthread_mutex_destroy(&mutexMain);
    pthread_mutex_destroy(&mutexLogger);

    for(int i = 0; i < maxKnightNum; i++)
    {
        pthread_mutex_destroy(&mutexKnights[i]);
    }
    for(int i = 0; i < maxRabbitNum; i++)
    {
        pthread_mutex_destroy(&mutexRabbits[i]);
    }
    return 0;
    //////////////////////////////////////////////////////////////
}

/**
 * LoggerProcess
 *
 * Method that executes the logger process
 *
 * @param KnightPipes[][2]
 * @param RabbitPipes[][2]
 * @param mainPipe[2]
 */
void LoggerProcess()
{
    Message msg; //message object for displaying
    //logger.Log("This is from the logger thread");
    bool running = true; //make this loop infinite until it gets the kill message
    while(running)
    {
        //continuously check the queue to see if a message has been sent (p4)
        if(!loggerQueue.empty())
        {
            pthread_mutex_lock(&mutexLogger);
            msg = loggerQueue.front();
            loggerQueue.pop();
            pthread_mutex_unlock(&mutexLogger);

            //logger.Log("I have read something");
            if(msg.damage == -5 && msg.type == -5 && msg.from == -5)
            {
                logger.Log("MESSAGE", "Logger Kill switch activated.");
                logger.Log("MESSAGE", "Finishing processing..");
                logger.Log("SUCCESS", "Saving to file name: '" + fileName + "'");
                logger.Log("MESSAGE", "Exiting Simulation...");
                _Exit(0);
            }
            else if(msg.to == -20)
                {
                    //////////FROM STACK EXCHANGE/////////////////////////
                    //Getting current time with milliseconds
                    //Getting current time with milliseconds
                    //https://codereview.stackexchange.com/questions/11921/getting-current-time-with-milliseconds
                    timeval curTime;
                    gettimeofday(&curTime, NULL);
                    int milli = curTime.tv_usec / 1000;

                    char buffer [80];
                    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

                    char currentTime[84] = "";
                    sprintf(currentTime, "%s:%03d", buffer, milli);
                    ///////////////////////////////////////////////////////
                    string out;
                    out += "<";
                    out += currentTime;
                    out += "> ";
                    out += "THE KNIGHT(S) WIN";
                    logger.LogToFile(out);
                }
            else if(msg.to == -30)
                {
                    //////////FROM STACK EXCHANGE/////////////////////////
                    //Getting current time with milliseconds
                    //https://codereview.stackexchange.com/questions/11921/getting-current-time-with-milliseconds
                    timeval curTime;
                    gettimeofday(&curTime, NULL);
                    int milli = curTime.tv_usec / 1000;

                    char buffer [80];
                    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

                    char currentTime[84] = "";
                    sprintf(currentTime, "%s:%03d", buffer, milli);
                    ///////////////////////////////////////////////////////
                    string out;
                    out += "<";
                    out += currentTime;
                    out += "> ";
                    out += "THE RABBIT(S) WIN";
                    logger.LogToFile(out);
                }
            else if (msg.damage == -1)
                {
                    string out;

                    if(msg.from >= maxRabbitNum && msg.type == 0)
                    {
                        //////////FROM STACK EXCHANGE/////////////////////////
                        //https://codereview.stackexchange.com/questions/11921/getting-current-time-with-milliseconds
                        timeval curTime;
                        gettimeofday(&curTime, NULL);
                        int milli = curTime.tv_usec / 1000;

                        char buffer [80];
                        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

                        char currentTime[84] = "";
                        sprintf(currentTime, "%s:%03d", buffer, milli);
                        ///////////////////////////////////////////////////////

                        out += "<";
                        out += currentTime;
                        out += "> ";
                        Knight knight;
                        if(msg.from - maxRabbitNum < 14)
                        {
                            knight.SetName(msg.from - maxRabbitNum);
                        }
                        else
                        {
                            knight.SetName("Knight: " + to_string(msg.from - maxRabbitNum));
                        }
                        out += knight.GetName() + " has fallen!";
                    }
                    else
                    {
                        //////////FROM STACK EXCHANGE/////////////////////////
                        //Getting current time with milliseconds
                        //https://codereview.stackexchange.com/questions/11921/getting-current-time-with-milliseconds
                        timeval curTime;
                        gettimeofday(&curTime, NULL);
                        int milli = curTime.tv_usec / 1000;

                        char buffer [80];
                        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

                        char currentTime[84] = "";
                        sprintf(currentTime, "%s:%03d", buffer, milli);
                        ///////////////////////////////////////////////////////


                        out += "<";
                        out += currentTime;
                        out += "> ";
                        Rabbit rabbit;
                        if(msg.from < 10)
                        {
                            rabbit.SetName(msg.from);
                        }
                        else
                        {
                            rabbit.SetName(to_string(msg.from));
                        }
                        out += rabbit.GetName() + " has fallen!";
                    }
                    logger.LogToFile(out);
                }
            else
                {
                    //Attack is from a rabbit
                    if(msg.from < maxRabbitNum)
                    {
                        //////////FROM STACK EXCHANGE/////////////////////////
                        //Getting current time with milliseconds
                        //https://codereview.stackexchange.com/questions/11921/getting-current-time-with-milliseconds
                        timeval curTime;
                        gettimeofday(&curTime, NULL);
                        int milli = curTime.tv_usec / 1000;

                        char buffer [80];
                        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

                        char currentTime[84] = "";
                        sprintf(currentTime, "%s:%03d", buffer, milli);
                        ///////////////////////////////////////////////////////

                        string out;
                        out += "<";
                        out += currentTime;
                        out += "> ";


                        Rabbit rabbit;
                        if(msg.from < 10)
                        {
                            rabbit.SetName(msg.from);
                        }
                        else
                        {
                            rabbit.SetName(to_string(msg.from));
                        }
                        Knight knight;
                        if(msg.to < 14)
                        {
                            knight.SetName(msg.to);
                        }
                        else
                        {
                            knight.SetName("Knight: " + to_string(msg.to));
                        }

                        out += (rabbit.GetName() + " ");
                        if(msg.type == 0)
                        {
                            out += "throat leaped ";
                        }
                        else if (msg.type == 1)
                        {
                            out += "bit ";
                        }
                        else
                        {
                            out += "flying nibbled ";
                        }

                        out += knight.GetName() + " for " + to_string(msg.damage) + " damage!";
                        logger.LogToFile(out);
                    }
                    else // attack is from a knight
                    {
                        //////////FROM STACK EXCHANGE///////////////////////////
                        //Getting current time with milliseconds
                        //https://codereview.stackexchange.com/questions/11921/getting-current-time-with-milliseconds
                        timeval curTime;
                        gettimeofday(&curTime, NULL);
                        int milli = curTime.tv_usec / 1000;

                        char buffer [80];
                        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

                        char currentTime[84] = "";
                        sprintf(currentTime, "%s:%03d", buffer, milli);
                        ///////////////////////////////////////////////////////

                        Knight knight;
                        if((msg.from - maxRabbitNum) < 14)
                        {
                            knight.SetName(msg.from - maxRabbitNum);
                        }
                        else
                        {
                            knight.SetName("Knight: " + to_string(msg.from));
                        }

                        Rabbit rabbit;

                        if((msg.from - maxRabbitNum) < 10)
                        {
                            rabbit.SetName(msg.to);
                        }
                        else
                        {
                            rabbit.SetName(to_string(msg.to));
                        }

                        string out;
                        out += "<";
                        out += currentTime;
                        out += "> ";
                        out += (knight.GetName() + " ");

                        if(msg.type == 0)
                        {
                            out += "thrusted ";
                        }
                        else if (msg.type == 1)
                        {
                            out += "stabbed ";
                        }
                        else
                        {
                            out += "cleaved ";
                        }

                        out += rabbit.GetName() + " for " + to_string(msg.damage) + " damage!";
                        logger.LogToFile(out);
                    }
                }
        }
    }
}

/**
 * KnightProcess
 *
 * Method that executes the Knight process
 *
 * @param KnightPipe[2]
 * @param RabbitPipes[][2]
 * @param mainPipe[2]
 * @param loggerPipe[2]
 * @param knightNum
 */
void KnightProcess(int knightNum)
{
    //logger.Log("This is the Knight Thread " + to_string(knightNum));
    srand(time(NULL) ^ getpid());
    Message msg; //msg object to hold a message
    Knight knight; //knight object for obvious reasons

    int currentRabbit = 0; //the current rabbit the knight is attacking
    while(knight.GetHealth() > 0 || currentRabbit > maxRabbitNum)
    {
        sleep(.2);
        if(!childsRunning){
            return;
        }
        //RECEIVE ATTACK
        //if there is something in the queue (p4)
        //if(read(KnightPipe[0], &msg, sizeof (Message)) > 0)
        if(!KnightQueues[knightNum].empty())
        {
            pthread_mutex_lock(&mutexKnights[knightNum]);
            msg = KnightQueues[knightNum].front();
            KnightQueues[knightNum].pop();
            pthread_mutex_unlock(&mutexKnights[knightNum]);

            if(msg.damage == 0 && msg.type == 0)
            {
                logger.Log("MESSAGE", "Battle Starting...");
                //this is to make the knight start attacking init
            }
            else if (msg.type == - 10)
            {
                currentRabbit++;
            }
            else
            {
                knight.SetHealth(knight.GetHealth() - msg.damage);

                //write to logger queue the received attack message (p4)
                pthread_mutex_lock(&mutexLogger);
                loggerQueue.push(msg);
                pthread_mutex_unlock(&mutexLogger);

                if(knight.GetHealth() <= 0)
                {
                    break; //end the loop here is the damage is too much
                }
                if(!childsRunning){
                    return;
                }
            }

            //SEND ATTACK
            int randomNumber = rand() % 100 + 1;
            if(randomNumber <= 15) // generate an attack
            {
                msg.type = 0;
                msg.damage = knight.GetStrongAttackDmg();
            }
            else if(randomNumber <= 75)
            {
                msg.type = 1;
                msg.damage = knight.GetWeakAttackDmg();
            }
            else
            {
                msg.type = 2;
                msg.damage = knight.GetAOEDamage();
            }

            msg.from = knightNum + maxRabbitNum;
            msg.to = currentRabbit;
            if(!childsRunning){
                return;
            }
            //write to selected rabbits queue (p4)
            pthread_mutex_lock(&mutexRabbits[currentRabbit]);
            RabbitQueues[currentRabbit].push(msg);
            pthread_mutex_unlock(&mutexRabbits[currentRabbit]);
            if(!childsRunning){
                return;
            }
        };
    }

    //Write Death message for the main process to handle
    msg.from = knightNum + maxRabbitNum;
    msg.type = 0;
    msg.damage = - 1;

    //write to main thread queue notifying of knight death(p4)
    pthread_mutex_lock(&mutexMain);
    mainQueue.push(msg);
    pthread_mutex_unlock(&mutexMain);

}

/**
 * RabbitProcess
 *
 * Method that executes the Rabbit process
 *
 * @param KnightPipes[][2]
 * @param RabbitPipe[2]
 * @param mainPipe[2]
 * @param loggerPipe[2]
 * @param rabbitNum
 */
void RabbitProcess(int rabbitNum)
{

    srand(time(NULL) ^ getpid());
    Message msg; //message object to hold message
    Rabbit rabbit; //rabbit object for obvious reasons
    rabbit.SetName(rabbitNum);
    //logger.Log("MESSAGE", "Spawned " + rabbit.GetName());
    int currentKnight = 0; //the current knight that the rabbit is attacking

    while(rabbit.GetHealth() > 0 || currentKnight < maxKnightNum)
    {
        sleep(.2);
        if(!childsRunning){
            return;
        }
        //RECEIVE ATTACK
        if(!RabbitQueues[rabbitNum].empty())
        {
            pthread_mutex_lock(&mutexRabbits[rabbitNum]);
            msg = RabbitQueues[rabbitNum].front();
            RabbitQueues[rabbitNum].pop();
            pthread_mutex_unlock(&mutexRabbits[rabbitNum]);

            if(msg.damage == 0 && msg.type == 0)
            {
                //this is to make the rabbit start attacking
            }
            else if(msg.type == -10)
            {
                currentKnight++;
            }
            else
            {
                rabbit.SetHealth(rabbit.GetHealth() - msg.damage);

                pthread_mutex_lock(&mutexLogger);
                loggerQueue.push(msg);
                pthread_mutex_unlock(&mutexLogger);

                if(rabbit.GetHealth() <= 0)
                {
                    break; //end the loop here if the damage is too much
                }
                if(!childsRunning){
                    return;
                }
            }

            //SEND ATTACK
            int randomNumber = rand() % 100 + 1;
            if(randomNumber <= 15) // generate an attack
            {
                msg.type = 0;
                msg.damage = rabbit.GetStrongAttackDmg();
            }
            else if(randomNumber <= 75)
            {
                msg.type = 1;
                msg.damage = rabbit.GetWeakAttackDmg();
            }
            else
            {
                msg.type = 2;
                msg.damage = rabbit.GetAOEDamage();
            }

            msg.from = rabbitNum;
            msg.to = currentKnight;
            if(!childsRunning){
                return;
            }
            pthread_mutex_lock(&mutexKnights[currentKnight]);
            KnightQueues[currentKnight].push(msg);
            pthread_mutex_unlock(&mutexKnights[currentKnight]);
            if(!childsRunning){
                return;
            }
        };
    }

    //write the death message to the main process
    msg.from = rabbitNum;
    msg.type = 0;
    msg.damage = - 1;

    pthread_mutex_lock(&mutexMain);
    mainQueue.push(msg);
    pthread_mutex_unlock(&mutexMain);

}

/**
 * MainProcess
 *
 * Method that executes the Knight process
 *
 * @param KnightPipes[][2]
 * @param RabbitPipes[][2]
 * @param mainPipe[2]
 * @param loggerPipe[2]
 */
void MainProcess()
{
    Message msg;

    //start the simulation
    msg.from = 0;
    msg.damage = 0;
    msg.type = 0;

    //write to the first knight to kick off the simulation
    pthread_mutex_lock(&mutexKnights[0]);
    KnightQueues[0].push(msg);
    pthread_mutex_unlock(&mutexKnights[0]);

    int aliveKnights = maxKnightNum;
    int aliveRabbits = maxRabbitNum;

    while(aliveKnights > 0 && aliveRabbits > 0)
    {
        //sleep(1);

        if(!mainQueue.empty())
        {
            pthread_mutex_lock(&mutexMain);
            msg = mainQueue.front();
            mainQueue.pop();
            pthread_mutex_unlock(&mutexMain);

            if(msg.damage == -1)
            {
                pthread_mutex_lock(&mutexLogger);
                loggerQueue.push(msg);
                pthread_mutex_unlock(&mutexLogger);

                //Knight died
                if(msg.from >= maxRabbitNum)
                {
                    //update alive knight array in all rabbits
                    msg.from = msg.from - maxRabbitNum; //get the id of the knight
                    msg.type = -10;

                    //update all lists
                    for(int i = 0; i < maxRabbitNum;i ++)
                    {
                        pthread_mutex_lock(&mutexRabbits[i]);
                        RabbitQueues[i].push(msg);
                        pthread_mutex_unlock(&mutexRabbits[i]);
                    }
                    aliveKnights--;
                    if(aliveKnights == 0){
                        childsRunning = false;
                        break;
                    }
                }
                //Rabbit died
                else
                {
                    //update alive knight array in all rabbits
                    msg.from = msg.from; //get the id of the rabbit
                    msg.type = -10;

                    //update all lists
                    for(int i = 0; i < maxKnightNum;i ++)
                    {
                        //write(KnightPipes[i][1], &msg, sizeof (Message));
                        pthread_mutex_lock(&mutexKnights[i]);
                        KnightQueues[i].push(msg);
                        pthread_mutex_unlock(&mutexKnights[i]);
                    }
                    aliveRabbits--;
                    if(aliveRabbits == 0){
                        childsRunning = false;
                        break;
                    }
                }
            }
        }
    }

    //kill all the combatants.. keep logger open to finish writing to file, then end program
    childsRunning = false;
    logger.Log("MESSAGE", "Battle has ended...");

    if(aliveKnights > 0)
    {
        msg.type = -20;
        msg.damage = -20;
        msg.from = -20;
        msg.to = -20;

        pthread_mutex_lock(&mutexLogger);
        loggerQueue.push(msg);
        pthread_mutex_unlock(&mutexLogger);
    }
    else
    {
        msg.type = -30;
        msg.damage = -30;
        msg.from = -30;
        msg.to = -30;

        pthread_mutex_lock(&mutexLogger);
        loggerQueue.push(msg);
        pthread_mutex_unlock(&mutexLogger);
    }

    //send kill message to the logger
    msg.damage = -5;
    msg.type = -5;
    msg.from = -5;

    pthread_mutex_lock(&mutexLogger);
    loggerQueue.push(msg);
    pthread_mutex_unlock(&mutexLogger);
}


/**
 * Terminate
 *
 * abort the program appropriately and close the opened log file.
 */
void Terminate()
{
    logger.CloseFile();
    abort();
}

/**
 * CheckArguments
 *
 * Method that checks the arguments to make sure the program is going to work
 *
 * @param agc - count of arguments
 * @param argv - the value of the arguments
 */
void CheckArguments(int argc, char *argv[])
{
    using namespace std;

    //check to make sure the minimum possible number of arguments is passed in, if not tell the user.
    if(argc <= 4)
    {
        logger.Log("ERROR", "Command line arguments -m and -n are required to run this program.");
        logger.Log("ERROR","Example, -l filename -m 4 -n 2");
        abort(); //terminate
    }
    else if (argc >= 5)
    {
        //variables to keep track if arguments are found or not, mostly for debugging purposes.
        bool lFound = false;
        bool mFound = false;
        bool nFound = false;

        //this loop is needed to check the command arguments. A loop here is required because the arguments can be
        //in any order.
        for(int i = 1; i < argc; i++)
        {
            if (string(argv[i]) == "-l") //check for the optional log file argument, if none is found it is defaulted
            {
                lFound = true;

                //logger.Log("MESSAGE", "-l found");
                try
                {
                    //try getting the string of the logfile name, if not found or null then default to 'log'
                    if (string(argv[i + 1]) != "-m" && string(argv[i + 1]) != "-n")
                    {
                        logger.SetLogFileName(string(argv[i + 1]));
                        fileName = string(argv[i + 1]);
                        //logger.Log("MESSAGE", "Log file name is set to: " + string(argv[i + 1]));
                        logger.OpenFile();
                    }
                    else
                    {
                        logger.Log("WARNING", "Log file name not found. Defaulting to log.");
                        logger.SetLogFileName("log");
                        fileName = "log";
                        logger.OpenFile();
                    }
                }
                catch(exception)
                {
                    logger.Log("WARNING", "Log file name not found. Defaulting to log.");
                    logger.SetLogFileName("log");
                    fileName = "log";
                    logger.OpenFile();
                };


            }
            else if (string(argv[i]) == "-m") // check for the m flag and make sure the value is right
            {
                mFound = true;
                //logger.Log("MESSAGE", "-m found");

                try
                {
                    if (string(argv[i + 1]) != "-l" && string(argv[i + 1]) != "-n")
                    {
                        maxKnightNum = stoi(string(argv[i + 1]));

                        if(maxKnightNum < 1)
                        {
                            logger.Log("ERROR", "-M and -N have to be 1 or greater");
                            Terminate();
                        }
                    }
                    else
                    {
                        logger.Log("ERROR", "Incorrect value for M flag.");
                        logger.Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                        logger.Log("ERROR","Example, -l filename -m 4 -n 2");
                        Terminate();
                    }
                }
                catch(exception)
                {
                    logger.Log("ERROR", "Incorrect value for M flag.");
                    logger.Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                    logger.Log("ERROR","Example, -l filename -m 4 -n 2");
                    Terminate();
                };
            }
            else if (string(argv[i]) == "-n") // check for the n flag and make sure the value is right
            {
                nFound = true;
                //logger.Log("MESSAGE", "-n found");

                try
                {
                    if (string(argv[i + 1]) != "-l" && string(argv[i + 1]) != "-m")
                    {
                        maxRabbitNum = stoi(string(argv[i + 1]));

                        if(maxRabbitNum < 1)
                        {
                            logger.Log("ERROR", "-M and -N have to be 1 or greater");
                            Terminate();
                        }
                    }
                    else
                    {
                        logger.Log("ERROR", "Incorrect value for N flag.");
                        logger.Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                        logger.Log("ERROR","Example, -l filename -m 4 -n 2");
                        Terminate();
                    }
                }
                catch(exception)
                {
                    logger.Log("ERROR", "Incorrect value for N flag.");
                    logger.Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                    logger.Log("ERROR","Example, -l filename -m 4 -n 2");
                    Terminate();
                };
            }
        }

        if(lFound == false) //if the log file is not specified. log it
        {
            logger.Log("WARNING", "Log file name not found. Defaulting to log.");
            logger.SetLogFileName("log");
            fileName = "log";
            logger.OpenFile();
        }

        if(!mFound || !nFound) // if m and n have not been passed in, throw an error and terminate the program.
        {
            logger.Log("ERROR", "Arguments -m and -n are required to run this application");
            Terminate(); //terminate if n and m are not found
        }

        if(maxKnightNum + maxRabbitNum < 5)
        {
            logger.Log("ERROR", "M + N MUST be greater than or equal to 5.");
            Terminate(); //terminate if n and m are not found
        }

    }
}
