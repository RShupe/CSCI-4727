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
#include <string>


#include "TLB.h"
#include "PageTable.h"
#include "Address.h"
#include "Cache.h"

void CheckArg(int argc, char *argv[]);
std::vector<std::vector<int>> ReadFileAndFillVars(std::string fileName);
void FillConfiguration(std::string fileName);

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

TLB tlb;
PageTable pageTable;
Cache L1;
Cache L2;


int main(int argc, char *argv[])
{
    using namespace std;
    CheckArg(argc, argv);

    string header =
            "Virtual  Virt.  Page TLB    TLB TLB  PT   Phys        DC  DC          L2  L2  \n"
            "Address  Page # Off  Tag    Ind Res. Res. Pg # DC Tag Ind Res. L2 Tag Ind Res.\n"
            "-------- ------ ---- ------ --- ---- ---- ---- ------ --- ---- ------ --- ----";
    cout << header << endl;

    for(int i = 0; i < 9; i++)
    {
        //cout <<  addresses[i][0] << " ";

        int address = addresses[i][1];

        printf("%08x %6x %4x %6x %3x %4s %4s %4x %6x %3x %4s %6x %3x %4s", address, 1,2,3,4,"hit","miss",7,8,9,"hit",3,1,"miss");

        cout << endl;
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

    int rows = count(istreambuf_iterator<char>(MyReadFile), istreambuf_iterator<char>(), '\n');
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

void FillConfiguration(std::string fileName)
{
    using namespace std;
    ifstream MyReadFile(fileName);

    string text;
    while (getline (MyReadFile, text))
    {
        string temp;
        temp = text.substr(text.find(":") + 1);

        if(temp == "Data TLB configuration")
        {
            cout << "--------------------------------------------" << endl;
            cout << "Data TLB configuration" << endl;
            getline (MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            cout << "Data TLB contains " << temp << " sets." << endl;

            getline (MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            cout << "Each set contains " << temp << " entries." << endl;

            cout << "Number of bits used for the index is " << 99 << ".\n" << endl;
        }else if(temp == "Page Table configuration")
        {
            cout << "Page Table configuration" << endl;
            getline(MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            cout << "Number of virtual pages: " << temp << endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            cout << "Number of physical pages: " << temp << endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            cout << "Each page contains " << temp << " bytes." << endl;

            cout << "Number of bits used for the index is: " << 99 << endl;
            cout << "Number of bits used for the page offset is: " << 99 << "\n"<< endl;

        }else if(temp == "Data Cache configuration")
        {
            cout << "Data Cache configuration" << endl;
            getline(MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "D-Cache contains " << temp << " sets."<< endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each set contains " << temp << " entries."<< endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each line is " << temp << " bytes."<< endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "The cache uses a write-through policy.\n" << endl;
            }
            else
            {
                cout << "The cache uses a write-allocate and write-back policy.\n" << endl;
            }
        }
        else if(temp == "L2 Cache configuration")
        {
            cout << "L2 Cache configuration" << endl;
            getline(MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "L2 Cache contains " << temp << " sets."<< endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each set contains " << temp << " entries."<< endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each line is " << temp << " bytes."<< endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "The cache uses a write-through policy.\n" << endl;
            }
            else
            {
                cout << "The cache uses a write-allocate and write-back policy.\n" << endl;
            }

            getline(MyReadFile, text);

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "The addresses read in are virtual addresses." <<  endl;
            }
            else
            {
                cout << "The addresses read in are physical addresses." << endl;
            }

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "TLB is enabled." <<  endl;
            }
            else
            {
                cout << "TLB is disabled." <<  endl;
            }

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "L2 Cache is enabled." << endl;
            }
            else
            {
                cout << "L2 Cache is disabled." << endl;
            }
            cout << "--------------------------------------------\n" << endl;
        }
    }
    MyReadFile.close();
}

/**
 * checks to see if a file name was passed in
 */
void CheckArg(int argc, char *argv[])
{
    using namespace std;

    if(argc <= 2)
    {
        cout << "ERROR";
        _Exit(1);
    }
    else
    {
        FillConfiguration(argv[1]);
        addresses = ReadFileAndFillVars(argv[2]);
    }
}
