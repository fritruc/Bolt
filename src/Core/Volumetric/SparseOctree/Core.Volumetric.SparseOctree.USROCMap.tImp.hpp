#include "Core.Volumetric.SparseOctree.USROCMap.h"
#include "Core.Volumetric.SparseOctree.Data.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include <SFML/OpenGL.hpp>


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::~cUSROCMap()
{
}


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::cUSROCMap() :
    mROMSConfig( cROMSConfig( Macro, VBO, Micro ) )
{
    static_assert( ( MACRO >= VBO ),   "MACRO should be Greater Than or Equal To VBO" );
    static_assert( ( VBO >= MICRO ), "VBO should be Greater Than or Equal To MICRO" );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline  __ATOMIC*
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::Data( int32_t iX, int32_t iY, int32_t iZ )
{
    // WARNING: Can crash if no chunk is present at input coordinates.
    cHashable3DKey  key = KeyForCoordinates( iX, iY, iZ );
    auto chunk = ChunkAtKey( key );
    uint16_t  dataX = iX - key.GetX() * mMacroSize;
    uint16_t  dataY = iY - key.GetY() * mMacroSize;
    uint16_t  dataZ = iZ - key.GetZ() * mMacroSize;
    return  chunk->Get( dataX, dataY, dataZ );
}


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline  void
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::Write( int32_t iX, int32_t iY, int32_t iZ, __ATOMIC iValue )
{
    cHashable3DKey  key = KeyForCoordinates( iX, iY, iZ );
    auto chunk = MkChunk( key );
    uint16_t  dataX = iX - key.GetX() * mMacroSize;
    uint16_t  dataY = iY - key.GetY() * mMacroSize;
    uint16_t  dataZ = iZ - key.GetZ() * mMacroSize;

    chunk->AnteriorReportAnalysisOnSet( iX, iY, iZ, iValue );
    chunk->Set( dataX, dataY, dataZ, iValue );
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Sparse Volume Information


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline  cHashable3DKey
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::KeyForCoordinates( int32_t iX, int32_t iY, int32_t iZ )  const
{
    int16_t keyX = iX / mMacroSize;
    int16_t keyY = iY / mMacroSize;
    int16_t keyZ = iZ / mMacroSize;
    return  cHashable3DKey( keyX, keyY, keyZ );
}


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline  tChunk*
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::ChunkAtKey( const  cHashable3DKey&  iKey )  const
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Chunk Manipulation


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline  tChunk*
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::MkChunk( const  cHashable3DKey&  iKey )
{
    auto existingChunk = ChunkAtKey( iKey );
    if( existingChunk )
        return  existingChunk;

    tChunk*  newChunk = new  tChunk( this, &mROMSConfig, iKey );
    mChunks.emplace( iKey.HashedSignature(), newChunk );
    return  newChunk;
}


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline  void
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::RmChunk( const  cHashable3DKey&  iKey )
{
    auto existingChunk = ChunkAtKey( iKey );
    if( !existingChunk )
        return;

    delete  existingChunk;
    mChunks.erase( iKey );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- VBO Related


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::BuildVBODebug()
{
    for ( auto it : mChunks )
    {
        auto chunk = it.second;
        chunk->BuildVBODebug();
    }
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- Render


template< eLod2N MACRO, eLod2N VBO, eLod2N MICRO, typename __ATOMIC >
inline  void
cUSROCMap< MACRO, VBO, MICRO, __ATOMIC >::RenderOctDebug()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        cHashable3DKey key( hashedKey );

        float sizef = static_cast< float >( mMacroSize );

        glPushMatrix();
        glTranslatef( key.GetX() * sizef, key.GetY() * sizef, key.GetZ() * sizef );
        chunk->RenderOctDebug();
        glPopMatrix();
    }
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

