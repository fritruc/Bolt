﻿#pragma once


#include <cstdint>
#include <cassert>


namespace  nVolumetric      {
namespace  nSparseOctree    {


typedef  uint8_t    tByte;
typedef  uint16_t   t2Byte;
typedef  uint16_t   tIndex;

typedef  uint16_t   tSize;
typedef  int32_t    tGlobalIndex;
typedef  uint64_t   tVolume;

static  const  uint64_t  sgSignedKeyComponentRangeShift= 0x7FFF;


// Level Of Detail (LOD) Enum
enum  eLod2N : uint16_t
{
    kLod4       = 4,
    kLod8       = 8,
    kLod16      = 16,
    kLod32      = 32,
    kLod64      = 64,
    kLod128     = 128,
    kLod256     = 256,
    kLod512     = 512,
    kLod1024    = 1024,
};


// Runtime Data Information Enum
enum  eDataType
{
    kEmpty,
    kFull,
    kSparse,
    kRaw
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

