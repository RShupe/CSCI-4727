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
#include <functional>

#include "lib/Logger.h"

#include "mob/Knight.h"
#include "mob/Rabbit.h"

typedef struct
{
    string from;
    string type;
    int damage;
} Message;


void CheckArguments(int argc, char *argv[]);
void Terminate();
void Child1Code();

int maxKnightNum = 0;   //The number of knights combatants for side 1;
int maxRabbitNum = 0;   //The number of rabbits combatants for side 2;
Logger logger;      //Logger object for outputting to the console and the log file.



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
    Message msg;

    CheckArguments(argc, argv); //check the arguments

    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1)
    {
        logger.Log("ERROR", "Error opening pipe 1.");
    }

    if (pipe(pipe2) == -1)
    {
        logger.Log("ERROR", "Error opening pipe 2.");
    }

    logger.Log("SUCCESS", "Pipes opened correctly!");


    for(int i = 0; i < maxKnightNum; i++)
    {
        int knightChild = fork();
        if (knightChild == -1)
        {
            logger.Log("ERROR", "Error forking for child 1.");
        }
        else if (knightChild == 0) //This is the first child's code
        {
            logger.Log("Knight child open: " + to_string(i + 1));


            Knight newKnight(i);

            int counter = 0;

            //logger.Log(currentKnight.GetName());
            //while loop? while health > 0
            while (newKnight.GetHealth() > 0) {
                if (counter == newKnight.GetAttackRate()) {
                    counter = 0;

                    msg.damage = newKnight.Attack();
                    msg.from = newKnight.GetName();
                    msg.type = newKnight.GetCurrentAttack();

                    //write(pipe1[1], (char *) &msg, sizeof(Message));

                    //logger.Log(msg.type);

                }

                counter++; // increment the counter to attack on the right loop

                newKnight.SetHealth(newKnight.GetHealth() - 10);



                //send attack or receive

            }
            _Exit(0);
        }
    }

    for(int i = 0; i < maxRabbitNum; i++)
    {
        int rabbitChild = fork();
        if (rabbitChild == -1)
        {
            logger.Log("ERROR", "Error forking for child 2.");
        }
        else if (rabbitChild == 0) //This is the first child's cod
        {
            logger.Log("Rabbit child open: " + to_string(i + 1));

            Knight newKnight(i);

            int counter = 0;

            //logger.Log(currentKnight.GetName());
            //while loop? while health > 0
            while (newKnight.GetHealth() > 0)
            {
                if (counter == newKnight.GetAttackRate())
                {
                    counter = 0;

                    msg.damage = newKnight.Attack();
                    msg.from = newKnight.GetName();
                    msg.type = newKnight.GetCurrentAttack();

                    //write(pipe1[1], (char *) &msg, sizeof(Message));

                    //logger.Log(msg.type);

                }

                counter++; // increment the counter to attack on the right loop

                newKnight.SetHealth(newKnight.GetHealth() - 10);

                //send attack or receive

            }
            _Exit(0);
        }
    }

    int t;
    for(int i = 0; i < 5; i++)
    {
        wait(&t);
    }

    logger.CloseFile();
    return 0;
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
