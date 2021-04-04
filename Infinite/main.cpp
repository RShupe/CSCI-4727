///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      infinite.cpp
//	Description:                    infinite loop with x number of processes
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Saturday February 20, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


int numberOfProcesses = 1;

void CheckArg(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    CheckArg(argc, argv);

    if(numberOfProcesses != 1)
    {
        int childNum;
        for(int i = 0; i < numberOfProcesses - 1; i ++)
        {
            childNum = fork(); // open a new process

            if(childNum == -1)
            {
                std::cout << "Error creating child" << std::endl;
            }
            else if (childNum == 0)
            {
                std::cout << "Child: " << i+1 << std::endl;
                while(1){}
            }
        }
    }

    std::cout << "Main Process" << std::endl;

    while(1){}

    for(int i = 0; i < numberOfProcesses; i ++)
    {
        wait(NULL);
    }


    return 0;
}

/**
 * checks to see if a number was passed in
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
        numberOfProcesses = stoi(string(argv[1]));
    }
}

