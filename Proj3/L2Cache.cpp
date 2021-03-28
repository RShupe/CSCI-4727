///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      L2Cache.cpp
//	Description:                    This is a class to hold all the attributes of a cache.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "L2Cache.h"


using namespace std;

struct dataEntry //struct to hold an lru number and the tag
{
    int tag = -1;
    int LRUNum = -1;
};

vector<vector<dataEntry>> L2CacheMemory;

/**
    No arg constructor
 */
L2Cache::L2Cache()
{

};

/**
 * InitCache
 *
 * Init the cache vector to the appropriate size
 */
void L2Cache::InitCache()
{
    //set the initial vector size and set the entries to -1
    vector<vector<dataEntry>> temp( GetNumberOfSets() , vector<dataEntry> (GetSetSize(), dataEntry()));
    L2CacheMemory = temp;
    for(int i = 0; i < GetNumberOfSets(); i ++)
    {
        L2CacheMemory[i];
    }

};

/**
 * Insert
 *
 * Inserts a tag at a spot in memory
 * @param Insert
 */
void L2Cache::Insert(int index, int tag)
{
    dataEntry entry;
    entry.tag = tag;
    entry.LRUNum = 0;//set the LRU to 0 to show its the most recently used entry

    for(int i = 0; i < L2CacheMemory[index].size(); i ++) //increment any other entry LRU at the index by one
    {
        if(L2CacheMemory[index][i].LRUNum != -1){
            L2CacheMemory[index][i].LRUNum++;
        }
    }
    //find a place to put the entry in the cache and place it
    bool placed = false;
    int i = 0;
    while(placed == false && i < L2CacheMemory[index].size())
    {
        if(L2CacheMemory[index][i].tag == -1)
        {
            L2CacheMemory[index][i] = entry;
            placed = true;
        }else
        {
            i++;
        }
    }
    //if the cache index is full, evict the highest LRU numbered entry
    if(placed == false)
    {
        EvictLRU(index);
        //find a place to put the entry in the cache and place it
        int i = 0;
        while(placed == false && i < L2CacheMemory[index].size())
        {
            if(L2CacheMemory[index][i].tag == -1)
            {
                L2CacheMemory[index][i] = entry;
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
void L2Cache::EvictLRU (int index)
{
    int indexEvict, highestLRU = 0;
    //find the highest LRU in the index and remove
    for(int i = 0; i < L2CacheMemory[index].size(); i ++)
    {
        if(L2CacheMemory[index][i].LRUNum >= highestLRU)
        {
            highestLRU = L2CacheMemory[index][i].LRUNum;
            indexEvict = i;
        }
    }

    dataEntry entry;
    L2CacheMemory[index][indexEvict] = entry;

    SetEvictionBool(true);
};
/**
 * CheckCache
 *
 * CheckCache for index and tag match
 * @param index
 * @param tag
 */
bool L2Cache::CheckCache (int index, int tag)
{
    bool found = false;
    //check the cache and look for a matching tag at the index
    for(int i = 0; i < L2CacheMemory[index].size(); i ++)
    {
        if(L2CacheMemory[index][i].tag == tag)
        {
            found = true;
            for(int i = 0; i < L2CacheMemory[index].size(); i ++)
            {
                if(L2CacheMemory[index][i].LRUNum != -1){
                    L2CacheMemory[index][i].LRUNum++;
                }
            }
            L2CacheMemory[index][i].LRUNum = 0;
        }
    }

    return found;
};
/**
 * SetOffset
 *
 * sets the Offset to the int passed in
 * @param Offset
 */
void L2Cache::SetNumOffsetBits(int inOffset)
{
    offsetBits = inOffset;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int L2Cache::GetNumOffsetBits() const
{
    return offsetBits;
};
/**
 * SetOffset
 *
 * sets the Offset to the int passed in
 * @param Offset
 */
void L2Cache::SetEvictionBool(bool in)
{
    Eviction = in;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
bool L2Cache::GetEvictionBool() const
{
    return Eviction;
};
/**
 * SetIndex
 *
 * sets the Index to the int passed in
 * @param Index
 */
void L2Cache::SetNumIndexBits(int inIndex)
{
    indexBits = inIndex;
};
/**
 * GetIndex
 *
 * Returns the Index
 * @returns Index
 */
int L2Cache::GetNumIndexBits() const
{
    return indexBits;
};
/**
 * SetNumberOfSets
 *
 * sets the NumberOfSets to the int passed in
 * @param NumberOfSets
 */
void L2Cache::SetNumberOfSets(int inNumberOfSets)
{
    numberOfSets = inNumberOfSets;
};
/**
 * GetNumberOfSets
 *
 * Returns the NumberOfSets
 * @returns NumberOfSets
 */
int L2Cache::GetNumberOfSets() const
{
    return numberOfSets;
};
/**
 * SetSetSize
 *
 * sets the SetSize to the int passed in
 * @param SetSize
 */
void L2Cache::SetSetSize(int inSetSize)
{
    setSize = inSetSize;
};
/**
 * GetSetSize
 *
 * Returns the SetSize
 * @returns SetSize
 */
int L2Cache::GetSetSize() const
{
    return setSize;
};
/**
 * SetLineSize
 *
 * sets the LineSize to the int passed in
 * @param LineSize
 */
void L2Cache::SetLineSize(int inLineSize)
{
    lineSize = inLineSize;
};
/**
 * GetLineSize
 *
 * Returns the LineSize
 * @returns LineSize
 */
int L2Cache::GetLineSize() const
{
    return lineSize;
};
