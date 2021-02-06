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
#include<fcntl.h>

#include "lib/Logger.h"

#include "mob/Knight.h"
#include "mob/Rabbit.h"

typedef struct
{
    int from;
    int type;
    int damage;
    int index;
    int indexTo;

} Message;


void CheckArguments(int argc, char *argv[]);
void Terminate();
void MainProcess();


int maxKnightNum = 0;   //The number of knights combatants for side 1;
int maxRabbitNum = 0;   //The number of rabbits combatants for side 2;
Logger logger;          //Logger object for outputting to the console and the log file.

int mainPipe[2];
int knightNumPipe[2];
int rabbitNumPipe[2];



//name bank for naming knights and rabbits.
string nameBank_Knight[] = {"King Arthur", "Sir Bedevere the Wise", "Sir Lancelot the Brave", "Sir Galahad the Chaste/Pure",
                            "Sir Robin the Not-Quite-So-Brave-As-Sir-Lancelot", "Sir Bors", "Sir Gawain", "Sir Ector", "Guillot the Truthful"
        ,"Gerould the Loyal", "Symon of the Fall", "Dodge the Bald", "Han the Smiling", "Sir Harrison"};
string nameBank_Rabbit[] = {"Waterton", "Sargos", "Blooding", "Carrotton", "Hareington", "Hopsville USA", "Florida", "Eggerton", "Volta",
                            "Eleyvine"};

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
    int KnightPipes[maxKnightNum][2];
    int RabbitPipes[maxRabbitNum][2];

    srand (time(NULL));

    CheckArguments(argc, argv); //check the arguments


    for(int i = 0; i < maxKnightNum; i ++) //create a pipe for each child process
    {
        pipe(KnightPipes[i]);

        //From Geeksforgeeks.com
        //https://www.geeksforgeeks.org/non-blocking-io-with-pipes-in-c/
        if (fcntl(KnightPipes[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);
    }
    for(int i = 0; i < maxRabbitNum; i ++) //create a pipe for each child process
    {
        pipe(RabbitPipes[i]);

        //From Geeksforgeeks.com
        //https://www.geeksforgeeks.org/non-blocking-io-with-pipes-in-c/
        if (fcntl(RabbitPipes[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);
    }

    pipe(mainPipe); //create the main process pipe


    pipe(rabbitNumPipe);
    pipe(knightNumPipe);

    write(knightNumPipe[1], &maxKnightNum, sizeof(maxKnightNum)); //write the current number of knights to a pipe
    write(rabbitNumPipe[1], &maxRabbitNum, sizeof(maxRabbitNum)); //write the current number of rabbits to a pipe


    for(int i = 0; i < maxKnightNum; i ++)
    {
        logger.Log("Spawned " + nameBank_Knight[i]);
    }
    for(int i = 0; i < maxRabbitNum; i ++)
    {
        logger.Log("Spawned " + nameBank_Rabbit[i]);
    }


    int knightChild;
    for(int i = 0; i < maxKnightNum; i++)
    {
        knightChild = fork();

        if (knightChild == -1)
        {
            logger.Log("ERROR", "Error forking for child.");
        }
        else if (knightChild == 0) //This is the child's code
        {
            Knight tempKnight;
            Message msg;
            int counter = 0;
            int numberOfKnights;

            while (tempKnight.GetHealth() > 0 )
            {
                msg.from = 0;

                if(counter == tempKnight.GetAttackRate())
                {
                    //attack a rabbit
                    counter = 0;

                    int randomNumber = rand() % 100 + 1;

                    if(randomNumber <= 15) // generate an attack
                    {
                        msg.type = 0;
                        msg.damage = tempKnight.GetStrongAttackDmg();
                    }
                    else if(randomNumber <= 75)
                    {
                        msg.type = 1;
                        msg.damage = tempKnight.GetWeakAttackDmg();
                    }
                    else
                    {
                        msg.type = 2;
                        msg.damage = tempKnight.GetAOEDamage();
                    }

                    msg.index = i; //from
                    sleep(0.1);

                    int rabbitNum;
                    ////////////////////////////////////// SEND ATTACK
                    if(read(rabbitNumPipe[0], &rabbitNum, sizeof(rabbitNum)) > 0)
                    {
                        if(rabbitNum > 0)
                        {
                            int chosenRabbit = rand() % rabbitNum; //should get random rabbit to attack here ********* from the current rabbit number

                            msg.indexTo = chosenRabbit; //document the receiving person
                            write(RabbitPipes[chosenRabbit][1], (char*) &msg, sizeof (Message)); //write the attack to the chosen rabbit

                            write(mainPipe[1], (char*) &msg, sizeof (Message)); //log this attack
                            write(rabbitNumPipe[1], &rabbitNum, sizeof(rabbitNum)); // write back rabbit num
                        }
                        else
                        {
                            int temp = 0;
                            logger.Log("no more rabbits to attack");
                            write(knightNumPipe[1], &temp, sizeof (temp));
                        }
                    };
                    /////////////////////////////////////

                }
                if(tempKnight.GetHealth() > 0) // if the knight is alive we can take an attack
                {
                    int checkIfNull = read(KnightPipes[i][0], (char* ) &msg, sizeof(Message));
                    if(checkIfNull > 0)
                    {
                        tempKnight.SetHealth(tempKnight.GetHealth() - msg.damage);
                    };
                }
                counter ++;
            }

/////////////////////////////////////////////////////////////////////////////////////////////////
//PROGRAM GETS STUCK SOMEWHERE AROUND HERE

            //reduce the number of knights when one dies
            if(read(knightNumPipe[0], &numberOfKnights, sizeof (numberOfKnights)) > 0)
            {
                numberOfKnights--;
                write(knightNumPipe[1], &numberOfKnights, sizeof(numberOfKnights));
                close(KnightPipes[i][0]);
                close(KnightPipes[i][1]);
            };

            msg.from = 0; //this is to tell the logger a knight has died
            msg.damage = 0;
            msg.index = i;

            write(mainPipe[1], (char*) &msg, sizeof (Message));


            msg.from = 0;
            msg.damage = 0;
            msg.type = 0;
            msg.index = 0;
            write(mainPipe[1], (char*) &msg, sizeof (Message));

            _Exit(0);

/////////////////////////////////////////////////////////////////////////////////////////////////
        }
        else
        {
           // MainProcess();
        }
    }

    int rabbitChild;
    for(int i = 0; i < maxRabbitNum; i++)
    {
        rabbitChild = fork();

        if (rabbitChild == -1)
        {
            logger.Log("ERROR", "Error forking for child.");
        }
        else if (rabbitChild == 0) //This is the child's code
        {
            Rabbit tempRabbit;
            Message msg;
            int counter = 0;
            int numberOfRabbits;

            while (tempRabbit.GetHealth() > 0 )
            {
                msg.from = 1;

                if(counter == tempRabbit.GetAttackRate())
                {
                    //attack a rabbit
                    counter = 0;

                    int randomNumber = rand() % 100 + 1;

                    if(randomNumber <= 15) // generate an attack
                    {
                        msg.type = 0;
                        msg.damage = tempRabbit.GetStrongAttackDmg();
                    }
                    else if(randomNumber <= 75)
                    {
                        msg.type = 1;
                        msg.damage = tempRabbit.GetWeakAttackDmg();
                    }
                    else
                    {
                        msg.type = 2;
                        msg.damage = tempRabbit.GetAOEDamage();
                    }

                    msg.index = i; //from
                    sleep(0.1);

                    int knightNum;
                    ////////////////////////////////////// SEND ATTACK
                    if(read(knightNumPipe[0], &knightNum, sizeof(knightNum)) > 0)
                    {
                        if(knightNum > 0)
                        {
                            int chosenKnight = rand() % knightNum; //should get random rabbit to attack here ********* from the current rabbit number

                            msg.indexTo = chosenKnight; //document the receiving person
                            write(KnightPipes[chosenKnight][1], (char*) &msg, sizeof (Message));

                            write(mainPipe[1], (char*) &msg, sizeof (Message)); //log this attack
                            write(knightNumPipe[1], &knightNum, sizeof(knightNum));
                        }
                        else
                        {
                            int temp = -1;
                            write(knightNumPipe[1], &temp, sizeof (temp));

                            _Exit(0);
                        }

                    };
                    /////////////////////////////////////

                }
                if(tempRabbit.GetHealth() > 0) // if the knight is alive we can take an attack
                {
                    int checkIfNull = read(RabbitPipes[i][0], (char* ) &msg, sizeof(Message));
                    if(checkIfNull > 0)
                    {
                        tempRabbit.SetHealth(tempRabbit.GetHealth() - msg.damage);
                    };
                }
                counter ++;
            }

            //reduce the number of rabbits when one dies
            if(read(rabbitNumPipe[0], &numberOfRabbits, sizeof (numberOfRabbits)) > 0)
            {
                numberOfRabbits--;
                write(rabbitNumPipe[1], &numberOfRabbits, sizeof(numberOfRabbits));

                close(RabbitPipes[i][0]);
                close(RabbitPipes[i][1]);
            };

            msg.from = 1; //this is to tell the logger a rabbit has died
            msg.damage = 0;
            msg.index = i;
            write(mainPipe[1], (char*) &msg, sizeof (Message));


           msg.from = 0;
           msg.damage = 0;
            msg.type = 0;
            msg.index = 0;
            write(mainPipe[1], (char*) &msg, sizeof (Message));

            _Exit(0);
        }
        else
        {
            //MainProcess();
        }
    }

    MainProcess();

    logger.Log("\n");
    int status;
    for(int i = 0; i < maxRabbitNum + maxKnightNum; i ++)
    {
        wait(&status);
    }

    int result;
    if(read(knightNumPipe[0], &result, sizeof (result)) > 0){
        if(result == 0)
        {
            logger.Log("KNIGHTS WIN");
        }else{
            logger.Log("RABBITS WIN");
        }
    }

    logger.CloseFile();
    return 0;
}

void MainProcess()
{
    //logger.Log("This is the main process code.");
    Message msgIn;

    while(read(mainPipe[0], (char * )&msgIn, sizeof (Message)) > 0)
    {
        string outString = "";

        if (msgIn.damage == 0 && msgIn.type == 0 && msgIn.from == 0 && msgIn.index == 0)
        {
            break;
        }

        else if(msgIn.damage == 0 && msgIn.from == 0) //check for death
        {
            outString = (nameBank_Knight[msgIn.index] + " has fallen!");
        }
        else if(msgIn.damage == 0 && msgIn.from == 1) //check for death
        {
            outString = "Killer Rabbit of " + (nameBank_Rabbit[msgIn.index] + " has fallen!");
        }
        else
        {
            if(msgIn.from == 0)
            {
                outString += nameBank_Knight[msgIn.index] + " ";

                if(msgIn.type == 0)
                {
                    outString +=  ("slashed ");
                }
                else if (msgIn.type == 1)
                {
                    outString += ("thrusted ");
                }
                else
                {
                    outString += ("cleaved ");
                }

                outString += "Killer Rabbit of " + nameBank_Rabbit[msgIn.indexTo] + " ";
            }
            else
            {
                outString += ("Killer Rabbit of " + nameBank_Rabbit[msgIn.index] + " ");

                if(msgIn.type == 0)
                {
                    outString += ("throat leaped ");
                }
                else if (msgIn.type == 1)
                {
                    outString += ("bit ");
                }
                else
                {
                    outString += ("flying nibbled ");
                }

                outString += nameBank_Knight[msgIn.indexTo] + " ";
            }

            outString += "for " + (to_string(msgIn.damage) + " damage!");
        }

        logger.LogToBoth("MESSAGE", outString);
    }



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
