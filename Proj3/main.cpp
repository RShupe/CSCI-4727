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
#include <tgmath.h>


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
bool isVirtual = true;
bool TLBEnabled;
bool L2Enabled;


int main(int argc, char *argv[])
{
    using namespace std;
    CheckArg(argc, argv);

    string header1 =
            "Virtual  Virt.  Page TLB    TLB TLB  PT   Phys        DC  DC          L2  L2  \n"
            "Address  Page # Off  Tag    Ind Res. Res. Pg # DC Tag Ind Res. L2 Tag Ind Res.\n"
            "-------- ------ ---- ------ --- ---- ---- ---- ------ --- ---- ------ --- ----";

    string header2 =
            "Physical Virt.  Page TLB    TLB TLB  PT   Phys        DC  DC          L2  L2  \n"
            "Address  Page # Off  Tag    Ind Res. Res. Pg # DC Tag Ind Res. L2 Tag Ind Res.\n"
            "-------- ------ ---- ------ --- ---- ---- ---- ------ --- ---- ------ --- ----";

    if(isVirtual)
    {
        cout << header1 << endl;
    }else{
        cout << header2 << endl;
    }

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
            int numberOfSets = stoi(temp);;
            cout << "Data TLB contains " << temp << " sets." << endl;

            int index = log2(stoi(temp));

            getline (MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            cout << "Each set contains " << temp << " entries." << endl;
            int entries = stoi(temp);

            //tlb = TLB();


            cout << "Number of bits used for the index is " << index << ".\n" << endl;
        }
        else if(temp == "Page Table configuration")
        {
            cout << "Page Table configuration" << endl;
            getline(MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            cout << "Number of virtual pages: " << temp << endl;

            int index = log2(stoi(temp));

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            cout << "Number of physical pages: " << temp << endl;

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            cout << "Each page contains " << temp << " bytes." << endl;

            int offset = log2(stoi(temp));

            cout << "Number of bits used for the index is: " << index << endl;
            cout << "Number of bits used for the page offset is: " << offset << "\n"<< endl;

        }
        else if(temp == "Data Cache configuration")
        {
            cout << "Data Cache configuration" << endl;
            L1 = Cache();

            getline(MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "D-Cache contains " << temp << " sets."<< endl;
            L1.SetNumberOfSets(stoi(temp));

            L1.SetNumIndexBits(log2(stoi(temp)));

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each set contains " << temp << " entries."<< endl;
            L1.SetSetSize(stoi(temp));

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each line is " << temp << " bytes."<< endl;
            L1.SetLineSize(stoi(temp));

            L1.SetNumOffsetBits(log2(stoi(temp)));

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "The cache uses a write-through policy." << endl;
                L1.SetPolicy(0);
            }
            else
            {
                cout << "The cache uses a write-allocate and write-back policy." << endl;
                L1.SetPolicy(1);
            }

            cout << "The number of bits used for the index is: " << L1.GetNumIndexBits() << endl;
            cout << "The number of bits used for the offset is: " << L1.GetNumOffsetBits() <<  "\n" <<endl;
        }
        else if(temp == "L2 Cache configuration")
        {
            cout << "L2 Cache configuration" << endl;
            L2 = Cache();

            getline(MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "L2 Cache contains " << temp << " sets."<< endl;
            L2.SetNumberOfSets(stoi(temp));

            L2.SetNumIndexBits(log2(stoi(temp)));

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each set contains " << temp << " entries."<< endl;
            L2.SetSetSize(stoi(temp));

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "Each line is " << temp << " bytes."<< endl;
            L2.SetLineSize(stoi(temp));

            L2.SetNumOffsetBits(log2(stoi(temp)));

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "The cache uses a write-through policy." << endl;
                L2.SetPolicy(0);
            }
            else
            {
                cout << "The cache uses a write-allocate and write-back policy." << endl;
                L2.SetPolicy(1);
            }

            cout << "The number of bits used for the index is: " << L2.GetNumIndexBits() << endl;
            cout << "The number of bits used for the offset is: " << L2.GetNumOffsetBits() <<  "\n" <<endl;

            getline(MyReadFile, text);

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                isVirtual = true;
                cout << "The addresses read in are virtual addresses." <<  endl;
            }
            else
            {
                isVirtual = false;
                cout << "The addresses read in are physical addresses." << endl;
            }

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "TLB is enabled." <<  endl;
                TLBEnabled = true;
            }
            else
            {
                cout << "TLB is disabled." <<  endl;
                TLBEnabled = false;
            }

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            if(temp == "y")
            {
                cout << "L2 Cache is enabled." << endl;
                L2Enabled = true;
            }
            else
            {
                cout << "L2 Cache is disabled." << endl;
                L2Enabled = true;
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
