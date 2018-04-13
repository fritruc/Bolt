#include "Core.Volumetric.SparseOctree.Simple3DKey.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


cSimple3DKey::cSimple3DKey( int16_t iX, int16_t iY, int16_t iZ ) :
    mX( iX ),
    mY( iY ),
    mZ( iZ )
{
}


int16_t
cSimple3DKey::GetX()  const
{
    return  mX;
}


int16_t
cSimple3DKey::GetY()  const
{
    return  mY;
}


int16_t
cSimple3DKey::GetZ()  const
{
    return  mZ;
}


cSimple3DKey
cSimple3DKey::Top()  const
{
    return  cSimple3DKey( mX, mY+1, mZ );
}


cSimple3DKey
cSimple3DKey::Bot()  const
{
    return  cSimple3DKey( mX, mY-1, mZ );
}


cSimple3DKey
cSimple3DKey::Front()  const
{
    return  cSimple3DKey( mX, mY, mZ-1 );
}



cSimple3DKey
cSimple3DKey::Back()  const
{
    return  cSimple3DKey( mX, mY, mZ+1 );
}



cSimple3DKey
cSimple3DKey::Left()  const
{
    return  cSimple3DKey( mX-1, mY, mZ );
}



cSimple3DKey
cSimple3DKey::Right()  const
{
    return  cSimple3DKey( mX+1, mY, mZ );
}


} // namespace  nSparseOctree
} // namespace  nVolumetric

