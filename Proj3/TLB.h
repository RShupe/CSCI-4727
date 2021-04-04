///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      TLB.h
//	Description:                    This is a header file for a TLB.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Thursday April 1, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PROJ3_TLB_H
#define PROJ3_TLB_H
using namespace std;

class TLB
{
private:
    int numberOfSets;
    int setSize;
    int indexBits;
    int offsetBits;
    bool Eviction;

public:
    TLB();
    void InitTLB();
    void Insert(int index, int tag, int physPageNumber);
    void EvictLRU (int index);
    bool CheckTLB (int index, int tag);

    void SetNumberOfSets(int inNumberOfSets);
    int GetNumberOfSets() const;
    void SetSetSize(int inSetSize);
    int GetSetSize() const;
    int GetPhysicalPage(int index, int tag);

    void SetIndexBits(int inBits);
    int GetIndexBits() const;

    void SetEvictionBool(bool in);
    bool GetEvictionBool() const;
};


#endif //PROJ3_TLB_H
