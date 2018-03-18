#include "Bitvolume/Static64/Data.h"


namespace  nBitvolume
{

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cData::cData() :
    mDataField()
{
}


cData::cData( t2Byte iData ) :
    mDataField( iData )
{
}


cData::cData( tByte iMaterial ) :
    mDataField( iMaterial )
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------ Data Manipulation Interface


const  t2Byte&
cData::GetDataField()  const
{
    return  mDataField.mData;
}


tByte
cData::GetMaterialField()  const
{
    return  mDataField.mField[0];
}


tByte
cData::GetNeighbourField()  const
{
    return  mDataField.mField[1];
}


bool
cData::HasNeighbour( eDataNeighbourFlag iDataNeighbourFlag)  const
{
    return  bool( GetNeighbourField() & tByte( iDataNeighbourFlag ) );
}


bool
cData::IsSolid()  const
{
    return  GetMaterialField() != sgEmptyMaterial;
}


void
cData::SetDataField( const  t2Byte&  iDataField )
{
    mDataField.mData = iDataField;
}


void
cData::SetMaterialField( tByte  iMaterialField )
{
    mDataField.mField[0] = iMaterialField;
}


void
cData::SetNeighbourField( tByte  iNeighbourField )
{
    mDataField.mField[1] = iNeighbourField;
}


void
cData::SetNeighbour( eDataNeighbourFlag iDataNeighbourFlag, bool iValue )
{
    tByte neighbourField = GetNeighbourField();
    if( iValue )
        SetNeighbourField( GetNeighbourField() | iDataNeighbourFlag );
    else
        SetNeighbourField( GetNeighbourField() & !iDataNeighbourFlag );
}




} // namespace  nBitvolume