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

#include "L1Cache.h"
using namespace std;

class Address {

private:
    bool isVirtual;
    int address;
    int pageOffset;
    int virtualPageNumber;
    int tlbIndex;
    int l1blockIndex;
    int l2blockIndex;
    int blockIndex;
    int tag;
    int dirtyBit;

public:
    Address (int inAddr);
    Address (int inAddr, L1Cache inL1);
    Address (int inAddr, L1Cache* inL1, L1Cache *inL2);

    int CalculatePageOffset();
    void SetPageOffset(int inPageOffset);
    int GetPageOffset() const;
    int CalculateTLBIndex();
    void SetTLBIndex(int inTLBIndex);
    int GetTLBIndex() const;
    int CalculateVirutalPageNumber();
    void SetVirutalPageNumber(int inVirutalPageNumber);
    int GetVirutalPageNumber() const;
    int CalculateL1BlockIndex();
    int CalculateL2BlockIndex();
    void setL1BlockIndex(int inBlockOffset);
    int GetL1BlockIndex() const;
    void setL2BlockIndex(int inBlockOffset);
    int GetL2BlockIndex() const;
    int CalculateBlockIndex();
    void setBlockIndex(int inBlockIndex);
    int GetBlockIndex() const;
    int CalculateTag();
    void setTag(int inTag);
    int GetTag() const;
    int CalculateDirtyBit();
    void setDirtyBit(int inDirtyBit);
    int GetDirtyBit() const;
};


#endif //PROJ3_ADDRESS_H
