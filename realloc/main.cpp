#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>

int main()
{
    int arraysize = 100000;

    /*//////////VECTOR//////////////////
    std::clock_t i_start = std::clock();
    auto o_start = std::chrono::high_resolution_clock::now();
    std::vector<int> test;
    for(int i = 0; i < arraysize; i ++){
        test.push_back(i);
    }


    std::clock_t i_end = std::clock();
    auto o_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed << std::setprecision(2) << " VECTOR CPU time used: "
              << 1000.0 * (i_end - i_start) / CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(o_end-o_start).count()
              << " ms\n";
    ////////////////////////////////////

    /*////////////////REALLOC//////////////
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    int *p;

    for(int i = 1; i <= arraysize; i ++)
    {
        p = (int*)realloc(p,  i * sizeof(int));
        p[i-1]=i;
    }
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed << std::setprecision(2) << " REALLOC CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";
    //////////////////////////////////*/
    return 0;
}
