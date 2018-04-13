#include "Core.Volumetric.SparseOctree.ROMSConfig.h"

#include "Core.Volumetric.SparseOctree.Utils.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


cROMSConfig::~cROMSConfig()
{
}


cROMSConfig::cROMSConfig( const  eLod2N&  iMACRO_LOD,
                          const  eLod2N&  iVBO_LOD,
                          const  eLod2N&  iMICRO_LOD ) :
    mMACRO_LOD( iMACRO_LOD ),
    mVBO_LOD( iVBO_LOD ),
    mMICRO_LOD( iMICRO_LOD )
{
    assert( mMACRO_LOD >= mVBO_LOD );
    assert( mVBO_LOD >= mMICRO_LOD );
}


const  eLod2N&
cROMSConfig::MACRO_LOD()  const
{
    return  mMACRO_LOD;
}


const  eLod2N&
cROMSConfig::VBO_LOD()  const
{
    return  mVBO_LOD;
}

const  eLod2N&
cROMSConfig::MICRO_LOD()  const
{
    return  mMICRO_LOD;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

