#pragma once

#include <unordered_map>

#include "Volumetric.Dynamic.Types.h"
#include "Volumetric.Dynamic.LodSparseChunk.h"
#include "Volumetric.Dynamic.HashableGlobal3DKey.h"


namespace  nVolumetric {
namespace  nDynamic {

class  cSparseMap
{

public:
    // Construction / Destruction
    ~cSparseMap();
    cSparseMap();
    cSparseMap( const  cSparseMap& ) = delete;

public:
    // Sparse Volume Information
    cHashable3DKey      KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )                                     const;
    cLodSparseChunk*  ChunkAtKey( const  cHashable3DKey&  iKey );

public:
    // Chunk cmd
    cLodSparseChunk*  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );
    void  UpdateChunkNeighbours( const  cHashable3DKey&  iKey );
    void  PurgeEmptyChunks();
    void  PurgeAllChunks();

    void  UpdateChunksVBOs();

public:
    // Wrapping Inner Data Access
    tByte   operator()( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    void    SafeSetMaterial( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, tByte iValue );

public:
    // Naive Rendering
    void  RenderVBOs( GLuint iShaderProgramID );

private:
    // Private Data Members
    std::unordered_map< tHashableKeySignature, cLodSparseChunk* > mChunks; // Owning
    int  mUseDebugColors;
};


} // namespace  nDynamic
} // namespace  nVolumetric

