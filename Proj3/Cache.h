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

class Cache
{
private:
    int numberOfSets;
    int setSize;
    int lineSize;
    bool writeThroughEnabled;
public:
    Cache();
    Cache(int inNumberOfSets, int inSetSize, int inLineSize, bool inWriteThrough);
    void Insert(int tag, int physicalPageNumber);
    void Evict ();
    void Evict (int index);
    bool CheckCache (int index);

    void SetNumberOfSets(int inNumberOfSets);
    int GetNumberOfSets() const;
    void SetSetSize(int inSetSize);
    int GetSetSize() const;
    void SetLineSize(int inLineSize);
    int GetLineSize() const;
};


#endif //PROJ3_CACHE_H
