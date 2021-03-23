///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      main.cpp
//	Description:
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "TLB.h"
#include "PageTable.h"
#include "Address.h"
#include "Cache.h"

std::string CheckArg(int argc, char *argv[]);
std::vector<std::vector<int>> ReadFileAndFillVars(std::string fileName);
void RunSimulation();

/*int TLBHits;
int TLBMisses;
float TLBHitRatio;
int PTHits;
int PTMisses;
float PTHitRatio;
int DCHits;
int DCMisses;
float DCHitRatio;
int L2Hits;
int L2Misses;
float L2HitRatio;
int TotalReads;
int TotalWrites;
float RatioOfReads;
int MainRefs;
int PTRefs;
int DiskRefs;*/

std::vector<std::vector<int>> addresses;

int main(int argc, char *argv[])
{
    using namespace std;
    string fileName = CheckArg(argc, argv);

    if(fileName == "ERROR")
    {
        _Exit(1);
    }
    addresses = ReadFileAndFillVars(fileName);

    for(int i = 0; i < 9; i++)
    {
        cout << addresses[i][0] << " ";
        stringstream stream;
        stream << hex << addresses[i][1];
        string result( stream.str() );
        cout << result << endl;
    }

    return 0;
}

void RunSimulation()
{

}

std::vector<std::vector<int>> ReadFileAndFillVars(std::string fileName)
{
    using namespace std;
    // Read from the text file
    ifstream MyReadFile(fileName);

    int rows = count(istreambuf_iterator<char>(MyReadFile), istreambuf_iterator<char>(), '\n') - 1;
    vector<vector<int>> addresses(rows, vector<int> (2));
    ifstream MyReadFile2(fileName);
    int i = 0;
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile2, fileName)) {
        // Output the text from the file
        if(fileName[0] == 'R')
        {
            addresses[i][0] = 0; //store read
            string temp(fileName.begin() + 2, fileName.end());
            int x;
            std::stringstream ss;
            ss << std::hex << temp;
            ss >> x;
            addresses[i][1] = x;
            i++;
        }
        else if(fileName[0] == 'W')
        {
            addresses[i][0] = 1; //store write
            string temp(fileName.begin() + 2, fileName.end());
            int x;
            std::stringstream ss;
            ss << std::hex << temp;
            ss >> x;
            addresses[i][1] = x;
            i++;
        }
    }

    // Close the file
    MyReadFile2.close();
    return addresses;
}


/**
 * checks to see if a file name was passed in
 */
std::string CheckArg(int argc, char *argv[])
{
    using namespace std;

    if(argc <= 1)
    {
        return "ERROR";
    }else
    {
        return string(argv[1]);
    }
}
