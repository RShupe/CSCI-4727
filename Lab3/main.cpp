#include <iostream>
#include <unistd.h>
#include <chrono>

void CheckArgs(int argc, char* argv[]);

int memory;
int argTime;

int main(int argc, char *argv[])
{
    using namespace std;
    using namespace chrono;
    using ClockType = std::chrono::system_clock;

    CheckArgs(argc, argv);

    memory = memory * 2097152;
    memory = memory / 4;

    int *memoryArray = malloc(5 * sizeof *memory);


    int i = 0;
    for (auto start = steady_clock::now(), now = start; now < start + seconds{argTime}; now = steady_clock::now())
    {
        memoryArray[i] = 2147483647;
        i++;
    }


    return 0;
}

/**
 * checks to see if a file name was passed in
 */
void CheckArgs(int argc, char *argv[])
{
    using namespace std;

    if(argc <= 2)
    {
        _Exit(1);
    }else
    {
         memory = strtol(argv[1], nullptr, 0);
         argTime = strtol(argv[2], nullptr, 0);
    }
}
