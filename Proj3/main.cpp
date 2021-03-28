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
#include <ctgmath>

#include "Address.h"
#include "L1Cache.h"
#include "L2Cache.h"

//---HEADERS------------------------------------------
void CheckArg(int argc, char *argv[]);
std::vector<std::vector<uint>> ReadAddresses(std::string fileName);
void FillConfiguration(std::string fileName);
void InsertIntoMainMemory(Address currentAddress, int physPageNumber);
void RunSimulation();
//-----------------------------------------------------

//--VARIABLES------------------------------------------
//int TLBHits;
//int TLBMisses;
//float TLBHitRatio;

//int PTHits;
//int PTMisses;
//float PTHitRatio;

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
//int PTRefs;
//int DiskRefs;

vector<vector<uint>> addresses;
vector<vector<uint>> mainMemory;

L1Cache L1;
L2Cache L2;
bool isVirtual = true;
//bool TLBEnabled;
bool L2Enabled;
bool writeAllocateAndWriteBackL1;
bool writeAllocateAndWriteBackL2;

int physPageSize;
int numPhysicalPages;
int pobitstemp;
int physPageIndexBits;
//-----------------------------------------------------

/**
 * The main method that drives the entire program
 */
int main(int argc, char *argv[])
{
    using namespace std;
    CheckArg(argc, argv); //check if 2 args exist
    RunSimulation(); //run the simulation

    int totalDCHits = DCHits + DCMisses;
    DCHitRatio = float(DCHits) / totalDCHits;

    int totalL2Hits = L2Hits + L2Misses;
    L2HitRatio = float(L2Hits) / totalL2Hits;

    int total = TotalReads + TotalWrites;
    RatioOfReads = float(TotalReads) / total;


    string statsString =
            "\nSimulation Statistics\n\n"
            "DC Hits : " + to_string(DCHits) +
            "\nDC Misses : "+ to_string(DCMisses) +
            "\nDC Hit Ratio : "+ to_string(DCHitRatio) +
            "\n\nL2 Hits : " + to_string(L2Hits) +
            "\nL2 Misses : "+ to_string(L2Misses) +
            "\nL2 Hit Ratio : "+ to_string(L2HitRatio)+
            "\n\nTotal Reads : " + to_string(TotalReads) +
            "\nTotal Writes : "+ to_string(TotalWrites) +
            "\nRatio of reads : "+ to_string(RatioOfReads) +
            "\n\nNumber of main memory references: " + to_string(MainRefs);

    cout << statsString << endl;
    return 0;
}

/**
 * The method that runs the memory simulation
 */
void RunSimulation()
{
    using namespace std;

    string header1 =
            "Virtual  Virt.  Page TLB    TLB TLB  PT   Phys        DC  DC          L2  L2  \n"
            "Address  Page # Off  Tag    Ind Res. Res. Pg # DC Tag Ind Res. L2 Tag Ind Res.\n"
            "-------- ------ ---- ------ --- ---- ---- ---- ------ --- ---- ------ --- ----";

    string header2 =
            "Physical Virt.  Page TLB    TLB TLB  PT   Phys        DC  DC          L2  L2  \n"
            "Address  Page # Off  Tag    Ind Res. Res. Pg # DC Tag Ind Res. L2 Tag Ind Res.\n"
            "-------- ------ ---- ------ --- ---- ---- ---- ------ --- ---- ------ --- ----";

    if(isVirtual) //determine which header to output
    {
        cout << header1 << endl;
    }
    else
        {
        cout << header2 << endl;

        vector<vector<uint>> temp( numPhysicalPages , vector<uint> (physPageSize / 4, 0));
        mainMemory = temp; //initialize main memory to the right size


        for(int i = 0; i < addresses.size() ; i++)
        {
            Address currentAddress(addresses[i][1]); //the current address we are working with

            if(addresses[i][0] == 1) //determine if the address is a read or a write.
            {
                TotalWrites++;
            }
            else
            {
                TotalReads++;
            }

            currentAddress.SetNumberPageOffsetBits(pobitstemp);
            currentAddress.CalculatePageOffset();
            int pageOffset = currentAddress.GetPageOffset(); //calculate page offset

            currentAddress.SetNumberPageIndexBits(physPageIndexBits);
            currentAddress.CalculatePhysicalPageNumber();
            int physPageNumber = currentAddress.GetPhysicalPageNumber(); //calculate physical page number

            //-----------L1------------
            currentAddress.SetNumberBlockOffsetBits(L1.GetNumOffsetBits());
            currentAddress.SetNumberBlockIndexBits(L1.GetNumIndexBits());
            currentAddress.CalculateBlockIndex();
            currentAddress.CalculateTag(); //calculate L1 tag

            int L1Index, L1Tag;
            L1Index = currentAddress.GetBlockIndex();
            L1Tag = currentAddress.GetTag();

            string foundInL1 = "";
            if(L1.CheckCache(currentAddress.GetBlockIndex(), currentAddress.GetTag())) //if a hit in the cache
            {
                foundInL1 = "hit";
                DCHits++;

                printf("%08x %6s %4x %6s %3s %4s %4s %4x %6x %3x %4s", currentAddress.GetAddress(), "" , pageOffset, "", "", " ", " ", physPageNumber,
                       L1Tag, L1Index, foundInL1.c_str());
            }
            else //if a miss in the cache
            {
                if(!writeAllocateAndWriteBackL1) //check if writeback is disabled
                {
                    //no write allocate / write through
                    if(addresses[i][0] == 0) // only put into cache if it is a read
                    {
                        L1.Insert(currentAddress.GetBlockIndex(), currentAddress.GetTag());
                    }
                    if(!L2Enabled) //if L2 is not enabled, insert directly into memory
                    {
                        InsertIntoMainMemory(currentAddress, physPageNumber);
                    }
                }
                else
                {
                    if(!L2Enabled)//if L2 is not enabled, insert directly into memory
                    {
                        InsertIntoMainMemory(currentAddress, physPageNumber);
                    }
                    L1.Insert(currentAddress.GetBlockIndex(), currentAddress.GetTag());
                }

                foundInL1 = "miss";
                DCMisses++;

                if(L2Enabled)
                {
                    //-------------L2------------------
                    currentAddress.SetNumberBlockOffsetBits(L2.GetNumOffsetBits());
                    currentAddress.SetNumberBlockIndexBits(L2.GetNumIndexBits());
                    currentAddress.CalculateBlockIndex();
                    currentAddress.CalculateTag();

                    int L2Index, L2Tag;
                    L2Index = currentAddress.GetBlockIndex();
                    L2Tag = currentAddress.GetTag();

                    string foundInL2 = "";
                    if(L2.CheckCache(currentAddress.GetBlockIndex(), currentAddress.GetTag())) {
                        foundInL2 = "hit";
                        L2Hits++;
                    }
                    else
                    {
                        foundInL2 = "miss";
                        L2Misses++;
                        MainRefs++;

                        if(!writeAllocateAndWriteBackL2)
                        {
                            //no write allocate
                            if(addresses[i][0] == 0)
                            {
                                L2.Insert(currentAddress.GetBlockIndex(), currentAddress.GetTag());
                            }
                            InsertIntoMainMemory(currentAddress, physPageNumber);
                        }
                        else
                        {
                            L2.Insert(currentAddress.GetBlockIndex(), currentAddress.GetTag());
                            InsertIntoMainMemory(currentAddress, physPageNumber);
                        }
                    }

                    printf("%08x %6s %4x %6s %3s %4s %4s %4x %6x %3x %4s %6x %3x %4s", currentAddress.GetAddress(), "", pageOffset, "", "", " ", " ", physPageNumber,
                           L1Tag, L1Index, foundInL1.c_str(), L2Tag, L2Index, foundInL2.c_str());
                }
                else
                {
                    MainRefs ++;
                    printf("%08x %6s %4x %6s %3s %4s %4s %4x %6x %3x %4s", currentAddress.GetAddress(), "", pageOffset, "", "", " ", " ", physPageNumber,
                           L1Tag, L1Index, foundInL1.c_str());
                }
            }

            cout << endl; //output the formatted string
        }
    }
}

/**
 * Inserts an address into main memory if it does not already exist.
 * @param currentAddress, physPageNumber
 */
void InsertIntoMainMemory(Address currentAddress, int physPageNumber)
{
    bool placed = false;
    int i = 0;
    while(placed == false && i < mainMemory[physPageNumber].size()) // loop to check if the address is already in memory
    {
        if(mainMemory[physPageNumber][i] == currentAddress.GetAddress())
        {
            placed = true;
        }else
        {
            i++;
        }
    }
    if(!placed) //if it is not, find an open spot and place it at the page number.
    {
        int i = 0;
        while(placed == false && i < mainMemory[physPageNumber].size())
        {
            if(mainMemory[physPageNumber][i] == 0)
            {
                mainMemory[physPageNumber][i] = currentAddress.GetAddress();
                placed = true;
            }else
            {
                i++;
            }
        }
    }
}



/**
 * Fills in the objects, as well as finding index and offset bits
 */
void FillConfiguration(std::string fileName)
{
    using namespace std;
    ifstream MyReadFile(fileName); //open the config file

    string text;
    while (getline (MyReadFile, text)) //while there is a line in the file
    {
        string temp;
        temp = text.substr(text.find(":") + 1);

        if(temp == "Data TLB configuration") //fill the data about the TLB configuration
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
        else if(temp == "Page Table configuration") //fill the data about the page table
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
            numPhysicalPages = stoi(temp);

            getline(MyReadFile, text);
            temp = text.substr(text.find(":") + 1);
            cout << "Each page contains " << temp << " bytes." << endl;
            physPageSize = stoi(temp);

            int offset = log2(stoi(temp));
            pobitstemp = offset;

            physPageIndexBits = index;

            cout << "Number of bits used for the index is: " << index << endl;
            cout << "Number of bits used for the page offset is: " << offset << "\n"<< endl;

        }
        else if(temp == "Data Cache configuration") //fill the data and initialize the L1
        {
            cout << "Data Cache configuration" << endl;
            L1 = L1Cache();

            getline(MyReadFile, text);
            string temp;
            temp = text.substr(text.find(":") + 1);
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            cout << "DCache contains " << temp << " sets."<< endl;
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
                writeAllocateAndWriteBackL1 = false;
            }
            else
            {
                cout << "The cache uses a write-allocate and write-back policy." << endl;
                writeAllocateAndWriteBackL1 = true;
            }

            cout << "The number of bits used for the index is: " << L1.GetNumIndexBits() << endl;
            cout << "The number of bits used for the offset is: " << L1.GetNumOffsetBits() <<  "\n" <<endl;

            L1.InitCache();
        }
        else if(temp == "L2 Cache configuration") //fill the data and initialize the L2
        {
            cout << "L2 Cache configuration" << endl;
            L2 = L2Cache();

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
                writeAllocateAndWriteBackL2 = false;
            }
            else
            {
                cout << "The cache uses a write-allocate and write-back policy." << endl;
                writeAllocateAndWriteBackL2 = true;
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
                //TLBEnabled = true;
            }
            else
            {
                cout << "TLB is disabled." <<  endl;
                //TLBEnabled = false;
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
                L2Enabled = false;
            }
            cout << "--------------------------------------------\n" << endl;

            L2.InitCache();
        }
    }
    MyReadFile.close(); //close the open file
}

/**
 * Reads in the addresses from the file and whether it is a read or a write
 * @param fileName
 */
std::vector<std::vector<uint>> ReadAddresses(std::string fileName)
{
    using namespace std;

    ifstream MyReadFile(fileName); //open the file

    int rows = count(istreambuf_iterator<char>(MyReadFile), istreambuf_iterator<char>(), '\n');
    vector<vector<uint>> addresses(rows, vector<uint> (2)); //initialize a temp 2d vector to store addresses
    ifstream MyReadFile2(fileName);
    int i = 0;

    while (getline (MyReadFile2, fileName)) {

        if(fileName[0] == 'R') //if the address is a read
        {
            addresses[i][0] = 0; //store read
            string temp(fileName.begin() + 2, fileName.end());
            uint x;
            std::stringstream ss;
            ss << std::hex << temp;
            ss >> x;
            addresses[i][1] = x; //convert and store hex string as an uint
            i++;
        }
        else if(fileName[0] == 'W') //if the address is a write
        {
            addresses[i][0] = 1; //store write
            string temp(fileName.begin() + 2, fileName.end());
            uint x;
            std::stringstream ss;
            ss << std::hex << temp;
            ss >> x;
            addresses[i][1] = x; //convert and store hex string as an uint
            i++;
        }
    }

    // Close the file
    MyReadFile2.close();
    return addresses; //return filled addresses vector
}


/**
 * checks to see if 2 file names was passed in
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
        addresses = ReadAddresses(argv[2]);
    }
}
