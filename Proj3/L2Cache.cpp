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
#include <tuple>
#include "L2Cache.h"


using namespace std;

struct dataEntry
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
tuple<int,int> L2Cache::Insert(int address)
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
        if(L2CacheMemory[IndexNum][i].tag == -1)
        {
            L2CacheMemory[IndexNum][i] = entry;
            foundSpot = true;
            break;
        }
    }
    if(!foundSpot)
    {
        //Evict LRU and try again
    }


    return make_tuple(IndexNum, Tag);
};
/**
 * Evict
 *
 * Evict LRU
 */
void L2Cache::Evict ()
{

};
/**
 * Evict
 *
 * Evict at index
 * @param index
 */
void L2Cache::Evict (int index)
{

};
/**
 * SetPolicy
 *
 * sets the policy
 * @param policynumber
 */
bool L2Cache::CheckCache (int index)
{

};
/**
 * SetPolicy
 *
 * sets the policy
 * @param policynumber
 */
void L2Cache::SetPolicy(int inPolicy)
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
