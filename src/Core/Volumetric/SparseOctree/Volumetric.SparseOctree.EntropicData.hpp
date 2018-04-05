#include "Volumetric.SparseOctree.EntropicData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  eType  cEntropicData< LOD, Atomic >::Type()  const
{
    return eType::kEntropic;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric
