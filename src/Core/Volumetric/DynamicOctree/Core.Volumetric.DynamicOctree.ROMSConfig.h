#pragma once


#include "Core.Volumetric.DynamicOctree.Types.h"


namespace  nVolumetric {
namespace  nDynamicOctree {


class  cROMSConfig final
{

public:
    // Construction / Destruction
    ~cROMSConfig();
    cROMSConfig(  const  eLod2N&  iMacroscopicLODGranularity,
                  const  eLod2N&  iVBO_LODGranularity,
                  const  eLod2N&  iMicroscopicLODGranularity );

public:
    // Accessors
    const  eLod2N&  MacroscopicLODGranularity()  const;
    const  eLod2N&  VBOLODGranularity()  const;
    const  eLod2N&  MicroscopicLODGranularity()  const;

private:
    // Private Member Data
    const  eLod2N  mMacroscopicLODGranularity;
    const  eLod2N  mVBO_LODGranularity;
    const  eLod2N  mMicroscopicLODGranularity;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

