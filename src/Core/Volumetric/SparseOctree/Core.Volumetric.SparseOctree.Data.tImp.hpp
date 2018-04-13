#include "Core.Volumetric.SparseOctree.Data.h"


#include "Core.Volumetric.SparseOctree.ROMSConfig.h"
#include "Core.Volumetric.SparseOctree.Utils.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline
cData<LOD,Atomic>::~cData()
{
    mROMSConfig = 0; // Non-Owning
    mParent = 0; // Non-Owning
}


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline
cData< __PARENT, __LOD, __ATOMIC >::cData( __PARENT*  iParent, const cROMSConfig * iROMSConfig, const  cSimple3DKey&  iAttributeKey ) :
    mROMSConfig( iROMSConfig ), // Non-Owning
    mParent( iParent ), // Non-Owning
    mAttributeKey( iAttributeKey )
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------ Template Data Container Accessors


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline  eLod2N
cData< __PARENT, __LOD, __ATOMIC >::Intrinsic_LOD()  const
{
    return  LOD;
}


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline  int16_t
cData< __PARENT, __LOD, __ATOMIC >::Intrinsic_LOD_Size()  const
{
    return  mLOD_Size;
}


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline  uint64_t
cData< __PARENT, __LOD, __ATOMIC >::Capacity()  const
{
    return  mCapacity;
}


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline  const  cROMSConfig&
cData< __PARENT, __LOD, __ATOMIC >::ROMSConfig()  const
{
    return  *mROMSConfig;
}


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline  const  cSimple3DKey&
cData< __PARENT, __LOD, __ATOMIC >::AttributeKey()  const
{
    return  mAttributeKey;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template<class __PARENT,eLod2N __LOD,typename __ATOMIC>
inline __ATOMIC cData<__PARENT,__LOD,__ATOMIC>::DefaultValue()
{
    return __ATOMIC( 0 );
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- Render


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline  glm::vec3
inline cData< __PARENT, __LOD, __ATOMIC >::WireFrameColor()
{
    return glm::vec3( 1.0f, 1.0f, 1.0f );
}


template< class __PARENT, eLod2N __LOD, typename __ATOMIC >
inline  void
inline cData< __PARENT, __LOD, __ATOMIC >::RenderWireFrameStructure()
{
    Utils::DirectDrawWireFrameCube( float( Intrinsic_LOD_Size ), OctDebugColor() );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

