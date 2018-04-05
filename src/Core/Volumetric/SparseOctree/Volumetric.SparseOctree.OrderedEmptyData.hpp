#include "Volumetric.SparseOctree.OrderedEmptyData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cOrderedEmptyData< LOD, Atomic >::~cOrderedEmptyData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cOrderedEmptyData< LOD, Atomic >::cOrderedEmptyData()
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  eSubType  cOrderedEmptyData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kEmpty;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cOrderedEmptyData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    // TODO: insert return statement here
}


template< eLod2N LOD, typename Atomic >
inline  void  cOrderedEmptyData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric
