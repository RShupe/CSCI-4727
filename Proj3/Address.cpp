///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Address.cpp
//	Description:                    This is a class to hold all the attributes of an address.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Tuesday March 23, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 #include "Address.h"


Address::Address (int inAddr)
{
    address = inAddr;
}

/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int Address::GetAddress() const
{
    return address;
}

/**
 * CalculateBlockIndex
 *
 * sets the BlockIndex
 * @returns BlockIndex
 */
void Address::CalculateBlockIndex()
{
    int blockAddress = address >> GetNumberBlockOffsetBits();

    SetBlockIndex( (blockAddress >> 0) & ((1 << GetNumberBlockIndexBits())-1));
};

/**
 * SetL1BlockIndex
 *
 * sets the L1BlockIndex to the int passed in
 * @param L1BlockIndex
 */
void Address::SetBlockIndex(int inBlockIndex)
{
    blockIndex = inBlockIndex;
}

/**
 * GetL1BlockIndex
 *
 * Returns the L1BlocIndex
 * @returns L1BlockIndex
 */
int Address::GetBlockIndex() const
{
    return blockIndex;
}
/**
 * SetL1BlockIndex
 *
 * sets the L1BlockIndex to the int passed in
 * @param L1BlockIndex
 */
void Address::SetNumberBlockOffsetBits(int inBlockOffset)
{
    blockOffsetBits = inBlockOffset;
}

/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int Address::GetNumberBlockOffsetBits() const
{
    return blockOffsetBits;
}

/**
 * SetL1BlockIndex
 *
 * sets the L1BlockIndex to the int passed in
 * @param L1BlockIndex
 */
void Address::SetNumberBlockIndexBits(int inBlockIndex)
{
    blockIndexBits = inBlockIndex;
}

/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int Address::GetNumberBlockIndexBits() const
{
    return blockIndexBits;
}

/**
 * CalculateTag
 *
 * sets the Tag
 * @returns Tag
 */
void Address::CalculateTag()
{
    SetTag(GetAddress() >> GetNumberBlockIndexBits() >> GetNumberBlockOffsetBits());
};
/**
 * SetTag
 *
 * sets the Tag to the int passed in
 * @param Tag
 */
void Address::SetTag(int inTag)
{
    tag = inTag;
}

/**
 * GetTag
 *
 * Returns the Tag
 * @returns Tag
 */
int Address::GetTag() const
{
    return tag;
}

/**
 * CalculatePageOffset
 *
 * sets the PageOffset
 * @returns PageOffset
 */
void Address::CalculatePageOffset()
{
    SetPageOffset((address >> 0) & ((1 << GetNumberPageOffsetBits())-1));
}
/**
 * SetPageOffset
 *
 * sets the PageOffset to the int passed in
 * @param PageOffset
 */
void Address::SetPageOffset(int inPageOffset)
{
    pageOffset = inPageOffset;
}
/**
 * PageOffset
 *
 * Returns the PageOffset
 * @returns PageOffset
 */
int Address::GetPageOffset() const
{
    return pageOffset;
}


/**
 * CalculatePageOffset
 *
 * sets the PageOffset
 * @returns PageOffset
 */
void Address::CalculatePhysicalPageNumber()
{
    SetPageOffset((address >> 0) & ((1 << GetNumberPageOffsetBits())-1));
}
/**
 * SetPhysicalPageNumber
 *
 * sets the PhysicalPageNumber to the int passed in
 * @param PhysicalPageNumber
 */
void Address::SetPhysicalPageNumber(int inBlockIndex)
{
    physicalPageNumber = inBlockIndex;
}

/**
 * GetOffset
 *
 * Returns the Offset
 * @returns Offset
 */
int Address::GetPhysicalPageNumber() const
{
    return physicalPageNumber;
}

/**
 * SetPageOffset
 *
 * sets the PageOffset to the int passed in
 * @param PageOffset
 */
void Address::SetNumberPageOffsetBits(int inPOffset)
{
    pobits = inPOffset;
}
/**
 * PageOffset
 *
 * Returns the PageOffset
 * @returns PageOffset
 */
int Address::GetNumberPageOffsetBits() const
{
    return pobits;
}
