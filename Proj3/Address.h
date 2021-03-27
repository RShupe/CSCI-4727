///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Address.h
//	Description:                    This is header file for addresses
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PROJ3_ADDRESS_H
#define PROJ3_ADDRESS_H

#include "Cache.h"
using namespace std;

class Address
{

private:
    bool isVirtual;
    int address;
    int pageOffset;
    int pobits;
    int virtualPageNumber;
    int physicalPageNumber;
    int tlbIndex;
    int blockOffset;
    int blockOffsetBits;
    int blockIndexBits;
    int blockIndex;
    int tag;
    int dirtyBit;

public:
    Address (int inAddr);
    int GetAddress() const;

    void SetNumberPageOffsetBits(int inPOBits);
    int GetNumberPageOffsetBits() const;

    void SetNumberBlockOffsetBits(int inBlockOffset);
    int GetNumberBlockOffsetBits() const;

    void SetNumberBlockIndexBits(int inBlockIndex);
    int GetNumberBlockIndexBits() const;

    void CalculateBlockIndex();
    void SetBlockIndex(int inBlockIndex);
    int GetBlockIndex() const;

    void CalculateTag();
    void SetTag(int inTag);
    int GetTag() const;

    void CalculatePageOffset();
    void SetPageOffset(int inPageOffset);
    int GetPageOffset() const;

    void SetPhysicalPageNumber(int inBlockIndex);
    void CalculatePhysicalPageNumber();
    int GetPhysicalPageNumber() const;

    /*
    int CalculateTLBIndex();
    void SetTLBIndex(int inTLBIndex);
    int GetTLBIndex() const;
    int CalculateVirutalPageNumber();
    void SetVirutalPageNumber(int inVirutalPageNumber);
    int GetVirutalPageNumber() const;
    int CalculateDirtyBit();
    void SetDirtyBit(int inDirtyBit);
    int GetDirtyBit() const;*/
};


#endif //PROJ3_ADDRESS_H
