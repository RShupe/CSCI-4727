///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      L1Cache.cpp
//	Description:                    This is a class to hold all the attributes of a cache.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <tuple>
#include <iostream>
#include "L1Cache.h"


using namespace std;

struct dataEntry
{
    int tag = -1;
    int LRUNum = -1;
};

vector<vector<dataEntry>> L1CacheMemory;


/**
    No arg constructor
 */
L1Cache::L1Cache()
{

};

/**
 * InitCache
 *
 * Init the cache vector to the appropriate size
 */
 void L1Cache::InitCache()
{
    vector<vector<dataEntry>> temp( GetNumberOfSets() , vector<dataEntry> (GetSetSize(), dataEntry()));
    L1CacheMemory = temp;
    for(int i = 0; i < GetNumberOfSets(); i ++)
    {
        L1CacheMemory[i];
    }

};

/**
 * Insert
 *
 * Inserts a tag at a spot in memory
 * @param Insert
 */
tuple<int,int> L1Cache::Insert(int address)
{
    int blockAddress = address >> GetNumOffsetBits();

    int IndexNum = (blockAddress >> 0) & ((1 << GetNumIndexBits())-1);

    blockAddress = address >> GetNumOffsetBits();
    int Tag = blockAddress >> GetNumIndexBits();

    dataEntry entry;
    entry.LRUNum = 0;
    entry.tag = Tag;

    bool foundSpot = false;
    for(int i  = 0; i < GetSetSize(); i ++)
    {
        if(L1CacheMemory[IndexNum][i].tag == -1)
        {
            L1CacheMemory[IndexNum][i] = entry;
            foundSpot = true;
            break;
        }
    }
    if(!foundSpot)
    {
        std::cout << "set is full" << std::endl;
    }


    return make_tuple(IndexNum, Tag);
};
/**
 * Evict
 *
 * Evict LRU
 */
void L1Cache::Evict ()
{

};
/**
 * Evict
 *
 * Evict at index
 * @param index
 */
void L1Cache::Evict (int index)
{

};
/**
 * SetPolicy
 *
 * sets the policy
 * @param policynumber
 */
bool L1Cache::CheckCache (int index)
{

};
/**
 * SetPolicy
 *
 * sets the policy
 * @param policynumber
 */
void L1Cache::SetPolicy(int inPolicy)
{
    if(inPolicy == 0)
    {

    }else
    {

    }

};

/**
 * SetOffset
 *
 * sets the Offset to the int passed in
 * @param Offset
 */
void L1Cache::SetNumOffsetBits(int inOffset)
{
    offsetBits = inOffset;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int L1Cache::GetNumOffsetBits() const
{
    return offsetBits;
};

/**
 * SetIndex
 *
 * sets the Index to the int passed in
 * @param Index
 */
void L1Cache::SetNumIndexBits(int inIndex)
{
    indexBits = inIndex;
};
/**
 * GetIndex
 *
 * Returns the Index
 * @returns Index
 */
int L1Cache::GetNumIndexBits() const
{
    return indexBits;
};

/**
 * SetNumberOfSets
 *
 * sets the NumberOfSets to the int passed in
 * @param NumberOfSets
 */
void L1Cache::SetNumberOfSets(int inNumberOfSets)
{
    numberOfSets = inNumberOfSets;
};
/**
 * GetNumberOfSets
 *
 * Returns the NumberOfSets
 * @returns NumberOfSets
 */
int L1Cache::GetNumberOfSets() const
{
    return numberOfSets;
};
/**
 * SetSetSize
 *
 * sets the SetSize to the int passed in
 * @param SetSize
 */
void L1Cache::SetSetSize(int inSetSize)
{
    setSize = inSetSize;
};
/**
 * GetSetSize
 *
 * Returns the SetSize
 * @returns SetSize
 */
int L1Cache::GetSetSize() const
{
    return setSize;
};
/**
 * SetLineSize
 *
 * sets the LineSize to the int passed in
 * @param LineSize
 */
void L1Cache::SetLineSize(int inLineSize)
{
    lineSize = inLineSize;
};
/**
 * GetLineSize
 *
 * Returns the LineSize
 * @returns LineSize
 */
int L1Cache::GetLineSize() const
{
    return lineSize;
};
