#pragma once


#include <cstdint>


template< uint16_t N >
class  cVLCROM
{

enum  eType
{
    kOrdered,
    kSparse,
    kEntropic
}

enum  eSubType
{
    kFull,
    kEmpty,

    kNone,

    kRaw,
    kRLE,
}

public:
    // Construction / Destruction
    ~cVLCROM();
    cVLCROM();
    cVLCROM( const cVLCROM& ) = delete;

public:
    virtual  eType      Type()      const  = 0;
    virtual  eSubType   SubType()   const  = 0;

private:
    const  uint32_t  mCapacity = N * N * N;
};

