///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      TLB.cpp
//	Description:                    This is a class to hold all the attributes of a TLB.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Thursday April 1, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "TLB.h"

using namespace std;

struct TLBdataEntry //struct to hold an lru number and the tag
{
    int tag = -1;
    int LRUNum = -1;
    int physTLBdataEntryNumber = -1;
};

vector<vector<TLBdataEntry>> TLBMemory;

/**
    No arg constructor
 */
TLB::TLB()
{

};

/**
 * InitTLB
 *
 * Init the TLB vector to the appropriate size
 */
void TLB::InitTLB()
{
    //set the initial vector size and set the entries to -1
    vector<vector<TLBdataEntry>> temp(GetNumberOfSets() , vector<TLBdataEntry> (GetSetSize(), TLBdataEntry()));
    TLBMemory = temp;
    for(int i = 0; i < GetNumberOfSets(); i ++)
    {
        TLBMemory[i];
    }

};

/**
 * Insert
 *
 * Inserts a tag at a spot in memory
 * @param Insert
 */
void TLB::Insert(int index, int tag, int physTLBdataEntryNumber)
{
    TLBdataEntry entry;
    entry.tag = tag;
    entry.LRUNum = 0; //set the LRU to 0 to show its the most recently used entry
    entry.physTLBdataEntryNumber = physTLBdataEntryNumber;

    for(int i = 0; i < TLBMemory[index].size(); i ++) //increment any other entry LRU at the index by one
    {
        if(TLBMemory[index][i].LRUNum != -1){
            TLBMemory[index][i].LRUNum++;
        }
    }

    //find a place to put the entry in the TLB and place it
    bool placed = false;
    int i = 0;
    while(placed == false && i < TLBMemory[index].size())
    {
        if(TLBMemory[index][i].tag == -1)
        {
            TLBMemory[index][i] = entry;
            placed = true;
        }else
        {
            i++;
        }
    }
    //if the TLB index is full, evict the highest LRU numbered entry
    if(placed == false)
    {
        EvictLRU(index);

        //find a place to put the entry in the TLB and place it
        int i = 0;
        while(placed == false && i < TLBMemory[index].size())
        {
            if(TLBMemory[index][i].tag == -1)
            {
                TLBMemory[index][i] = entry;
                placed = true;
            }else
            {
                i++;
            }
        }
    }
}

/**
 * Evict
 *
 * Evict at index LRU
 * @param index
 */
void TLB::EvictLRU (int index)
{
    int indexEvict, highestLRU = 0;
    //find the highest LRU in the index and remove
    for(int i = 0; i < TLBMemory[index].size(); i ++)
    {
        if(TLBMemory[index][i].LRUNum >= highestLRU)
        {
            highestLRU = TLBMemory[index][i].LRUNum;
            indexEvict = i;
        }
    }

    TLBdataEntry entry;
    TLBMemory[index][indexEvict] = entry;

    SetEvictionBool(true);
};
/**
 * CheckTLB
 *
 * CheckTLB for index and tag match
 * @param index
 * @param tag
 */
bool TLB::CheckTLB (int index, int tag)
{
    bool found = false;

    //check the TLB and look for a matching tag at the index
    for(int i = 0; i < TLBMemory[index].size(); i ++)
    {
        if(TLBMemory[index][i].tag == tag)
        {
            found = true;
            for(int i = 0; i < TLBMemory[index].size(); i ++)
            {
                if(TLBMemory[index][i].LRUNum != -1){
                    TLBMemory[index][i].LRUNum++;
                }
            }
            TLBMemory[index][i].LRUNum = 0;
        }
    }

    return found;
};

void TLB::SetEvictionBool(bool in)
{
    Eviction = in;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
bool TLB::GetEvictionBool() const
{
    return Eviction;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int TLB::GetPhysicalPage(int index, int tag)
{
    int temp = 0;
    for(int i = 0; i < TLBMemory[index].size(); i ++)
    {
        if(TLBMemory[index][i].tag == tag)
        {
            temp = TLBMemory[index][i].physTLBdataEntryNumber;
        }
    }
    return temp;
}

/**
 * SetNumberOfSets
 *
 * sets the NumberOfSets to the int passed in
 * @param NumberOfSets
 */
void TLB::SetNumberOfSets(int inNumberOfSets)
{
    numberOfSets = inNumberOfSets;
};
/**
 * GetNumberOfSets
 *
 * Returns the NumberOfSets
 * @returns NumberOfSets
 */
int TLB::GetNumberOfSets() const
{
    return numberOfSets;
};
/**
 * SetSetSize
 *
 * sets the SetSize to the int passed in
 * @param SetSize
 */
void TLB::SetSetSize(int inSetSize)
{
    setSize = inSetSize;
};
/**
 * GetSetSize
 *
 * Returns the SetSize
 * @returns SetSize
 */
int TLB::GetSetSize() const
{
    return setSize;
};

/**
 * SetIndexBits
 *
 * sets the IndexBits to the int passed in
 * @param IndexBits
 */
void TLB::SetIndexBits(int inBits)
{
    indexBits = inBits;
};
/**
 * GetIndexBits
 *
 * Returns the IndexBits
 * @returns IndexBits
 */
int TLB::GetIndexBits() const
{
    return indexBits;
};