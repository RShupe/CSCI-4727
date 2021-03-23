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

using namespace std;


Address::Address ()
{

}
/**
 * CalculatePageOffset
 *
 * sets the PageOffset
 * @returns PageOffset
 */
int Address::CalculatePageOffset()
{

};
/**
 * SetPageOffset
 *
 * sets the PageOffset to the int passed in
 * @param Name
 */
void Address::SetPageOffset(int inPageOffset)
{
    pageOffset = inPageOffset;
}

/**
 * GetPageOffset
 *
 * Returns the PageOffset
 * @returns PageOffset
 */
int Address::GetPageOffset() const
{
    return pageOffset;
}
/**
 * CalculateTLBIndex
 *
 * sets the TLBIndex
 * @returns TLBIndex
 */
int Address::CalculateTLBIndex()
{

};
/**
 * SetTLBIndex
 *
 * sets the TLBIndex to the int passed in
 * @param TLBIndex
 */
void Address::SetTLBIndex(int inTLBIndex)
{
    tlbIndex = inTLBIndex;
}

/**
 * GetTLBIndex
 *
 * Returns the TLBIndex
 * @returns TLBIndex
 */
int Address::GetTLBIndex() const
{
    return tlbIndex;
}
/**
 * CalculateVirutalPageNumber
 *
 * sets the VirutalPageNumber
 * @returns VirutalPageNumber
 */
int Address::CalculateVirutalPageNumber()
{

};
/**
 * SetVirutalPageNumber
 *
 * sets the VirutalPageNumber to the int passed in
 * @param VirutalPageNumber
 */
void Address::SetVirutalPageNumber(int inVirutalPageNumber)
{
    virtualPageNumber = inVirutalPageNumber;
}

/**
 * GetVirutalPageNumber
 *
 * Returns the VirutalPageNumber
 * @returns VirutalPageNumber
 */
int Address::GetVirutalPageNumber() const
{
    return virtualPageNumber;
}
/**
 * CalculateBlockOffset
 *
 * sets the BlockOffset
 * @returns BlockOffset
 */
int Address::CalculateBlockOffset()
{

};
/**
 * SetBlockOffset
 *
 * sets the BlockOffset to the int passed in
 * @param BlockOffset
 */
void Address::setBlockOffset(int inBlockOffset)
{
    blockOffset = inBlockOffset;
}

/**
 * GetBlockOffset
 *
 * Returns the BlockOffset
 * @returns BlockOffset
 */
int Address::GetBlockOffset() const
{
    return blockOffset;
}
/**
 * CalculateBlockIndex
 *
 * sets the BlockIndex
 * @returns BlockIndex
 */
int Address::CalculateBlockIndex()
{

};
/**
 * SetBlockIndex
 *
 * sets the BlockIndex to the int passed in
 * @param BlockIndex
 */
void Address::setBlockIndex(int inBlockIndex)
{
    blockIndex = inBlockIndex;
}

/**
 * GetBlockIndex
 *
 * Returns the BlockIndex
 * @returns BlockIndex
 */
int Address::GetBlockIndex() const
{
    return blockIndex;
}
/**
 * CalculateTag
 *
 * sets the Tag
 * @returns Tag
 */
int Address::CalculateTag()
{

};
/**
 * SetTag
 *
 * sets the Tag to the int passed in
 * @param Tag
 */
void Address::setTag(int inTag)
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
 * CalculateDirtyBit
 *
 * sets the DirtyBit
 * @returns DirtyBit
 */
int Address::CalculateDirtyBit()
{

};

/**
 * SetDirtyBit
 *
 * sets the DirtyBit to the int passed in
 * @param DirtyBit
 */
void Address::setDirtyBit(int inDirtyBit)
{
    dirtyBit = inDirtyBit;
}

/**
 * GetDirtyBit
 *
 * Returns the DirtyBit
 * @returns DirtyBit
 */
int Address::GetDirtyBit() const
{
    return dirtyBit;
}