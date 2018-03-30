#pragma once


#include "OrderedVLCROM.h"


template< uint16_t N >
class  cFullVLCROM :
    public  cOrderedVLCROM< N >
{
public:
    // Construction / Destruction
    ~cFullVLCROM();
    cFullVLCROM();
    cFullVLCROM( const cFullVLCROM& ) = delete;

public:
    virtual  eType      Type()      const;
    virtual  eSubType   SubType()   const;
};

