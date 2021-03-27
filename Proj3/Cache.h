///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Cache.h
//	Description:                    This is a header file for a cache.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PROJ3_CACHE_H
#define PROJ3_CACHE_H
using namespace std;

class Cache
{
private:
    int numberOfSets;
    int setSize;
    int lineSize;
    int offsetBits;
    int indexBits;
    bool writeThroughEnabled;
public:
    Cache();
    void InitCache();
    void Insert(int index, int tag);
    void EvictLRU (int index);
    bool CheckCache (int index, int tag);
    void SetPolicy(int inPolicy);
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
};


#endif //PROJ3_CACHE_H
