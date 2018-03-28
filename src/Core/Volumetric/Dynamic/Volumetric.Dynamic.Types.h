#pragma once

#include <cstdint>

namespace  nVolumetric {
namespace  nDynamic {

typedef  uint8_t    tByte;                  // 8 bits,  [0, 255]
typedef  uint16_t   t2Byte;                 // 16 bits, [0, 65535]

typedef  uint16_t   tUKeyComponent;         // 16 bits, [0, 65535]
typedef  int16_t    tKeyComponent;          // 16 bits, [−32,767, +32,767]
typedef  uint64_t   tHashableKeySignature;  // 64 bits, [0, +18,446,744,073,709,551,615]

typedef  uint8_t    tLocalDataIndex;        // 8 bits.  [0, 255]
typedef  int32_t    tGlobalDataIndex;       // 32 bits, [−2,147,483,647, +2,147,483,647]

typedef  uint32_t   tBufferDataIndex;       // 32 bits, [0, 4,294,967,295]


static  const  int  sgElementSize = sizeof( glm::vec3 );


#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif


// A small piece of documentation:
// We comply with OpenGL Right-Handed basis
// Example in world space:
// Positive X is going to the right
// Positive Y is going to the top
// Positive Z is going away from screen

enum  class  eNeighbourFace_Flag: tByte
{
    kNone   = 0,    // 0000 0000
    kRight  = 1,    // 0000 0001    // 2^0
    kLeft   = 2,    // 0000 0010    // 2^1
    kTop    = 4,    // 0000 0100    // 2^2
    kBot    = 8,    // 0000 1000    // 2^3
    kBack   = 16,   // 0001 0000    // 2^4
    kFront  = 32,   // 0010 0000    // 2^5
};

enum  class  eNeighbourFace_Index : tByte
{
    kRight  = 0,
    kLeft   = 1,
    kTop    = 2,
    kBot    = 3,
    kBack   = 4,
    kFront  = 5,
};


} // namespace  nDynamic
} // namespace  nVolumetric

