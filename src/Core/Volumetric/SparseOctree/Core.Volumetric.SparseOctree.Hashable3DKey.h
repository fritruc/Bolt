#pragma once


#include "Core.Volumetric.SparseOctree.Simple3DKey.h"
#include "Core.Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cHashable3DKey :
    public  cSimple3DKey
{

public:
    cHashable3DKey( int16_t iX, int16_t iY, int16_t iZ );
    cHashable3DKey( uint64_t iHashedSignature );

public:
    void  Set( uint64_t iHashedSignature );
    const  uint64_t&  HashedSignature()  const;

    cHashable3DKey  Top()  const;
    cHashable3DKey  Bot()  const;
    cHashable3DKey  Front()  const;
    cHashable3DKey  Back()  const;
    cHashable3DKey  Left()  const;
    cHashable3DKey  Right()  const;

private:
    void  InvalidCache()  const;
    void  UpdateHashedSignatureCache()  const;

private:
    // Private Data Members
    mutable  bool  mCacheValid;
    mutable  uint64_t  mCachedHashedSignature;

};


} // namespace  nSparseOctree
} // namespace  nVolumetric

