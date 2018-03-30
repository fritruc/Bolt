#pragma once


#include "VLCROM.h"


template< uint16_t N >
class  cOrderedVLCROM :
    public  cVLCROM< N >
{
public:
    // Construction / Destruction
    ~cOrderedVLCROM();
    cOrderedVLCROM();
    cOrderedVLCROM( const cOrderedVLCROM& ) = delete;

public:
    virtual  eType      Type()      const;
    virtual  eSubType   SubType()   const;
};

