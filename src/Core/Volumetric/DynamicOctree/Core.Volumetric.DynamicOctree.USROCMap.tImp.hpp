#include "Core.Volumetric.SparseOctree.USROCMap.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include <SFML/OpenGL.hpp>


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< typename __AtomicType >
inline
cUSROCMap< __AtomicType >::~cUSROCMap()
{
}


template< typename __AtomicType >
inline
cUSROCMap< __AtomicType >::cUSROCMap( const  cROMSConfig& iROMSConfig ) :
    mROMSConfig( iROMSConfig ),
    mChunks()
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< typename __AtomicType >
inline  __AtomicType*
cUSROCMap< __AtomicType >::Data( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    auto chunk = ChunkAtKey( key );
    tIndex  dataX = tIndex( tIndex( iX ) - key.GetX() * tSize( Macro ) );
    tIndex  dataY = tIndex( tIndex( iY ) - key.GetY() * tSize( Macro ) );
    tIndex  dataZ = tIndex( tIndex( iZ ) - key.GetZ() * tSize( Macro ) );
    return  chunk->Get( dataX, dataY, dataZ );
}


template< typename __AtomicType >
inline  void
cUSROCMap< __AtomicType >::Write( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ, const  __AtomicType& iValue )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    auto chunk = MkChunk( key );
    tIndex dataX = tIndex( tIndex( iX ) - key.GetX() * tSize( Macro ) );
    tIndex dataY = tIndex( tIndex( iY ) - key.GetY() * tSize( Macro ) );
    tIndex dataZ = tIndex( tIndex( iZ ) - key.GetZ() * tSize( Macro ) );
    chunk->Set( dataX, dataY, dataZ, iValue );
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Sparse Volume Information


template< typename __AtomicType >
inline  cHashable3DKey
cUSROCMap< Macro, VBO, Micro, Atomic >::KeyForIndices( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ)  const
{
    double  size = double( Macro );
    tKeyComponent keyX = tKeyComponent( floor( iX / size ) );
    tKeyComponent keyY = tKeyComponent( floor( iY / size ) );
    tKeyComponent keyZ = tKeyComponent( floor( iZ / size ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


template< typename __AtomicType >
inline  bool
cUSROCMap< Macro, VBO, Micro, Atomic >::ChunkExists( const  cHashable3DKey&  iKey )  const
{
    return  ( ! ( mChunks.find( iKey.HashedSignature() ) == mChunks.end() ) );
}


template< typename __AtomicType >
inline  cROMSChunk< Macro, Atomic >*
cUSROCMap< Macro, VBO, Micro, Atomic >::ChunkAtKey( const  cHashable3DKey&  iKey )  const
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Chunk Manipulation


template< typename __AtomicType >
inline  cROMSChunk< Macro, Atomic >*
cUSROCMap< Macro, VBO, Micro, Atomic >::MkChunk( const  cHashable3DKey&  iKey )
{
    if( ChunkExists( iKey ) )
        return  ChunkAtKey( iKey );

    cRootROMSChunk< Macro, VBO, Micro, Atomic >*  chunk = new  cRootROMSChunk< Macro, VBO, Micro, Atomic >( this, &mROMSConfig, eType::kEmpty, Atomic( 0 ) );
    mChunks.emplace( iKey.HashedSignature(), chunk );
    return  chunk;
}


template< typename __AtomicType >
inline  void
cUSROCMap< Macro, VBO, Micro, Atomic >::RmChunk( const  cHashable3DKey&  iKey )
{
    if( !ChunkExists( iKey ) )
        return;

    auto it = mChunks.find( iKey.HashedSignature() );
    delete  it->second;
    mChunks.erase( it );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- VBO Related


template< typename __AtomicType >
inline  void  cUSROCMap< __AtomicType >::BuildVBODebug()
{
    for ( auto it : mChunks )
    {
        auto chunk = it.second;
        chunk->BuildVBODebug();
    }
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- Render


template< typename __AtomicType >
inline  void
cUSROCMap< __AtomicType >::RenderOctDebug()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        cHashable3DKey key( hashedKey );

        float sizef = float( Macro );

        glPushMatrix();
        glTranslatef( key.GetX() * sizef, key.GetY() * sizef, key.GetZ() * sizef );
        chunk->RenderOctDebug();
        glPopMatrix();
    }
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

