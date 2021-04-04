///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      PageTable.cpp
//	Description:                    This is a class to hold all the attributes of a PageTable.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Thursday April 1, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "PageTable.h"

using namespace std;

struct Page //struct to hold an lru number and the tag
{
    int physPageNumber = -1;
    int LRUNum = -1;
};

vector<Page> PageTableMemory;

/**
    No arg constructor
 */
PageTable::PageTable()
{

};

/**
 * InitPageTable
 *
 * Init the PageTable vector to the appropriate size
 */
void PageTable::InitPageTable(int numberOfPages)
{
    //set the initial vector size and set the entries to -1
    vector<Page> temp(numberOfPages , Page());
    PageTableMemory = temp;

    for(int i = 0; i < numberOfPages; i ++)
    {
        PageTableMemory[i];
    }

};

/**
 * Insert
 *
 * Inserts a tag at a spot in memory
 * @param Insert
 */
void PageTable::Insert(int index, int physPageNumber)
{
    Page entry;
    entry.LRUNum = 0; //set the LRU to 0 to show its the most recently used entry
    entry.physPageNumber = physPageNumber;

    PageTableMemory[index] = entry;

    for(int i = 0; i < PageTableMemory.size(); i ++) //increment any other entry LRU at the index by one
    {
        if(PageTableMemory[i].LRUNum != -1 && i != index){
            PageTableMemory[i].LRUNum++;
        }
    }
}

/**
 * Evict
 *
 * Evict at index LRU
 * @param index
 */
int PageTable::EvictLRU()
{
    int index, physPageNumberEvicted, highestLRU = 0;
    //find the highest LRU in the index and remove
    for(int i = 0; i < PageTableMemory.size(); i ++)
    {
        if(PageTableMemory[i].LRUNum >= highestLRU)
        {
            highestLRU = PageTableMemory[i].LRUNum;
            physPageNumberEvicted = PageTableMemory[i].physPageNumber;
        }
    }

    Page entry;
    PageTableMemory[index] = entry;
    SetEvictionBool(true);

    return physPageNumberEvicted;
}
/**
 * CheckPageTable
 *
 * CheckPageTable for index and tag match
 * @param index
 * @param tag
 */
bool PageTable::CheckPageTable(int index)
{
    bool found = false;

    //check the PageTable and look for a matching tag at the index
    for(int i = 0; i < PageTableMemory.size(); i ++)
    {
        if(PageTableMemory[index].physPageNumber != -1)
        {
            found = true;
            for(int i = 0; i < PageTableMemory.size(); i ++)
            {
                if(PageTableMemory[index].LRUNum != -1){
                    PageTableMemory[index].LRUNum++;
                }
            }
            PageTableMemory[index].LRUNum = 0;
        }
    }
    return found;
};

/**
 * GetPhysicalPageAtIndex
 *
 * Returns the GetPhysicalPageAtIndex
 * @returns GetPhysicalPageAtIndex
 */
int PageTable::GetPhysicalPageNumber(int index) const
{
    return PageTableMemory[index].physPageNumber;
};

void PageTable::SetEvictionBool(bool in)
{
    Eviction = in;
};
/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
bool PageTable::GetEvictionBool() const
{
    return Eviction;
};
/**
 * SetNumberOfSets
 *
 * sets the NumberOfSets to the int passed in
 * @param NumberOfSets
 */
void PageTable::SetNumberOfSets(int inNumberOfSets)
{
    numberOfSets = inNumberOfSets;
};
/**
 * GetNumberOfSets
 *
 * Returns the NumberOfSets
 * @returns NumberOfSets
 */
int PageTable::GetNumberOfSets() const
{
    return numberOfSets;
};
