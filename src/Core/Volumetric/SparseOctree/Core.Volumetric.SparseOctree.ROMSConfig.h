#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cROMSConfig final
{

public:
    // Construction / Destruction
    ~cROMSConfig();
    cROMSConfig(  const  eLod2N&  iMACRO_LOD,
                  const  eLod2N&  iVBO_LOD,
                  const  eLod2N&  iMICRO_LOD);

public:
    // Accessors
    const  eLod2N&  MACRO_LOD()  const;
    const  eLod2N&  VBO_LOD()  const;
    const  eLod2N&  MICRO_LOD()  const;

private:
    // Private Member Data
    eLod2N  mMACRO_LOD;
    eLod2N  mVBO_LOD;
    eLod2N  mMICRO_LOD;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

