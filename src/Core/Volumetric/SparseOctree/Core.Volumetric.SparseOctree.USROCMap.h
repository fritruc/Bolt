#pragma once


#include <unordered_map>


#include "Core.Volumetric.SparseOctree.Types.h"
#include "Core.Volumetric.SparseOctree.Hashable3DKey.h"
#include "Core.Volumetric.SparseOctree.ROMSConfig.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< class __PARENT, eLod2N __INTRINSIC_LOD, typename __ATOMIC >
class  cData;


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
class  cUSROCMap final
{
private:
    // Macro Data Chunk Typedef
    typedef  cData< cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >, MACRO, __ATOMIC >  tChunk;

public:
    // Construction / Destruction
    ~cUSROCMap();
    cUSROCMap();
    cUSROCMap( const  cUSROCMap& ) = delete; // Not-Allowed

public:
    // Accessors
    __ATOMIC*   Data( int32_t iX, int32_t iY, int32_t iZ );
    void        Write( int32_t iX, int32_t iY, int32_t iZ, __ATOMIC iValue );

private:
    // Sparse Volume Information
    cHashable3DKey  KeyForCoordinates( int32_t iX, int32_t iY, int32_t iZ )  const;
    tChunk*         ChunkAtKey( const  cHashable3DKey&  iKey )  const;

private:
    // Chunk Manipulation
    tChunk* MkChunk( const  cHashable3DKey&  iKey );
    void    RmChunk( const  cHashable3DKey&  iKey );

public:
    // VBO Related
    void  BuildVBODebug();

public:
    // Render
    void  RenderOctDebug();

private:
    // Private Member Data
    const  int16_t  mMACRO_Size = static_cast< int16_t >( MACRO );
    const  cROMSConfig  mROMSConfig; // Owning
    std::unordered_map< uint64_t, tChunk* >  mChunks; // Owning

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.USROCMap.tImp.hpp"

