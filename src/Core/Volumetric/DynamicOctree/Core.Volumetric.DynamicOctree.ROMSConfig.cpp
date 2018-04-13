#include "Core.Volumetric.DynamicOctree.ROMSConfig.h"


namespace  nVolumetric {
namespace  nDynamicOctree {


cROMSConfig::~cROMSConfig()
{
}


cROMSConfig::cROMSConfig( const  eLod2N&  iMacroscopicLODGranularity,
                          const  eLod2N&  iVBO_LODGranularity,
                          const  eLod2N&  iMicroscopicLODGranularity ) :
    mMacroscopicLODGranularity( iMacroscopicLODGranularity ),
    mVBO_LODGranularity( iVBO_LODGranularity ),
    mMicroscopicLODGranularity( iMicroscopicLODGranularity )
{
    assert( mMacroscopicLODGranularity >= mVBO_LODGranularity );
    assert( mVBO_LODGranularity >= mMicroscopicLODGranularity );
}


const  eLod2N&
cROMSConfig::MacroscopicLODGranularity()  const
{
    return  mMacroscopicLODGranularity;
}


const  eLod2N&
cROMSConfig::VBOLODGranularity()  const
{
    return  mVBO_LODGranularity;
}


const  eLod2N&
cROMSConfig::MicroscopicLODGranularity()  const
{
    return  mMicroscopicLODGranularity;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

