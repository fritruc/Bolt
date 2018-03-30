#pragma once


#include "VLCROM.h"


template< uint16_t N >
class  cSparseVLCROM :
    public  cVLCROM< N >
{
public:
    // Construction / Destruction
    ~cSparseVLCROM();
    cSparseVLCROM();
    cSparseVLCROM( const cSparseVLCROM& ) = delete;

public:
    virtual  eType      Type()      const;
    virtual  eSubType   SubType()   const;

private:
    cVLCROM< N / 2 >*  mOctData[8];
};

