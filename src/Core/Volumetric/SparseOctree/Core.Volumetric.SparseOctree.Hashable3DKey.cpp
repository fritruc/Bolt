#include "Core.Volumetric.SparseOctree.Hashable3DKey.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


cHashable3DKey::cHashable3DKey( int16_t iX, int16_t iY, int16_t iZ ) :
    cSimple3DKey( iX, iY, iZ ),
    mCacheValid( false ),
    mCachedHashedSignature( 0 )
{
}


cHashable3DKey::cHashable3DKey( uint64_t iHashedSignature ) :
    cSimple3DKey( 0, 0, 0 ),
    mCacheValid( true ),
    mCachedHashedSignature( iHashedSignature )
{
    Set( iHashedSignature );
}


void
cHashable3DKey::Set( uint64_t iHashedSignature )
{
    mCachedHashedSignature = iHashedSignature;
    mCacheValid = true;

    mX = int16_t( ( ( mCachedHashedSignature & uint64_t( 0x0000FFFF00000000 ) ) >> 32 ) - sgSignedKeyComponentRangeShift );
    mY = int16_t( ( ( mCachedHashedSignature & uint64_t( 0x00000000FFFF0000 ) ) >> 16 ) - sgSignedKeyComponentRangeShift );
    mZ = int16_t( (   mCachedHashedSignature & uint64_t( 0x000000000000FFFF ) )         - sgSignedKeyComponentRangeShift );
}


const  uint64_t&
cHashable3DKey::HashedSignature()  const
{
    UpdateHashedSignatureCache();
    return  mCachedHashedSignature;
}


cHashable3DKey
cHashable3DKey::Top()  const
{
    return  cHashable3DKey( mX, mY+1, mZ );
}


cHashable3DKey
cHashable3DKey::Bot()  const
{
    return  cHashable3DKey( mX, mY-1, mZ );
}


cHashable3DKey
cHashable3DKey::Front()  const
{
    return  cHashable3DKey( mX, mY, mZ-1 );
}



cHashable3DKey
cHashable3DKey::Back()  const
{
    return  cHashable3DKey( mX, mY, mZ+1 );
}



cHashable3DKey
cHashable3DKey::Left()  const
{
    return  cHashable3DKey( mX-1, mY, mZ );
}



cHashable3DKey
cHashable3DKey::Right()  const
{
    return  cHashable3DKey( mX+1, mY, mZ );
}


void
cHashable3DKey::InvalidCache()  const
{
    mCacheValid = false;
}


void
cHashable3DKey::UpdateHashedSignatureCache()  const
{
    if( mCacheValid )
        return;

    mCachedHashedSignature = uint64_t( uint64_t( mX ) + sgSignedKeyComponentRangeShift ) << 32 |
                             uint64_t( uint64_t( mY ) + sgSignedKeyComponentRangeShift ) << 16 |
                             uint64_t( uint64_t( mZ ) + sgSignedKeyComponentRangeShift );

    mCacheValid = true;
}


} // namespace  nSparseOctree
} // namespace  nVolumetric

