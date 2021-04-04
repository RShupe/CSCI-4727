///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Lab2.cpp
//	Description:                    Knights of Ni, Processes
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday February 2, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sys/wait.h>
#include <stdlib.h>
#include "Logger.h"

void CheckArg(int argc, char *argv[]);

Logger logger;

/**
 * This is the main method that drives the program.
 */
int main(int argc, char *argv[])
{
    using namespace std;

    string userInput;

    logger.SetLogFileName("the_forest");

    CheckArg(argc, argv);

    logger.OpenFile();

    logger.LogToBoth("MESSAGE", "It is I! A Knight Who Says Ni.");
    logger.LogToBoth("MESSAGE", "What do you wish to say?");
    cout << "Say: ";
    cin >> userInput;
    logger.LogToFile("User said: " + userInput);

    for(int i = 0; i < 5; i++)
    {
        logger.LogToBoth("MESSAGE", "Ni!");
    }

    logger.LogToBoth("MESSAGE", "I demand a shubbery!");

    logger.LogToBoth("MESSAGE", "Output to: " + logger.GetLogFileName());

    logger.CloseFile();
    return 0;
}

/**
 * checks to see if a file name was passed in
 */
void CheckArg(int argc, char *argv[])
{
    using namespace std;

    if(argc <= 1)
    {
        return;
    }else
    {
        string temp = string(argv[1]);
        logger.SetLogFileName(temp);
    }
}
