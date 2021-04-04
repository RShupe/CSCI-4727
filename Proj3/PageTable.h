///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      PageTable.h
//	Description:                    This is a header file for a PageTable.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Thursday April 1, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PROJ3_PageTable_H
#define PROJ3_PageTable_H
using namespace std;

class PageTable
{
private:
    int numberOfSets;
    int setSize;
    int indexBits;
    int offsetBits;
    bool Eviction;

public:
    PageTable();
    void InitPageTable(int numberOfPages);
    void Insert(int index, int physPageNumber);
    int EvictLRU ();
    bool CheckPageTable (int index);
    int GetPhysicalPageNumber(int index) const;
    void SetNumberOfSets(int inNumberOfSets);
    int GetNumberOfSets() const;

    void SetEvictionBool(bool in);
    bool GetEvictionBool() const;
};


#endif //PROJ3_PageTable_H
