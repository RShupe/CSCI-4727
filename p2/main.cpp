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
int numberOfCores = 1;
int enableNice = 0;

void CheckArg(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    CheckArg(argc, argv);


    //set the cpu cores
    cpu_set_t  mask;
    CPU_ZERO(&mask);

    for(int i = 0; i < numberOfCores; i ++)
    {
        CPU_SET(i, &mask);
    }
    sched_setaffinity(0, sizeof(mask), &mask);

    int niceNums[4] = {0,5,10,15};

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
                if(enableNice == 1)
                {
                    nice(niceNums[i+1]);
                }


                while(1){}
            }
        }
    }

    std::cout << "Main Process" << std::endl;

    if(enableNice == 1)
    {
        nice(niceNums[0]);
    }

    while(1){}

}

/**
 * checks to see if a number was passed in
 */
void CheckArg(int argc, char *argv[])
{
    using namespace std;

    if(argc <= 3)
    {
        return;
    }
    else
    {
        numberOfProcesses = stoi(string(argv[1]));
        numberOfCores = stoi(string(argv[2]));
        enableNice = stoi(string(argv[3]));
    }
}

