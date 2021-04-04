///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      L2Cache.h
//	Description:                    This is a header file for a cache.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PROJ3_L2CACHE_H
#define PROJ3_L2CACHE_H
using namespace std;

class L2Cache
{
private:
    int numberOfSets;
    int setSize;
    int lineSize;
    int offsetBits;
    int indexBits;
    int lastEvictedAddress;
    bool Eviction;

public:
    L2Cache();
    void InitCache();
    void Insert(int index, int tag);
    void EvictLRU (int index);
    bool CheckCache (int index, int tag);
    int GetNumOffsetBits() const;
    void SetNumOffsetBits(int inOffset);
    int GetNumIndexBits() const;
    void SetNumIndexBits(int inIndex);
    void SetNumberOfSets(int inNumberOfSets);
    int GetNumberOfSets() const;
    void SetSetSize(int inSetSize);
    int GetSetSize() const;
    void SetLineSize(int inLineSize);
    int GetLineSize() const;

    void SetEvictionBool(bool in);
    bool GetEvictionBool() const;
};


#endif //PROJ3_L1CACHE_H
