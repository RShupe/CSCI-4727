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


void CheckArguments(int argc, char *argv[]);
void Terminate();

int maxKnightNum = 0;   //The number of knights combatants for side 1;
int maxRabbitNum = 0;   //The number of rabbits combatants for side 2;
Logger logger;          //Logger object for outputting to the console and the log file.

vector<int> cids;       //holds the child pid's


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

    int ParentToKnight[maxKnightNum][2]; //pipe for communication from the parent to a knight
    int KnightToParent[maxKnightNum][2]; //pipe for communication from the knight to parent

    int ParentToRabbit[maxRabbitNum][2]; //pipe for communication from the parent to a rabbit
    int RabbitToParent[maxRabbitNum][2]; //pipe for communication from the rabbit to parent

    int loggerPipeKnight[maxKnightNum][2]; //pipe to send to the logger
    int loggerPipeRabbit[maxRabbitNum][2]; //pipe to send to the logger

    //INIT LOGGER PIPE FOR KNIGHTS
    for(int i = 0; i < maxKnightNum; i++){
        if(pipe(loggerPipeKnight[i]) < 0){
            Terminate();
        }

        //From Geeksforgeeks.com
        //https://www.geeksforgeeks.org/non-blocking-io-with-pipes-in-c/
        if (fcntl(loggerPipeKnight[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);
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
        srand (time(NULL));
        bool running = true;

        Message msg;

        while(running)
        {
            for(int i = 0; i < maxKnightNum; i ++) {
                if (read(loggerPipeRabbit[i][0], &msg, sizeof(Message)) > 0) {
                    if (msg.damage == -5 && msg.type == -5 && msg.from == -5) {
                        logger.LogToBoth("Exit switch activated (logger)");
                        running = false;
                        break;
                    }
                    Rabbit rabbit;
                    rabbit.SetName(msg.from);

                    Knight knight;
                    knight.SetName(i);

                    string outString = "";

                    outString += knight.GetName() + "";

                    if (msg.type == 0) {
                        outString += " slashed ";
                    } else if (msg.type == 1) {
                        outString += " thrusted ";
                    }
                    else{
                        outString += " cleaved ";
                    }

                    outString += rabbit.GetName() + " for " + to_string(msg.damage) + " damage!";

                    logger.LogToBoth(outString);
                }
            }

            for(int i = 0; i < maxRabbitNum; i ++) {
                if (read(loggerPipeKnight[i][0], &msg, sizeof(Message)) > 0) {
                    if (msg.damage == -5 && msg.type == -5 && msg.from == -5) {
                        logger.LogToBoth("Exit switch activated (logger)");
                        running = false;
                        break;
                    }
                    Rabbit rabbit;
                    rabbit.SetName(i);

                    Knight knight;
                    knight.SetName(msg.from);

                    string outString = "";

                    outString += rabbit.GetName() + "";

                    if (msg.type == 0) {
                        outString += " throat leaped ";
                    } else if (msg.type == 1) {
                        outString += " bit ";
                    }
                    else{
                        outString += " flying nibbled ";
                    }

                    outString += knight.GetName() + " for " + to_string(msg.damage) + " damage!";

                    logger.LogToBoth(outString);
                }
            }
        }

        for(int i = 0; i < maxKnightNum; i ++)
        {
            close(loggerPipeKnight[i][0]);
        }

        for(int i = 0; i < maxKnightNum; i ++)
        {
            close(loggerPipeRabbit[i][0]);
        }
        _exit(EXIT_SUCCESS);
    }

    //INITIALIZE KNIGHTS PIPES
    for(int i = 0 ; i < maxKnightNum; i ++)
    {
        if(pipe(ParentToKnight[i]) < 0){
            Terminate();
        }
        if(pipe(KnightToParent[i]) < 0){
            Terminate();
        }

        //From Geeksforgeeks.com
        //https://www.geeksforgeeks.org/non-blocking-io-with-pipes-in-c/
        if (fcntl(ParentToKnight[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);

        if (fcntl(KnightToParent[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);

    }

    //KNIGHT CODE
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
            sleep(1);
            srand(time(NULL) ^ getpid());
            close(ParentToKnight[i][1]);
            close(KnightToParent[i][0]);
            close(loggerPipeKnight[i][0]);

            int counter = 0;
            Knight knight;
            Message msgOut;
            Message msgIn;
            msgOut.damage = 0;
            msgOut.from = i;
            msgOut.type = 0;
            msgIn.damage = 0;
            msgIn.from = 0;
            msgIn.type = 0;

            knight.SetName(i);

            while(knight.GetHealth() > 0)
            {
                /////////////RECEIVE ATTACK////////////
                if(read(ParentToKnight[i][0], &msgIn, sizeof(Message)) > -1)
                {
                    knight.SetHealth(knight.GetHealth() - msgIn.damage);

                    write(loggerPipeKnight[i][1], &msgIn, sizeof (Message));
                    //logger.Log("Knight " + to_string(i) + " Health: " + to_string(knight.GetHealth()) + " attacked from Rabbit: " + to_string(msgIn.from));

                }else{
                    //logger.Log("Pipe Empty.");
                    sleep(.5);
                }

                if (knight.GetHealth() <= 0)
                {
                    break;
                }

                ////////////SEND ATTACK////////////////
                if(counter == knight.GetAttackRate())
                {
                    counter = 0;

                    int randomNumber = rand() % 100 + 1;
                    if(randomNumber <= 15) // generate an attack
                    {
                        msgOut.type = 0;
                        msgOut.damage = knight.GetStrongAttackDmg();
                    }
                    else if(randomNumber <= 75)
                    {
                        msgOut.type = 1;
                        msgOut.damage = knight.GetWeakAttackDmg();
                    }
                    else
                    {
                        msgOut.type = 2;
                        msgOut.damage = knight.GetAOEDamage();
                    }

                    msgOut.from = i;
                    if(write(KnightToParent[i][1], &msgOut, sizeof(Message)) < 0){
                        logger.Log("CANNOT WRITE ATTACK (KNIGHT)'");
                    }
                }
                else
                {
                    counter ++;
                }
            }

            msgOut.type = 0;
            msgOut.damage = -7;
            msgOut.from = 1;
            if(write(KnightToParent[i][1], &msgOut, sizeof(Message)) > 0){
                logger.Log(knight.GetName() + " has fallen!");
            };

            close(loggerPipeKnight[i][1]);
            close(ParentToKnight[i][0]);
            close(KnightToParent[i][1]);
            _exit(EXIT_SUCCESS);
        }
        else{
        }
    }

    //INITIALIZE RABBITS PIPES
    for(int i = 0 ; i < maxRabbitNum; i ++)
    {
        pipe(ParentToRabbit[i]);
        pipe(RabbitToParent[i]);

        //From Geeksforgeeks.com
        //https://www.geeksforgeeks.org/non-blocking-io-with-pipes-in-c/
        if (fcntl(ParentToRabbit[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);

        if (fcntl(RabbitToParent[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);

    }

    //INIT LOGGER PIPE FOR RABBITS
    for(int i = 0; i < maxRabbitNum; i++){
        if(pipe(loggerPipeRabbit[i]) < 0){
            Terminate();
        }

        //From Geeksforgeeks.com
        //https://www.geeksforgeeks.org/non-blocking-io-with-pipes-in-c/
        if (fcntl(loggerPipeRabbit[i][0], F_SETFL, O_NONBLOCK) < 0)
            exit(2);
    }

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
            srand(time(NULL) ^ getpid());
            close(ParentToRabbit[i][1]);
            close(RabbitToParent[i][0]);
            close(loggerPipeRabbit[i][0]);

            int counter = 0;
            Rabbit rabbit;
            Message msgOut;
            Message msgIn;
            msgOut.damage = 0;
            msgOut.from = i;
            msgOut.type = 0;
            msgIn.damage = 0;
            msgIn.from = 0;
            msgIn.type = 0;

            rabbit.SetName(i);

            while(rabbit.GetHealth() > 0)
            {
                msgOut.from = i;

                ////////////SEND ATTACK////////////////
                if(counter == rabbit.GetAttackRate())
                {
                    counter = 0;

                    int randomNumber = rand() % 100 + 1;
                    if(randomNumber <= 15) // generate an attack
                    {
                        msgOut.type = 0;
                        msgOut.damage = rabbit.GetStrongAttackDmg();
                    }
                    else if(randomNumber <= 75)
                    {
                        msgOut.type = 1;
                        msgOut.damage = rabbit.GetWeakAttackDmg();
                    }
                    else
                    {
                        msgOut.type = 2;
                        msgOut.damage = rabbit.GetAOEDamage();
                    }

                    write(RabbitToParent[i][1], &msgOut, sizeof(Message));

                }
                else
                {
                    counter ++;
                }

                /////////////RECEIVE ATTACK////////////
                if(read(ParentToRabbit[i][0], &msgIn, sizeof(Message)) > -1)
                {
                    rabbit.SetHealth(rabbit.GetHealth() - msgIn.damage);
                    write(loggerPipeRabbit[i][1], &msgIn, sizeof (Message));

                    //logger.Log("Rabbit " + to_string(i) + " Health: " + to_string(rabbit.GetHealth())
                    //+ " attacked from Knight: " + to_string(msgIn.from));
                }
                else
                {
                    //logger.Log("Pipe Empty.");
                    sleep(.5);
                }


                if (rabbit.GetHealth() <= 0)
                {
                    break;
                }
            }

            msgOut.from = 0; //Rabbit died
            msgOut.damage = -7; //death signal
            msgOut.type = i; //index of the rabbit
            if(write(RabbitToParent[i][1], &msgOut, sizeof(Message)) > 0){
                logger.Log(rabbit.GetName() + " has fallen!");
            };

            close(loggerPipeRabbit[i][1]);
            close(ParentToRabbit[i][0]);
            close(RabbitToParent[i][1]);
            _exit(EXIT_SUCCESS);
        }
    }


    ///////////////////////MAIN PROCESS CODE///////////////////////

    //CLOSE UNUSED ENDS MAIN PROCESS
    for(int i = 0; i < (maxKnightNum); i++)
    {
        ParentToKnight[i][0];
        KnightToParent[i][1];
    }
    for(int i = 0; i < (maxRabbitNum); i++)
    {
        ParentToRabbit[i][0];
        RabbitToParent[i][1];
    }

    //INIT A DEFAULT MESSAGE
    Message msg;
    msg.type=0;
    msg.from=0;
    msg.damage=0;


    int aliveKnights = maxKnightNum; //get the initial number of alive knights
    int aliveRabbits = maxRabbitNum; //get the initial number of alive rabbits

    int aliveKnightsArray[maxKnightNum]; //init the size of the alive knights array for bookkeeping
    int aliveRabbitsArray[maxRabbitNum];//init the size of the alive rabbits array for bookkeeping

    //INITIALIZE KNIGHT ARRAY TO KEEP TRACK OF ALIVE KNIGHTS ID's
    for(int i = 0; i < maxKnightNum; i ++)
    {
        aliveKnightsArray[i] = i;
    }
    //INITIALIZE RABBIT ARRAY TO KEEP TRACK OF ALIVE RABBITS ID's
    for(int i = 0; i < maxRabbitNum; i ++)
    {
        aliveRabbitsArray[i] = i;
    }

    //MANAGER
    while(aliveRabbits > 0 && aliveKnights > 0)
    {
        int knightIndex = 0; //index for keeping track of which knight i am reading from
        int rabbitIndex =0;//index for keeping track of which rabbit i am reading from

        //Read from the knights pipes and send it to a random rabbit
        while(knightIndex < aliveKnights)
        {
            //leep(1);
            if(aliveRabbits != 0){
                msg.type=0;
                msg.from=0;
                msg.damage=0;
                if(read(KnightToParent[knightIndex][0], &msg, sizeof (Message)) > 0 )
                {
                    if(msg.damage == -7)
                    {
                        knightIndex = 0;
                        int y = 0;
                        for(int x = 0; x < aliveKnights; x ++)
                        {
                            if(aliveKnightsArray[0] == msg.from)
                            {
                                if((y + 1) < aliveKnights)
                                {
                                    y++;
                                }
                            }

                            aliveKnightsArray[x] = aliveKnightsArray[y];
                            y++;
                        }
                        aliveKnights--;

                        if(aliveKnights == 0){
                            break;
                        }
                    }
                    else
                    {
                        //find random rabbit to send it to
                        int randomNumber = rand() % aliveRabbits;
                        int rabbitIndex = aliveRabbitsArray[randomNumber];
                        write(ParentToRabbit[rabbitIndex][1], &msg, sizeof (Message));
                    }

                    knightIndex++;
                }
            }
        }

        if(aliveKnights == 0){
            break;
        }

        //Read from the rabbits pipes and send it to a random knight
        while(rabbitIndex < aliveRabbits)
        {
            //sleep(1);
            if(aliveKnights != 0)
            {
                msg.type=0;
                msg.from=0;
                msg.damage=0;
                if(read(RabbitToParent[rabbitIndex][0], &msg, sizeof (Message)) > 0 )
                {
                    if(msg.damage == -7)
                    {
                        rabbitIndex = 0;
                        int y = 0;
                        for(int x = 0; x < aliveRabbits; x ++)
                        {
                            if(aliveRabbitsArray[0] == msg.from)
                            {
                                if((y + 1) < aliveRabbits)
                                {
                                    y++;
                                }
                            }

                            aliveRabbitsArray[x] = aliveRabbitsArray[y];
                            y++;
                        }
                        aliveRabbits--;

                        if(aliveRabbits == 0){
                            break;
                        }
                    }
                    else
                    {
                        //find random knight to send it to
                        int randomNumber = rand() % aliveKnights;
                        int knightIndex = aliveKnightsArray[randomNumber];
                        write(ParentToKnight[knightIndex][1], &msg, sizeof (Message));
                    }

                    rabbitIndex++;
                }
            }
        }
    }


    //CHECK TO SEE WHO WON THE BATTLE
    if(aliveKnights == 0 && aliveRabbits == 0)
    {
        logger.LogToBoth("both 0");
    }
    else if(aliveKnights > 0)
    {
        logger.LogToBoth("KNIGHTS WIN");
    }else{
        logger.Log("RABBITS WIN");
    }


    //SEND KILL MESSAGE TO THE LOGGING PROCESS
    sleep(1);
    msg.type = -5;
    msg.from = -5;
    msg.damage = -5;
    write(loggerPipeKnight[0][1], &msg, sizeof (Message));

    logger.CloseFile();

    //CLOSE USED ENDS (CLEANUP)
    for(int i = 0; i < (maxKnightNum); i++)
    {
        ParentToKnight[i][1];
        KnightToParent[i][0];
    }
    for(int i = 0; i < (maxRabbitNum); i++)
    {
        ParentToRabbit[i][1];
        RabbitToParent[i][0];
    }


    //KILL REMAINING ALIVE PROCESSES
    for(int i = 0; i < cids.size(); i ++)
    {
        if(kill(cids[i], SIGTERM) == -1 && errno != ESRCH){
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
    ////////////////////////////////////////////
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
