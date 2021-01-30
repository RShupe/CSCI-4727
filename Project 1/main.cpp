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
#include "Log.h"

void CheckArguments(int argc, char *argv[]);

int side1Num = 0;
int side2Num = 0;


int main(int argc, char *argv[])
{
    using namespace std;

    CheckArguments(argc, argv);

    return 0;
}

void CheckArguments(int argc, char *argv[])
{
    using namespace std;

    //check to make sure the minimum possible number of arguments is passed in, if not tell the user.
    if(argc <= 4)
    {
        Log("ERROR", "Command line arguments -m and -n are required to run this program.");
        Log("ERROR","Example, -l filename -m 4 -n 2");
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

                Log("MESSAGE", "-l found");
                try
                {
                    //try getting the string of the logfile name, if not found or null then default to 'log'
                    if (string(argv[i + 1]) != "-m" && string(argv[i + 1]) != "-n")
                    {
                        SetLogFileName(string(argv[i + 1]));
                        Log("MESSAGE", "Log file name is set to: " + string(argv[i + 1]));
                    }
                    else
                    {
                        Log("WARNING", "Log file name not found. Defaulting to log.");
                    }
                }
                catch(exception)
                {
                    Log("WARNING", "Log file name not found. Defaulting to log.");
                };
            }
            else if (string(argv[i]) == "-m") // check for the m flag and make sure the value is right
            {
                mFound = true;
                Log("MESSAGE", "-m found");

                try
                {
                    if (string(argv[i + 1]) != "-l" && string(argv[i + 1]) != "-n")
                    {
                        side1Num = stoi(string(argv[i + 1]));

                        if(side1Num < 1)
                        {
                            Log("ERROR", "-M and -N have to be 1 or greater");
                            abort();
                        }
                    }
                    else
                    {
                        Log("ERROR", "Incorrect value for M flag.");
                        Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                        Log("ERROR","Example, -l filename -m 4 -n 2");
                        abort();
                    }
                }
                catch(exception)
                {
                    Log("ERROR", "Incorrect value for M flag.");
                    Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                    Log("ERROR","Example, -l filename -m 4 -n 2");
                    abort();
                };
            }
            else if (string(argv[i]) == "-n") // check for the n flag and make sure the value is right
            {
                nFound = true;
                Log("MESSAGE", "-n found");

                try
                {
                    if (string(argv[i + 1]) != "-l" && string(argv[i + 1]) != "-m")
                    {
                        side2Num = stoi(string(argv[i + 1]));

                        if(side2Num < 1)
                        {
                            Log("ERROR", "-M and -N have to be 1 or greater");
                            abort();
                        }
                    }
                    else
                    {
                        Log("ERROR", "Incorrect value for N flag.");
                        Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                        Log("ERROR","Example, -l filename -m 4 -n 2");
                        abort();
                    }
                }
                catch(exception)
                {
                    Log("ERROR", "Incorrect value for N flag.");
                    Log("ERROR", "Command line arguments -m and -n are required to run this program.");
                    Log("ERROR","Example, -l filename -m 4 -n 2");
                    abort();
                };
            }
        }

        if(lFound == false) //if the log file is not specified. log it
        {
            Log("WARNING", "Log file name not found. Defaulting to log.");
        }

        if(!mFound || !nFound) // if m and n have not been passed in, throw an error and terminate the program.
        {
            Log("ERROR", "Arguments -m and -n are required to run this application");
            abort(); //terminate if n and m are not found
        }

        if(side1Num + side2Num < 5)
        {
            Log("ERROR", "M + N MUST be greater than or equal to 5.");
            abort(); //terminate if n and m are not found
        }

        //debugging
        Log("MESSAGE", "M: " + to_string(side1Num));
        Log("MESSAGE", "N: " + to_string(side2Num));
        Log("MESSAGE", "LOGFILE: " + logFileName);
    }


}
