#include "Volumetric.Dynamic.SparseMap.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"


static  const  glm::vec3     sgDebugColor[14] = {   glm::vec3(   237.f,  028.f,  036.f   )   /   255.f,
                                                    glm::vec3(   255.f,  127.f,  039.f   )   /   255.f,
                                                    glm::vec3(   255.f,  242.f,  000.f   )   /   255.f,
                                                    glm::vec3(   037.f,  177.f,  076.f   )   /   255.f,
                                                    glm::vec3(   000.f,  162.f,  232.f   )   /   255.f,
                                                    glm::vec3(   063.f,  072.f,  204.f   )   /   255.f,
                                                    glm::vec3(   163.f,  073.f,  164.f   )   /   255.f,
                                                    glm::vec3(   255.f,  172.f,  204.f   )   /   255.f,
                                                    glm::vec3(   255.f,  201.f,  014.f   )   /   255.f,
                                                    glm::vec3(   239.f,  228.f,  176.f   )   /   255.f,
                                                    glm::vec3(   181.f,  230.f,  029.f   )   /   255.f,
                                                    glm::vec3(   153.f,  217.f,  234.f   )   /   255.f,
                                                    glm::vec3(   112.f,  146.f,  190.f   )   /   255.f,
                                                    glm::vec3(   200.f,  191.f,  231.f   )   /   255.f };


namespace  nVolumetric {
namespace  nDynamic {


template< uint32_t N >
cSparseMap< N >::~cSparseMap()
{
    PurgeAllChunks();
}


template< uint32_t N >
cSparseMap< N >::cSparseMap() :
    mChunks(),
    mUseDebugColors( 1 )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Sparse Volume Information


template< uint32_t N >
cHashable3DKey
cSparseMap< N >::KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const
{
    tKeyComponent keyX = tKeyComponent( floor( double(iX) / double( N ) ) );
    tKeyComponent keyY = tKeyComponent( floor( double(iY) / double( N ) ) );
    tKeyComponent keyZ = tKeyComponent( floor( double(iZ) / double( N ) ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


template< uint32_t N >
bool
cSparseMap< N >::ChunkExists( const  cHashable3DKey&  iKey )  const
{
    return  ( ! ( mChunks.find( iKey.HashedSignature() ) == mChunks.end() ) );
}


template< uint32_t N >
cLodSparseChunk< N >*
cSparseMap< N >::ChunkAtKey( const  cHashable3DKey&  iKey )
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Chunk cmd


template< uint32_t N >
cLodSparseChunk< N >*
cSparseMap< N >::MkChunk( const  cHashable3DKey&  iKey )
{
    static int debugColorIndex= 0;

    if( ChunkExists( iKey ) )
        return  ChunkAtKey( iKey );

    auto chunk = new cLodSparseChunk< N >();
    chunk->SetDebugColor( sgDebugColor[debugColorIndex%14] );
    debugColorIndex++;
    mChunks.emplace( iKey.HashedSignature(), chunk );
    UpdateChunkNeighbours( iKey );
    return  chunk;
}


template< uint32_t N >
void
cSparseMap< N >::RmChunk( const  cHashable3DKey&  iKey )
{
    if( !ChunkExists( iKey ) )
        return;

    auto it = mChunks.find( iKey.HashedSignature() );
    delete  it->second;
    mChunks.erase( it );
    UpdateChunkNeighbours( iKey );
}


template< uint32_t N >
void
cSparseMap< N >::UpdateChunkNeighbours( const  cHashable3DKey&  iKey )
{
    auto chunk  = ChunkAtKey( iKey );           // can be NULL
    auto top    = ChunkAtKey( iKey.Top() );     // can be NULL
    auto bot    = ChunkAtKey( iKey.Bot() );     // can be NULL
    auto front  = ChunkAtKey( iKey.Front() );   // can be NULL
    auto back   = ChunkAtKey( iKey.Back() );    // can be NULL
    auto left   = ChunkAtKey( iKey.Left() );    // can be NULL
    auto right  = ChunkAtKey( iKey.Right() );   // can be NULL

    if( chunk )
    {
        chunk->SetNeighbour( eNF_Index::kIndexTop,     top );
        chunk->SetNeighbour( eNF_Index::kIndexBot,     bot );
        chunk->SetNeighbour( eNF_Index::kIndexFront,   front );
        chunk->SetNeighbour( eNF_Index::kIndexBack,    back );
        chunk->SetNeighbour( eNF_Index::kIndexLeft,    left );
        chunk->SetNeighbour( eNF_Index::kIndexRight,   right );
    }

    if( top )   top->SetNeighbour(      eNF_Index::kIndexBot,      chunk );
    if( bot )   bot->SetNeighbour(      eNF_Index::kIndexTop,      chunk );
    if( front ) front->SetNeighbour(    eNF_Index::kIndexBack,     chunk );
    if( back )  back->SetNeighbour(     eNF_Index::kIndexFront,    chunk );
    if( left )  left->SetNeighbour(     eNF_Index::kIndexRight,    chunk );
    if( right ) right->SetNeighbour(    eNF_Index::kIndexLeft,     chunk );
}


template< uint32_t N >
void
cSparseMap< N >::PurgeEmptyChunks()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        if( chunk->IsEmpty() ) RmChunk( cHashable3DKey( hashedKey ) );
    }
}


template< uint32_t N >
void
cSparseMap< N >::PurgeAllChunks()
{
    std::vector< cHashable3DKey > toRemove;
    toRemove.reserve( mChunks.size() );

    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        toRemove.push_back( cHashable3DKey( hashedKey ) );
    }

    for( int i = 0; i < toRemove.size(); ++i )
    {
        RmChunk( toRemove[i] );
    }
}


template< uint32_t N >
void
cSparseMap< N >::UpdateChunksVBOs()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        chunk->UpdateVBOs();
    }
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Wrapping Inner Data Access


template< uint32_t N >
tByte
cSparseMap< N >::operator()( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    auto chunk = ChunkAtKey( key );
    return  chunk->GetMaterial( dataX, dataY, dataZ );
}


template< uint32_t N >
void
cSparseMap< N >::SafeSetMaterial( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, tByte iValue )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    auto chunk = MkChunk( key );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    chunk->SetMaterial( dataX, dataY, dataZ, iValue );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Naive Rendering


template< uint32_t N >
void
cSparseMap< N >::RenderVBOs( GLuint iShaderProgramID )
{
    int location = glGetUniformLocation( iShaderProgramID, "useDebugColor" );
    glUniform1i(location, mUseDebugColors );

    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        cHashable3DKey key( hashedKey );

        glPushMatrix();
        glTranslatef( key.GetX() * 64.f, key.GetY() * 64.f, key.GetZ() * 64.f );
        chunk->DrawVBOs( iShaderProgramID );
        glPopMatrix();

    }
}

} // namespace  nDynamic
} // namespace  nVolumetric

