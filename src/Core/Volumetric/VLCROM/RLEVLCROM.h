#pragma once


#include "EntropicVLCROM.h"


template< uint16_t N >
class  cRLEVLCROM :
    public  cEntropicVLCROM< N >
{
public:
    // Construction / Destruction
    ~cRLEVLCROM();
    cRLEVLCROM();
    cRLEVLCROM( const cRLEVLCROM& ) = delete;

public:
    virtual  eType      Type()      const;
    virtual  eSubType   SubType()   const;
};

