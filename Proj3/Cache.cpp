///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Cache.cpp
//	Description:                    This is a class to hold all the attributes of a cache.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <tuple>
#include <iostream>
#include "Cache.h"


using namespace std;

struct dataEntry
{
    int tag = -1;
    int LRUNum = -1;
};

vector<vector<dataEntry>> CacheMemory;

/**
    No arg constructor
 */
Cache::Cache()
{

};

/**
 * InitCache
 *
 * Init the cache vector to the appropriate size
 */
 void Cache::InitCache()
{
    vector<vector<dataEntry>> temp( GetNumberOfSets() , vector<dataEntry> (GetSetSize(), dataEntry()));
    CacheMemory = temp;
    for(int i = 0; i < GetNumberOfSets(); i ++)
    {
        CacheMemory[i];
    }

};

/**
 * Insert
 *
 * Inserts a tag at a spot in memory
 * @param Insert
 */
void Cache::Insert(int index, int tag)
{
    dataEntry entry;
    entry.tag = tag;
    entry.LRUNum = 0;

    for(int i = 0; i < CacheMemory[index].size(); i ++)
    {
        if(CacheMemory[index][i].LRUNum != -1){
            CacheMemory[index][i].LRUNum++;
        }
    }

    bool placed = false;
    int i = 0;
    while(placed == false && i < CacheMemory[index].size())
    {
        if(CacheMemory[index][i].tag == -1)
        {
            CacheMemory[index][i] = entry;
            placed = true;
        }else
        {
            i++;
        }
    }
    if(placed == false)
    {
        EvictLRU(index);

        int i = 0;
        while(placed == false && i < CacheMemory[index].size())
        {
            if(CacheMemory[index][i].tag == -1)
            {
                CacheMemory[index][i] = entry;
                placed = true;
            }else
            {
                i++;
            }
        }
    }
};

/**
 * Evict
 *
 * Evict at index LRU
 * @param index
 */
void Cache::EvictLRU (int index)
{
    int indexEvict, highestLRU = 0;

    for(int i = 0; i < CacheMemory[index].size(); i ++)
    {
        if(CacheMemory[index][i].LRUNum >= highestLRU)
        {
            highestLRU = CacheMemory[index][i].LRUNum;
            indexEvict = i;
        }
    }

    dataEntry entry;
    CacheMemory[index][indexEvict] = entry;
};
/**
 * CheckCache
 *
 * CheckCache for index and tag match
 * @param index
 * @param tag
 */
bool Cache::CheckCache (int index, int tag)
{
    bool found = false;

    for(int i = 0; i < CacheMemory[index].size(); i ++)
    {
        if(CacheMemory[index][i].tag == tag)
        {
            found = true;
            for(int i = 0; i < CacheMemory[index].size(); i ++)
            {
                if(CacheMemory[index][i].LRUNum != -1){
                    CacheMemory[index][i].LRUNum++;
                }
            }
            CacheMemory[index][i].LRUNum = 0;
        }
    }

    return found;
};
/**
 * SetPolicy
 *
 * sets the policy
 * @param policynumber
 */
void Cache::SetPolicy(int inPolicy)
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
void Cache::SetNumOffsetBits(int inOffset)
{
    offsetBits = inOffset;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int Cache::GetNumOffsetBits() const
{
    return offsetBits;
};
/**
 * SetIndex
 *
 * sets the Index to the int passed in
 * @param Index
 */
void Cache::SetNumIndexBits(int inIndex)
{
    indexBits = inIndex;
};
/**
 * GetIndex
 *
 * Returns the Index
 * @returns Index
 */
int Cache::GetNumIndexBits() const
{
    return indexBits;
};
/**
 * SetNumberOfSets
 *
 * sets the NumberOfSets to the int passed in
 * @param NumberOfSets
 */
void Cache::SetNumberOfSets(int inNumberOfSets)
{
    numberOfSets = inNumberOfSets;
};
/**
 * GetNumberOfSets
 *
 * Returns the NumberOfSets
 * @returns NumberOfSets
 */
int Cache::GetNumberOfSets() const
{
    return numberOfSets;
};
/**
 * SetSetSize
 *
 * sets the SetSize to the int passed in
 * @param SetSize
 */
void Cache::SetSetSize(int inSetSize)
{
    setSize = inSetSize;
};
/**
 * GetSetSize
 *
 * Returns the SetSize
 * @returns SetSize
 */
int Cache::GetSetSize() const
{
    return setSize;
};
/**
 * SetLineSize
 *
 * sets the LineSize to the int passed in
 * @param LineSize
 */
void Cache::SetLineSize(int inLineSize)
{
    lineSize = inLineSize;
};
/**
 * GetLineSize
 *
 * Returns the LineSize
 * @returns LineSize
 */
int Cache::GetLineSize() const
{
    return lineSize;
};
