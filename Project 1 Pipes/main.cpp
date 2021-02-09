///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Main.cpp
//	Description:                    This is the driver for the program (i tried)
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Friday January 30, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <fcntl.h>
#include <chrono>
#include <sstream>
#include <lastlog.h>

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
void LoggerProcess(int loggerPipe[2]);
void MainProcess(int KnightPipes[][2], int RabbitPipe[][2], int mainPipe[2], int loggerPipe[2]);
void KnightProcess(int KnightPipe[2], int RabbitPipes[][2], int mainPipe[2], int loggerPipe[2], int knightNum);
void RabbitProcess(int KnightPipes[][2], int RabbitPipe[2], int mainPipe[2], int loggerPipe[2], int rabbitNum);
void Terminate();

int maxKnightNum = 0;   //The number of knights combatants for side 1;
int maxRabbitNum = 0;   //The number of rabbits combatants for side 2;
Logger logger;          //Logger object for outputting to the console and the log file.

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

    vector<int> cids;       //holds the child pid's

    int loggerPipe[2];
    int mainPipe[2];
    int KnightPipes[maxKnightNum][2];
    int RabbitPipes[maxRabbitNum][2];

    //INIT LOGGER PIPE
    if(pipe(loggerPipe) < 0)
    {
        logger.Log("Failed Initializing Logger Pipe.");
    }

    //INIT MAIN PROCESS PIPE
    if(pipe2(mainPipe, O_NONBLOCK) < 0)
    {
        logger.Log("Failed Initializing Main Process Pipe.");
    }

    //INIT PIPES FOR KNIGHTS
    for(int i = 0; i < maxKnightNum; i++)
    {
        if(pipe2(KnightPipes[i], O_NONBLOCK) < 0)
        {
            logger.Log("Failed Initializing Knight Pipes.");
        }
    }

    //INIT PIPES FOR RABBITS
    for(int i = 0; i < maxRabbitNum; i++)
    {
        if(pipe2(RabbitPipes[i], O_NONBLOCK) < 0)
        {
            logger.Log("Failed Initializing Rabbit Pipes.");
        }
    }

    //LOGGER PROCESS
    int loggerChild = fork();
    cids.push_back(loggerChild);
    if (loggerChild == -1)
    {
        logger.Log("ERROR", "Error forking logger.");
    }
    else if (loggerChild == 0) //This is the child's code
    {
        //LOGGER PROCESS CODE
        LoggerProcess(loggerPipe);
        _exit(EXIT_SUCCESS);
    }

    //KNIGHT PROCESS INIT
    int knightChild;
    for(int i = 0; i < maxKnightNum; i++) {
        knightChild = fork();
        cids.push_back(knightChild);

        if (knightChild == -1) {
            logger.Log("ERROR", "Error forking for child.");
        }
        else if (knightChild == 0) //This is the child's code
        {
            //KNIGHT PROCESS CODE
            KnightProcess(KnightPipes[i], RabbitPipes, mainPipe, loggerPipe, i);
            _exit(EXIT_SUCCESS);
        }
        else{
        }
    }

    //RABBIT PROCESS INIT
    int rabbitChild;
    for(int i = 0; i < maxRabbitNum; i++)
    {
        rabbitChild = fork();
        cids.push_back(rabbitChild);

        if (rabbitChild == -1) {
            logger.Log("ERROR", "Error forking for child.");
        }
        else if (rabbitChild == 0) //This is the child's code
        {
            //RABBIT PROCESS CODE
            RabbitProcess(KnightPipes, RabbitPipes[i], mainPipe, loggerPipe, i);
            _exit(EXIT_SUCCESS);
        }
    }

    ///////////////////////MAIN PROCESS///////////////////////
    MainProcess(KnightPipes, RabbitPipes, mainPipe, loggerPipe);
    //WAIT FOR REST OF PROCESSES TO DIE
    int status;
    sleep(2);
    for(int i = 0; i < cids.size(); i ++)
    {
        if(kill(cids[i], SIGTERM) == -1 && errno != ESRCH){
            exit(EXIT_SUCCESS);
        }
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
void LoggerProcess(int loggerPipe[2])
{

    close(loggerPipe[1]); //close unused end
    Message msg; //message object for displayinf
    bool running = true; //make this loop infinite until it gets the kill message
    while(running)
    {
        if(read(loggerPipe[0], &msg, sizeof(Message)) > 0)
        {
            //logger.Log("I have read something");
            if(msg.damage == -5 && msg.type == -5 && msg.from == -5)
            {
                logger.Log("Logger Kill switch activated.");
                logger.Log("Output saved to file.");
                close(loggerPipe[0]);
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
void KnightProcess(int KnightPipe[2], int RabbitPipes[][2], int mainPipe[2], int loggerPipe[2], int knightNum)
{
    //logger.Log("This is the Knight Process " + to_string(knightNum));
    close(loggerPipe[0]);
    srand(time(NULL) ^ getpid());
    Message msg;
    Knight knight;


    int currentRabbit = 0;
    while(knight.GetHealth() > 0 || currentRabbit > maxRabbitNum)
    {
        sleep(.2);

        //RECEIVE ATTACK
        if(read(KnightPipe[0], &msg, sizeof (Message)) > 0)
        {
            if(msg.damage == 0 && msg.type == 0)
            {

            }
            else if (msg.type == - 10)
            {
                currentRabbit++;
            }
            else
            {
                knight.SetHealth(knight.GetHealth() - msg.damage);
                //logger.Log("Knight Health: " + to_string(knight.GetHealth()));
                write(loggerPipe[1], &msg, sizeof (Message));

                if(knight.GetHealth() <= 0)
                {
                    break;
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
            write(RabbitPipes[currentRabbit][1], &msg, sizeof (Message));
        };

    }

    msg.from = knightNum + maxRabbitNum;
    msg.type = 0;
    msg.damage = - 1;
    write(mainPipe[1], &msg, sizeof (Message));

    close(mainPipe[1]);
    close(mainPipe[0]);
    close(loggerPipe[1]);
    _Exit(0);
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
void RabbitProcess(int KnightPipes[][2], int RabbitPipe[2], int mainPipe[2], int loggerPipe[2], int rabbitNum)
{
    //logger.Log("This is the Rabbit Process " + to_string(rabbitNum));
    close(loggerPipe[0]);
    close(RabbitPipe[1]);
    srand(time(NULL) ^ getpid());
    Message msg;
    Rabbit rabbit;

    int currentKnight = 0;

    while(rabbit.GetHealth() > 0 || currentKnight < maxKnightNum)
    {
        sleep(.2);

        //RECEIVE ATTACK
        if(read(RabbitPipe[0], &msg, sizeof (Message)) > 0)
        {
            if(msg.damage == 0 && msg.type == 0)
            {

            }
            else if(msg.type == -10)
            {
                currentKnight++;
            }
            else
            {
                rabbit.SetHealth(rabbit.GetHealth() - msg.damage);
                //logger.Log("Rabbit Health: " + to_string(rabbit.GetHealth()));
                write(loggerPipe[1], &msg, sizeof (Message));

                if(rabbit.GetHealth() <= 0)
                {
                    break;
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
            write(KnightPipes[currentKnight][1], &msg, sizeof (Message));

        };

    }
    //logger.Log("Rabbit has died peacefully");

    msg.from = rabbitNum;
    msg.type = 0;
    msg.damage = - 1;
    write(mainPipe[1], &msg, sizeof (Message));

    close(RabbitPipe[0]);

    close(mainPipe[1]);
    close(mainPipe[0]);
    close(loggerPipe[1]);
    _Exit(0);
}

/**
 * KnightProcess
 *
 * Method that executes the Knight process
 *
 * @param KnightPipes[][2]
 * @param RabbitPipes[][2]
 * @param mainPipe[2]
 * @param loggerPipe[2]
 */
void MainProcess(int KnightPipes[][2], int RabbitPipes[][2], int mainPipe[2], int loggerPipe[2])
{
    //logger.Log("This is the main process.");
    close(loggerPipe[0]);

    Message msg;

    //start the simulation
    msg.from = 0;
    msg.damage = 0;
    msg.type = 0;

    write(KnightPipes[0][1], &msg, sizeof(Message));

    int aliveKnights = maxKnightNum;
    int aliveRabbits = maxRabbitNum;

    while(aliveKnights > 0 && aliveRabbits > 0)
    {
        sleep(.2);
        if(read(mainPipe[0], &msg, sizeof (Message)) > 0)
        {
            if(msg.damage == -1)
            {
                write(loggerPipe[1], &msg, sizeof (Message));

                //Knight died
                if(msg.from >= maxRabbitNum)
                {
                    //update alive knight array in all rabbits
                    msg.from = msg.from - maxRabbitNum; //get the id of the knight
                    msg.type = -10;

                    //update all lists
                    for(int i = 0; i < maxRabbitNum;i ++)
                    {
                        write(RabbitPipes[i][1], &msg, sizeof (Message));
                    }
                    aliveKnights--;
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
                        write(KnightPipes[i][1], &msg, sizeof (Message));
                    }
                    aliveRabbits--;
                }
            }
        }
    }


    if(aliveKnights > 0){
        msg.type = -20;
        msg.damage = -20;
        msg.from = -20;
        msg.to = -20;
        write(loggerPipe[1], &msg, sizeof(Message));
    }else
        {
        msg.type = -30;
        msg.damage = -30;
        msg.from = -30;
        msg.to = -30;
        write(loggerPipe[1], &msg, sizeof(Message));
    }

    //send kill message to the logger
    msg.damage = -5;
    msg.type = -5;
    msg.from = -5;
    write(loggerPipe[1], &msg, sizeof(Message));

    close(loggerPipe[1]);
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
                        //logger.Log("MESSAGE", "Log file name is set to: " + string(argv[i + 1]));
                        logger.OpenFile();
                    }
                    else
                    {
                        logger.Log("WARNING", "Log file name not found. Defaulting to log.");
                        logger.SetLogFileName("log");
                        logger.OpenFile();
                    }
                }
                catch(exception)
                {
                    logger.Log("WARNING", "Log file name not found. Defaulting to log.");
                    logger.SetLogFileName("log");
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
