#pragma once


#include <cstdint>
#include <cassert>


namespace  nVolumetric {
namespace  nDynamicOctree {


typedef  uint8_t    tByte;
typedef  uint16_t   t2Byte;
typedef  uint16_t   tIndex;
typedef  int16_t    tKeyComponent;
typedef  uint16_t   tSize;
typedef  int32_t    tGlobalIndex;
typedef  uint64_t   tVolume;
typedef  uint64_t   tLargeByteSize;

typedef  uint64_t   tHashableKeySignature;
static  const  tHashableKeySignature  sgSignedKeyComponentRangeShift= 0x7FFF;

enum  eLod2N : t2Byte
{
    kLod0       = 0,
    kLod1       = 1,
    kLod2       = 2,
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

} // namespace  nDynamicOctree
} // namespace  nVolumetric

