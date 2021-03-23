///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Cache.cpp
//	Description:                    This is a class to hold all the attributes of a cache.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Cache.h"
using namespace std;

Cache::Cache()
{

};

Cache::Cache(int inNumberOfSets, int inSetSize, int inLineSize, bool inWriteThrough)
{

};

void Cache::Insert(int tag, int physicalPageNumber)
{

};
void Cache::Evict ()
{

};
void Cache::Evict (int index)
{

};
bool Cache::CheckCache (int index)
{

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