#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cHashable3DKey;


class  cSimple3DKey
{

public:
    cSimple3DKey( int16_t iX, int16_t iY, int16_t iZ );

public:
    int16_t  GetX()  const;
    int16_t  GetY()  const;
    int16_t  GetZ()  const;

    cSimple3DKey  Top()  const;
    cSimple3DKey  Bot()  const;
    cSimple3DKey  Front()  const;
    cSimple3DKey  Back()  const;
    cSimple3DKey  Left()  const;
    cSimple3DKey  Right()  const;

protected:
    // Private Data Members
    int16_t  mX;
    int16_t  mY;
    int16_t  mZ;
};


} // namespace  nSparseOctree
} // namespace  nVolumetric

