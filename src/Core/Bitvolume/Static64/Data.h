#pragma once

#include "Bitvolume/Static64/Utils.h"


namespace  nBitvolume
{


class  cData
{

public:

public:
enum  eDataNeighbourFlag: tByte
{
    kNone   = 0,    // 0000 0000
    kTop    = 1,    // 0000 0001
    kBot    = 2,    // 0000 0010
    kFront  = 4,    // 0000 0100
    kBack   = 8,    // 0000 1000
    kLeft   = 16,   // 0001 0000
    kRight  = 32,   // 0010 0000
};

public:
    // Construction / Destruction
    cData();
    cData( t2Byte iData );
    cData( tByte iMaterial );

public:
    // Data Manipulation Interface
    const  t2Byte&  GetDataField()                                          const;
    tByte           GetMaterialField()                                      const;
    tByte           GetNeighbourField()                                     const;
    bool            HasNeighbour( eDataNeighbourFlag iDataNeighbourFlag)    const;
    bool            IsSolid()                                               const;

    void  SetDataField( const  t2Byte&  iDataField );
    void  SetMaterialField( tByte  iMaterialField );
    void  SetNeighbourField( tByte  iNeighbourField );
    void  SetNeighbour( eDataNeighbourFlag iDataNeighbourFlag, bool iValue );

private:
    // Private Data Members
    union  uDataField
    {
        uDataField()                    : mData( t2Byte( 0 ) )          {}
        uDataField( t2Byte iData )      : mData( iData )                {}
        uDataField( tByte iMaterial )   : mData( t2Byte( iMaterial ) )  {}

        t2Byte  mData;      // Occupies 2 Bytes
        tByte   mField[2];  // Occupies 2 Bytes
    };                      // The whole union occupies 2 Bytes: First Byte is Material Field, Second Byte is Neighbour Field

    uDataField  mDataField;
};


} // namespace  nBitvolume