#pragma once


#include "EntropicVLCROM.h"


template< uint16_t N >
class  cRawVLCROM :
    public  cEntropicVLCROM< N >
{
public:
    // Construction / Destruction
    ~cRawVLCROM();
    cRawVLCROM();
    cRawVLCROM( const cRawVLCROM& ) = delete;

public:
    virtual  eType      Type()      const;
    virtual  eSubType   SubType()   const;
};

