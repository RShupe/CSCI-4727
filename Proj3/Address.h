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


class Address {

private:
    bool isVirtual;
    int pageOffset;
    int virtualPageNumber;
    int tlbIndex;
    int blockOffset;
    int blockIndex;
    int tag;
    int dirtyBit;

public:
    Address ();
    int CalculatePageOffset();
    void SetPageOffset(int inPageOffset);
    int GetPageOffset() const;
    int CalculateTLBIndex();
    void SetTLBIndex(int inTLBIndex);
    int GetTLBIndex() const;
    int CalculateVirutalPageNumber();
    void SetVirutalPageNumber(int inVirutalPageNumber);
    int GetVirutalPageNumber() const;
    int CalculateBlockOffset();
    void setBlockOffset(int inBlockOffset);
    int GetBlockOffset() const;
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
