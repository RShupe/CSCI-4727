///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Address.cpp
//	Description:                    This is a class to hold all the attributes of an address.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 #include "Address.h"


Address::Address (int inAddr)
{
    address = inAddr;
}
Address::Address (int inAddr, L1Cache inL1)
{
    address = inAddr;
    cpyL1 = inL1;

    CalculateL1BlockIndex();
}
Address::Address (int inAddr, L1Cache inL1, L1Cache inL2)
{
    address = inAddr;
    cpyL1 = inL1;
    cpyL2 = inL2;
}
/**
 * CalculatePageOffset
 *
 * sets the PageOffset
 * @returns PageOffset

int Address::CalculatePageOffset()
{

};
/**
 * SetPageOffset
 *
 * sets the PageOffset to the int passed in
 * @param Name

void Address::SetPageOffset(int inPageOffset)
{
    pageOffset = inPageOffset;
}

/**
 * GetPageOffset
 *
 * Returns the PageOffset
 * @returns PageOffset
 *
int Address::GetPageOffset() const
{
    return pageOffset;
}
/**
 * CalculateTLBIndex
 *
 * sets the TLBIndex
 * @returns TLBIndex
 *
int Address::CalculateTLBIndex()
{

};
/**
 * SetTLBIndex
 *
 * sets the TLBIndex to the int passed in
 * @param TLBIndex
 *
void Address::SetTLBIndex(int inTLBIndex)
{
    tlbIndex = inTLBIndex;
}

/**
 * GetTLBIndex
 *
 * Returns the TLBIndex
 * @returns TLBIndex
 *
int Address::GetTLBIndex() const
{
    return tlbIndex;
}
/**
 * CalculateVirutalPageNumber
 *
 * sets the VirutalPageNumber
 * @returns VirutalPageNumber
 *
int Address::CalculateVirutalPageNumber()
{

};
/**
 * SetVirutalPageNumber
 *
 * sets the VirutalPageNumber to the int passed in
 * @param VirutalPageNumber
 *
void Address::SetVirutalPageNumber(int inVirutalPageNumber)
{
    virtualPageNumber = inVirutalPageNumber;
}

/**
 * GetVirutalPageNumber
 *
 * Returns the VirutalPageNumber
 * @returns VirutalPageNumber
 *
int Address::GetVirutalPageNumber() const
{
    return virtualPageNumber;
}
/**
 * CalculateL1BlockIndex
 *
 * sets the L1BlockIndex
 * @returns L1BlockIndex
 *
int Address::CalculateL1BlockIndex()
{
    int blockAddress = address >> cpyL1.GetNumOffsetBits();

    setL1BlockIndex((blockAddress >> 0) & ((1 << cpyL1.GetNumIndexBits())-1));
};
/**
 * CalculateL2BlockIndex
 *
 * sets the L2BlockIndex
 * @returns L2BlockIndex
 *
int Address::CalculateL2BlockIndex()
{

};
/**
 * SetL1BlockIndex
 *
 * sets the L1BlockIndex to the int passed in
 * @param L1BlockIndex
 *
void Address::setL1BlockIndex(int inBlockIndex)
{
    l1blockIndex = inBlockIndex;
}

/**
 * GetL1BlockIndex
 *
 * Returns the L1BlocIndex
 * @returns L1BlockIndex
 *
int Address::GetL1BlockIndex() const
{
    return l1blockIndex;
}
/**
 * SetL2BlockIndex
 *
 * sets the L2BlockIndex to the int passed in
 * @param L2BlockIndex
 *
void Address::setL2BlockIndex(int inBlockIndex)
{
    l2blockIndex = inBlockIndex;
}

/**
 * GetL2BlockIndex
 *
 * Returns the L2BlockIndex
 * @returns L2BlockIndex
 *
int Address::GetL2BlockIndex() const
{
    return l2blockIndex;
}
/**
 * CalculateTag
 *
 * sets the Tag
 * @returns Tag
 *
int Address::CalculateTag()
{

};
/**
 * SetTag
 *
 * sets the Tag to the int passed in
 * @param Tag
 *
void Address::setTag(int inTag)
{
    tag = inTag;
}

/**
 * GetTag
 *
 * Returns the Tag
 * @returns Tag
 *
int Address::GetTag() const
{
    return tag;
}
/**
 * CalculateDirtyBit
 *
 * sets the DirtyBit
 * @returns DirtyBit
 *
int Address::CalculateDirtyBit()
{

};

/**
 * SetDirtyBit
 *
 * sets the DirtyBit to the int passed in
 * @param DirtyBit
 *
void Address::setDirtyBit(int inDirtyBit)
{
    dirtyBit = inDirtyBit;
}

/**
 * GetDirtyBit
 *
 * Returns the DirtyBit
 * @returns DirtyBit
 *
int Address::GetDirtyBit() const
{
    return dirtyBit;
}**/