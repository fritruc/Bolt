#include "Volumetric.Dynamic.LodSparseChunk.h"


#include "Volumetric.Dynamic.Utils.h"


namespace  nVolumetric {
namespace  nDynamic {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< uint32_t N >
cLodSparseChunk< N >::~cLodSparseChunk()
{
    DestroyVBOs();
}


template< uint32_t N >
cLodSparseChunk< N >::cLodSparseChunk() :
    mOccupiedVolume( 0 ),
    mNVerticesVBOElem( 0 ),
    mDebugColor( sf::Vector3f() )
{
    InitVBOs();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Volume Information


template< uint32_t N >
uint16_t
cLodSparseChunk< N >::Size()  const
{
    return  N;
}


template< uint32_t N >
uint32_t
cLodSparseChunk< N >::Capacity()  const
{
    return  mCapacity;
}


template< uint32_t N >
uint32_t
cLodSparseChunk< N >::OccupiedVolume()  const
{
    return  mOccupiedVolume;
}


template< uint32_t N >
bool
cLodSparseChunk< N >::IsFull()  const
{
    return  mOccupiedVolume == mCapacity;
}


template< uint32_t N >
bool
cLodSparseChunk< N >::IsEmpty()  const
{
    return  mOccupiedVolume == 0;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Volume Manipulation


template< uint32_t N >
void
cLodSparseChunk< N >::Fill(tByte iVal)
{
    for( tLocalDataIndex  i = 0; i < N; ++i )
    {
        for( tLocalDataIndex  j = 0; j < N; ++j )
        {
            for( tLocalDataIndex  k = 0; k < N; ++k )
            {
                //TODO: Check with correct Hashable Local 3D Key
                mData[i][j][k] = iVal;
            }
        }
    }

    if( iVal == 0 )
        mOccupiedVolume = 0;
    else
        mOccupiedVolume = mCapacity;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Material Accessors


template< uint32_t N >
bool
cLodSparseChunk< N >::IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  bool( mData[iX][iY][iZ] );
}


template< uint32_t N >
tByte
cLodSparseChunk< N >::GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  mData[iX][iY][iZ];
}


template< uint32_t N >
void
cLodSparseChunk< N >::SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue )
{
    mData[iX][iY][iZ] = iValue;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Neighbour Accessors


template< uint32_t N >
cLodSparseChunk< N >*
cLodSparseChunk< N >::GetNeighbour( eNeighbourFace_Index  iNeighbour )  const
{
    return  mNeighbour[ int( iNeighbour ) ];
}


template< uint32_t N >
void
cLodSparseChunk< N >::SetNeighbour( eNeighbourFace_Index iNeighbour, cLodSparseChunk* iAdress )
{
    mNeighbour[ int( iNeighbour ) ] = iAdress;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Data Manipulation


template< uint32_t N >
tByte*
cLodSparseChunk< N >::DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )
{
    return  &mData[iX][iY][iZ];
}


template< uint32_t N >
tByte*
cLodSparseChunk< N >::GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    auto chunk = GetSafeExternChunkHandle( iX, iY, iZ );
    if( !chunk )
        return  NULL;

    int w = int( N );
    tLocalDataIndex safeX = tLocalDataIndex( iX % w + ( iX % w < 0 ? w : 0) );
    tLocalDataIndex safeY = tLocalDataIndex( iY % w + ( iY % w < 0 ? w : 0) );
    tLocalDataIndex safeZ = tLocalDataIndex( iZ % w + ( iZ % w < 0 ? w : 0) );
    return  chunk->DataHandle( safeX, safeY, safeZ );
}


template< uint32_t N >
 cLodSparseChunk< N >*
cLodSparseChunk< N >::GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    if( ( iX >= 0 && iX < N ) &&
        ( iY >= 0 && iY < N ) &&
        ( iZ >= 0 && iZ < N ) )
    {
        return  this;
    }
    else
    {
        if( iY == -1 )  return  mNeighbour[ int( eNeighbourFace_Index::kTop   ) ];
        if( iY == N )   return  mNeighbour[ int( eNeighbourFace_Index::kBot   ) ];
        if( iZ == -1 )  return  mNeighbour[ int( eNeighbourFace_Index::kFront ) ];
        if( iZ == N )   return  mNeighbour[ int( eNeighbourFace_Index::kBack  ) ];
        if( iX == -1 )  return  mNeighbour[ int( eNeighbourFace_Index::kLeft  ) ];
        if( iX == N )   return  mNeighbour[ int( eNeighbourFace_Index::kRight ) ];
    }

    return  NULL;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Naive Rendering


template< uint32_t N >
void
cLodSparseChunk< N >::DrawVBOs( GLuint iShaderProgramID )
{
    SendUniformDebugColor( iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kTop   , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kBot   , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kFront , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kBack  , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kLeft  , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kRight , iShaderProgramID );
}


template< uint32_t N >
void
cLodSparseChunk< N >::SetDebugColor( const  glm::vec3& iDebugColor )
{
    mDebugColor = iDebugColor;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- VBO Interface


template< uint32_t N >
void
cLodSparseChunk< N >::UpdateVBOs()
{
    UpdateVBO( eNeighbourFace_Index::kTop );
    UpdateVBO( eNeighbourFace_Index::kBot );
    UpdateVBO( eNeighbourFace_Index::kFront );
    UpdateVBO( eNeighbourFace_Index::kBack );
    UpdateVBO( eNeighbourFace_Index::kLeft );
    UpdateVBO( eNeighbourFace_Index::kRight );
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------- Private OpenGL Object Building


template< uint32_t N >
void
cLodSparseChunk< N >::InitVBOs()
{
    glGenBuffers( 6, mVBO_ID );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( eNeighbourFace_Index::kTop ) ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( eNeighbourFace_Index::kBot ) ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( eNeighbourFace_Index::kFront ) ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( eNeighbourFace_Index::kBot ) ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( eNeighbourFace_Index::kLeft ) ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( eNeighbourFace_Index::kRight ) ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


template< uint32_t N >
void
cLodSparseChunk< N >::DestroyVBOs()
{
    glDeleteBuffers( 6, mVBO_ID );
}


template< uint32_t N >
void
cLodSparseChunk< N >::UpdateVBO( eNeighbourFace_Index  iVBO_ID_index )
{
    if(glIsBuffer( mVBO_ID[ int( iVBO_ID_index ) ] ) == GL_TRUE)
        glDeleteBuffers( 1, &mVBO_ID[ int( iVBO_ID_index ) ] );

    glGenBuffers( 1, &mVBO_ID[ int( iVBO_ID_index ) ] );

    int stride = 6;
    mNVerticesVBOElem = OccupiedVolume() * stride;
    int index = 0;
    std::vector< sf::Vector3f > vertices;
    vertices.resize( mNVerticesVBOElem );
    int memsize = sgElementSize * mNVerticesVBOElem;

    int colorstride = 6;
    mNColorsVBOElem = OccupiedVolume() * colorstride;
    int colorindex = 0;
    std::vector< sf::Vector3f > colors;
    colors.resize( mNColorsVBOElem );
    int memcolorsize = sgElementSize * mNColorsVBOElem;

    eNeighbourFace_Flag neighbourFlag = eNeighbourFace_Flag( iVBO_ID_index );

    for( tLocalDataIndex  i = 0; i < N; ++i )
    {
        for( tLocalDataIndex  j = 0; j < N; ++j )
        {
            for( tLocalDataIndex  k = 0; k < N; ++k )
            {
                tByte* data = DataHandle( i, j, k );
                if( *data > 0 )
                {
                    /*
                    GenFace( iVBO_ID_index, index, vertices, i, j, k );
                    sf::Vector3f color = ColorFromVGAMaterial( data->GetMaterialField() );
                    colors[index + 0] = color;
                    colors[index + 1] = color;
                    colors[index + 2] = color;
                    colors[index + 3] = color;
                    colors[index + 4] = color;
                    colors[index + 5] = color;
                    index += stride;
                    colorindex += colorstride;
                    */
                }
            }
        }
    }

    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( iVBO_ID_index ) ] );

        glBufferData( GL_ARRAY_BUFFER, memsize + memcolorsize, 0, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, memsize, &vertices[0] );
        glBufferSubData( GL_ARRAY_BUFFER, memsize, memcolorsize, &colors[0] );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    mVerticesMsize = memsize;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------- Private OpenGL Object Rendering


template< uint32_t N >
void
cLodSparseChunk< N >::DrawVBO( eNeighbourFace_Index  iVBO_ID_index, GLuint iShaderProgramID )
{
    SendUniformNormal( iVBO_ID_index, iShaderProgramID );

    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ int( iVBO_ID_index ) ] );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( 0 ) );
    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( mVerticesMsize ) );
    glEnableVertexAttribArray( 1 );

    glDrawArrays( GL_TRIANGLES, 0, mNVerticesVBOElem );

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


template< uint32_t N >
void
cLodSparseChunk< N >::SendUniformNormal( eNeighbourFace_Index  iVBO_ID_index, GLuint iShaderProgramID  )
{
    int location = glGetUniformLocation( iShaderProgramID, "normal" );
    auto normal = sgUniformFaceNormals[ int( iVBO_ID_index ) ];
    glUniform3f(location, normal.x, normal.y, normal.z );
}


template< uint32_t N >
void
cLodSparseChunk< N >::SendUniformDebugColor( GLuint iShaderProgramID  )
{
    int location = glGetUniformLocation( iShaderProgramID, "debugColor" );
    glUniform3f(location, mDebugColor.x, mDebugColor.y, mDebugColor.z );
}



} // namespace  nDynamic
} // namespace  nVolumetric

