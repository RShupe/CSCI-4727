///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Main.cpp
//	Description:                    This is the driver for the program
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Friday January 30, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include<fcntl.h>

#include "lib/Logger.h"

#include "mob/Knight.h"
#include "mob/Rabbit.h"

//Struct for the message that gets sent across pipes
typedef struct
{
    int from;
    int type;
    int damage;

} Message;

typedef struct
{
    string Message;

} LogMessage;


void CheckArguments(int argc, char *argv[]);
void Terminate();
void LoggerProcess();

int maxKnightNum = 0;   //The number of knights combatants for side 1;
int maxRabbitNum = 0;   //The number of rabbits combatants for side 2;
Logger logger;          //Logger object for outputting to the console and the log file.

int loggerPipe[2];
int mainPipe[2];


/**
 * Main
 *
 * The main function of the program.
 *
 * @param agc - count of arguments
 * @param argv - the value of the arguments
 */
int main(int argc, char *argv[]) {
    using namespace std;

    srand (time(NULL));
    CheckArguments(argc, argv); //check the arguments

    int KnightPipes[maxKnightNum][2];
    int RabbitPipes[maxRabbitNum][2];


    pipe(loggerPipe); //create the logger process pipe
    pipe(mainPipe); //create the logger process pipe

    int loggerChild = fork();
    if (loggerChild == -1)
    {
        logger.Log("ERROR", "Error forking logger.");
    }
    else if (loggerChild == 0) //This is the child's code
    {
        srand (time(NULL));
        LoggerProcess();
    }

    for(int i = 0 ; i < maxKnightNum; i ++)
    {
        pipe(KnightPipes[i]);
    }

    for(int i = 0 ; i < maxRabbitNum; i ++)
    {
        pipe(RabbitPipes[i]);
    }


    int knightChild;
    for(int i = 0; i < maxKnightNum; i++) {
        knightChild = fork();

        if (knightChild == -1) {
            logger.Log("ERROR", "Error forking for child.");
        }
        else if (knightChild == 0) //This is the child's code
        {
            srand (time(NULL));
            Message msg;
            Knight knight;
            int counter = 0;

            while(knight.GetHealth() > 0)
            {
                sleep(.2);
                //RECEIVE
                if(read(KnightPipes[i][0], &msg, sizeof (Message)) > 0)
                {
                    knight.SetHealth(knight.GetHealth() - msg.damage);

                    Rabbit rabbit;
                    rabbit.SetName(msg.from);

                    //LogMessage log;
                    //log.Message = knight.GetName() + " received " + to_string(msg.damage) + " damage from " +
                    // rabbit.GetName();

                    write(loggerPipe[1], &msg, sizeof (Message));// log the received attack

                    if(knight.GetHealth() < 0){
                        break;
                    }
                }

                //ATTACK
                if(counter == knight.GetAttackRate())
                {
                    counter = 0;

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

                    msg.from = maxRabbitNum + i;
                    write(RabbitPipes[i][1], &msg, sizeof(Message));
                }
                else
                {
                    counter ++;
                }
            }

            //SIGNAL TO MAIN OF DEATH
            msg.from = maxRabbitNum + i; //KNIGHT ID IS THROUGH maxRabbitnum - k
            write(mainPipe[1], &msg, sizeof (Message));

            close(KnightPipes[i][0]);
            //close(KnightPipes[i][1]);

            _exit(EXIT_SUCCESS);
        }
        else{
        }
    }


    int rabbitChild;
    for(int i = 0; i < maxRabbitNum; i++)
    {
        rabbitChild = fork();

        if (rabbitChild == -1) {
            logger.Log("ERROR", "Error forking for child.");
        }
        else if (rabbitChild == 0) //This is the child's code
        {
            srand (time(NULL));
            Message msg;
            Rabbit rabbit;
            int counter = 0;

            while(rabbit.GetHealth() > 0)
            {
                sleep(.2);
                //RECEIVE
                if(read(RabbitPipes[i][0], &msg, sizeof (Message)) > 0)
                {
                    rabbit.SetHealth(rabbit.GetHealth() - msg.damage);
                    write(loggerPipe[1], &msg, sizeof (Message));// log the received attack

                    if(rabbit.GetHealth() < 0){
                        break;
                    }
                }

                //ATTACK
                if(counter == rabbit.GetAttackRate())
                {
                    counter = 0;

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

                    msg.from = i;
                    write(KnightPipes[i][1], &msg, sizeof(Message));
                }
                else
                {
                    counter ++;
                }
            }

            //SIGNAL TO MAIN OF DEATH
            msg.from = i; //RABBIT ID IS 0 - MAX RABBIT NUM
            write(mainPipe[1], &msg, sizeof (Message));

            close(RabbitPipes[i][0]);
            //close(RabbitPipes[i][1]);

            _exit(EXIT_SUCCESS);
        }
        else{

        }
    }

    //sleep(5);

    int aliveKnights = maxKnightNum;
    int aliveRabbits = maxRabbitNum;
    Message msg;

    //while atleast one knight and one rabbit alive, check for a death to end the simulation
    while(aliveKnights > 0 && aliveRabbits > 0)
    {
        if(read(mainPipe[0], &msg, sizeof (Message)) > 0)
        {
            logger.LogToBoth("Detected a Death!");
            if(msg.from >= maxKnightNum)
            {
                logger.LogToBoth("Knight "+to_string(maxRabbitNum - msg.from)+" has fallen.");
                aliveKnights--;
            }
            else
            {
                logger.LogToBoth("Rabbit " + to_string(msg.from) + " has fallen.");
                aliveRabbits--;
            }
        }
        else{

        }
    }

    sleep(2);

    if(aliveKnights != 0)
    {
        logger.LogToBoth("VICTORY", "KNIGHTS WIN");
    }
    else
    {
        logger.LogToBoth("DEFEAT", "RABBITS WIN");
    }

    msg.damage = -5;

    write(loggerPipe[1], &msg, sizeof (Message));


    logger.CloseFile();

    int status;

    //for(int i = 0; i < maxRabbitNum + maxKnightNum + 1; i ++)
    //{
    //    wait(&status);
    //}

    close(mainPipe[0]);
    close(mainPipe[1]);

    kill(0,SIGTERM);

    return 0;
}


//CODE FOR THE LOGGER
void LoggerProcess()
{
    bool running = true;

    Message msg;

    while(running)
    {
        if(read(loggerPipe[0], &msg, sizeof (Message)) > 0)
        {

            if(msg.damage == -5)
            {
                logger.LogToBoth("Exit switch activated");
                break;
            }

            if(msg.from <= maxRabbitNum)
            {
                //Rabbit rabbit;
                //rabbit.SetName(msg.from);
                //logger.Log(rabbit.GetName() + " received: Type:" + to_string(msg.type) + " Damage: " + to_string(msg.damage));

                logger.LogToBoth("I am rabbit " + to_string(msg.from) + " and I received " + to_string(msg.damage) + " damage");
            }else
            {
                //Knight knight;
                //knight.SetName(msg.from - maxRabbitNum -1);
                //logger.Log(knight.GetName() + " received: Type:" + to_string(msg.type) + " Damage: " + to_string(msg.damage));

                logger.LogToBoth("I am knight " + to_string(msg.from - maxRabbitNum) + " and I received " + to_string(msg.damage) + " damage");
            }
        }

    }

    close(loggerPipe[0]);
    close(loggerPipe[1]);
    _exit(EXIT_SUCCESS);
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

        //debugging
        //logger.Log("MESSAGE", "M: " + to_string(side1Num));
        //logger.Log("MESSAGE", "N: " + to_string(maxRabbitNum));
        //logger.Log("MESSAGE", "LOGFILE: " + logger.GetLogFileName());
    }
}
