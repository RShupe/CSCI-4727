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
#include "L1Cache.h"

using namespace std;

struct dataEntry //struct to hold an lru number and the tag
{
    int tag = -1;
    int LRUNum = -1;
};

vector<vector<dataEntry>> CacheMemory;

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
     //set the initial vector size and set the entries to -1
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
void L1Cache::Insert(int index, int tag)
{
    dataEntry entry;
    entry.tag = tag;
    entry.LRUNum = 0; //set the LRU to 0 to show its the most recently used entry

    for(int i = 0; i < CacheMemory[index].size(); i ++) //increment any other entry LRU at the index by one
    {
        if(CacheMemory[index][i].LRUNum != -1){
            CacheMemory[index][i].LRUNum++;
        }
    }

    //find a place to put the entry in the cache and place it
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
    //if the cache index is full, evict the highest LRU numbered entry
    if(placed == false)
    {
        EvictLRU(index);

        //find a place to put the entry in the cache and place it
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
}

/**
 * Evict
 *
 * Evict at index LRU
 * @param index
 */
void L1Cache::EvictLRU (int index)
{
    int indexEvict, highestLRU = 0;
    //find the highest LRU in the index and remove
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

    SetEvictionBool(true);
};
/**
 * CheckCache
 *
 * CheckCache for index and tag match
 * @param index
 * @param tag
 */
bool L1Cache::CheckCache (int index, int tag)
{
    bool found = false;

    //check the cache and look for a matching tag at the index
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
 * SetOffset
 *
 * sets the Offset to the int passed in
 * @param Offset
 */
void L1Cache::SetEvictionBool(bool in)
{
    Eviction = in;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
bool L1Cache::GetEvictionBool() const
{
    return Eviction;
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
