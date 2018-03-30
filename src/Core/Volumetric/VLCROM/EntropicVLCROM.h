#pragma once


#include "VLCROM.h"


template< uint16_t N >
class  cEntropicVLCROM :
    public  cVLCROM< N >
{
public:
    // Construction / Destruction
    ~cEntropicVLCROM();
    cEntropicVLCROM();
    cEntropicVLCROM( const cEntropicVLCROM& ) = delete;

public:
    virtual  eType      Type()      const;
    virtual  eSubType   SubType()   const;
};

