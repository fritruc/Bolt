#pragma once


#include "OrderedVLCROM.h"


template< uint16_t N >
class  cEmptyVLCROM :
    public  cOrderedVLCROM< N >
{
public:
    // Construction / Destruction
    ~cEmptyVLCROM();
    cEmptyVLCROM();
    cEmptyVLCROM( const cEmptyVLCROM& ) = delete;

public:
    virtual  eType      Type()      const;
    virtual  eSubType   SubType()   const;
};

