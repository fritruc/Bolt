#pragma once


#include <unordered_map>


#include "Core.Volumetric.DynamicOctree.Types.h"
#include "Core.Volumetric.DynamicOctree.Hashable3DKey.h"
#include "Core.Volumetric.DynamicOctree.RootROMSChunk.h"
#include "Core.Volumetric.DynamicOctree.ROMSConfig.h"


namespace  nVolumetric {
namespace  nDynamicOctree {


template< typename __AtomicType >
class  cUSROCMap final
{

public:
    // Construction / Destruction
    ~cUSROCMap();
    cUSROCMap( const  cROMSConfig& iROMSConfig );
    cUSROCMap( const  cUSROCMap& ) = delete;

public:
    // Accessors
    __AtomicType*  Data( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ );
    void  Write( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ, const  __AtomicType&  iValue );

private:
    // Sparse Volume Information
    cHashable3DKey      KeyForIndices( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )  const;
    cROMSChunk< Macro, Atomic >*  ChunkAtKey( const  cHashable3DKey&  iKey )  const;

private:
    // Chunk Manipulation
    cROMSChunk< Macro, Atomic >*  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );

public:
    // VBO Related
    void  BuildVBODebug();

public:
    // Render
    void  RenderOctDebug();

private:
    // Private Member Data
    const  cROMSConfig  mROMSConfig; // Owning
    std::unordered_map< tHashableKeySignature, cRootROMSChunk< Macro, VBO, Micro, Atomic >* >  mChunks; // Owning

};


} // namespace  nDynamicOctree
} // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.USROCMap.tImp.hpp"

