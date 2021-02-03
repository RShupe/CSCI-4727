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
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void CheckArg(int argc, char *argv[]);

std::string logFile = "";


/**
 * This is the main method that drives the program.
 */
int main(int argc, char *argv[])
{
    using namespace std;
    int value = fork();
    logFile = "the_forest";

    CheckArg(argc, argv);

    if(value == -1)
    {
        cout << "Something went wrong." << endl;
    }
    else if(value == 0)
    {
        cout << "My process ID is: " << getpid() << endl;
        cout << "and my parent's ID is: " << getppid() << endl;

        execl("Ni", "", logFile.c_str(), (char *) NULL);

        _Exit(EXIT_SUCCESS);
    }
    else
    {
        int i;
        wait(&i);
        cout << endl;
        cout << endl;
        cout << "Printing contents of the log file." << endl;
        string command = "cat -n ";
        command += logFile;
        system(command.c_str());
    }

    return 0;
}

/**
 * Checks to see if a file name argument was passed in
 */
void CheckArg(int argc, char *argv[])
{
    using namespace std;

    if(argc <= 1)
    {
        return;
    }
    else
    {
        logFile = argv[1];
    }
}

