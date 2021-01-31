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
#include "Logger.h"

void CheckArguments(int argc, char *argv[]);
void Terminate();

int side1Num = 0;   //The number of combatants for side 1;
int side2Num = 0;   //The number of combatants for side 2;
Logger logger;      //Logger object for outputting to the console and the log file.

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
    Logger();

    CheckArguments(argc, argv);

    logger.LogToFile("THIS IS A TEST");
    logger.LogToFile("MESSAGE", "This is another test.");


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

                logger.Log("MESSAGE", "-l found");
                try
                {
                    //try getting the string of the logfile name, if not found or null then default to 'log'
                    if (string(argv[i + 1]) != "-m" && string(argv[i + 1]) != "-n")
                    {
                        logger.SetLogFileName(string(argv[i + 1]));
                        logger.Log("MESSAGE", "Log file name is set to: " + string(argv[i + 1]));
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
                logger.Log("MESSAGE", "-m found");

                try
                {
                    if (string(argv[i + 1]) != "-l" && string(argv[i + 1]) != "-n")
                    {
                        side1Num = stoi(string(argv[i + 1]));

                        if(side1Num < 1)
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
                logger.Log("MESSAGE", "-n found");

                try
                {
                    if (string(argv[i + 1]) != "-l" && string(argv[i + 1]) != "-m")
                    {
                        side2Num = stoi(string(argv[i + 1]));

                        if(side2Num < 1)
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

        if(side1Num + side2Num < 5)
        {
            logger.Log("ERROR", "M + N MUST be greater than or equal to 5.");
            Terminate(); //terminate if n and m are not found
        }

        //debugging
        logger.Log("MESSAGE", "M: " + to_string(side1Num));
        logger.Log("MESSAGE", "N: " + to_string(side2Num));
        logger.Log("MESSAGE", "LOGFILE: " + logger.GetLogFileName());
    }
}
