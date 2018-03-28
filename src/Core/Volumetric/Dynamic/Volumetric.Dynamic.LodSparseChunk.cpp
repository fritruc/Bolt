#include "Volumetric.Dynamic.LodSparseChunk.h"
#include "Volumetric.Dynamic.Utils.h"


namespace  nVolumetric {
namespace  nDynamic {


static  const  sf::Vector3f  sgUniformFaceNormals[6] = { sf::Vector3f(  0.f,    +1.f,   0.f     ),      // Top
                                                         sf::Vector3f(  0.f,    -1.f,   0.f     ),      // Bot
                                                         sf::Vector3f(  0.f,    0.f,    +1.f    ),      // Front
                                                         sf::Vector3f(  0.f,    0.f,    -1.f    ),      // Back
                                                         sf::Vector3f(  -1.f,   0.f,    0.f     ),      // Left
                                                         sf::Vector3f(  +1.f,   0.f,    0.f     ) };    // Right

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction

cLodSparseChunk::~cLodSparseChunk()
{
    DestroyVBOs();
}


cLodSparseChunk::cLodSparseChunk() :
    mOccupiedVolume( 0 ),
    mNVerticesVBOElem( 0 ),
    mDebugColor( sf::Vector3f() )
{
    InitVBOs();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Volume Information


uint16_t
cLodSparseChunk::Size()  const
{
    return  N;
}


uint32_t
cLodSparseChunk::Capacity()  const
{
    return  mCapacity;
}


uint32_t
cLodSparseChunk::OccupiedVolume()  const
{
    return  mOccupiedVolume;
}


bool
cLodSparseChunk::IsFull()  const
{
    return  mOccupiedVolume == mCapacity;
}


bool
cLodSparseChunk::IsEmpty()  const
{
    return  mOccupiedVolume == 0;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Volume Manipulation


void
cLodSparseChunk::Fill(tByte iVal)
{
    for( tLocalDataIndex  i = 0; i < N; ++i )
    {
        for( tLocalDataIndex  j = 0; j < N; ++j )
        {
            for( tLocalDataIndex  k = 0; k < N; ++k )
            {
                //TODO: Check with correct Hashable Local 3D Key
                mData.emplace( 0, iVal );
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


bool
cLodSparseChunk::IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    auto it = mData.find( 0 );
    if( it == mData.end() )
        return  false;

    return  bool( it->second );
}


tByte
cLodSparseChunk::GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    auto it = mData.find( 0 );
    if( it == mData.end() )
        return  false;

    return  it->second;
}


void
cLodSparseChunk::SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue )
{
    tByte oldMat = GetMaterial( iX, iY, iZ );
    mData.emplace( 0, iValue );

    tByte flag = tByte( bool( oldMat ) ) << 1 | tByte( bool( iValue ) );
    // Bitfield manipulation:
    // 11   old solid - new solid   - 3 - no change
    // 10   old solid - new empty   - 2 - decrease occupied volume
    // 01   old empty - new solid   - 1 - increase occupied volume
    // 00   old empty - new empty   - 0 - no change
    if( flag == 2 ) --mOccupiedVolume;
    if( flag == 1 ) ++mOccupiedVolume;

    if( flag == 1 || flag == 2 )    // Update neighbours in case of change
    {
        UpdateDataNeighbours( iX, iY, iZ );
    }
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Neighbour Accessors


cLodSparseChunk*
cLodSparseChunk::GetNeighbour( eNeighbourFace_Index  iNeighbour )  const
{
    return  mNeighbour[ int( iNeighbour ) ];
}


void cLodSparseChunk::SetNeighbour( eNeighbourFace_Index iNeighbour, cLodSparseChunk* iAdress )
{
    mNeighbour[ int( iNeighbour ) ] = iAdress;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Data Manipulation


tByte*
cLodSparseChunk::DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )
{
    auto it = mData.find( 0 );
    if( it == mData.end() )
        return  NULL;

    return  &it->second;
}


void
cLodSparseChunk::UpdateDataNeighbours( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )
{
    /*
    cData* currentHandle    = DataHandle( iX, iY, iZ );
    bool  currentIsSolid    = currentHandle->IsSolid();
    cData* topDataHandle    = GetSafeExternDataHandle( iX,     iY+1,   iZ      );
    cData* botDataHandle    = GetSafeExternDataHandle( iX,     iY-1,   iZ      );
    cData* frontDataHandle  = GetSafeExternDataHandle( iX,     iY,     iZ+1    );
    cData* backDataHandle   = GetSafeExternDataHandle( iX,     iY,     iZ-1    );
    cData* leftDataHandle   = GetSafeExternDataHandle( iX-1,   iY,     iZ      );
    cData* rightDataHandle  = GetSafeExternDataHandle( iX+1,   iY,     iZ      );

    if( topDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagTop, topDataHandle->IsSolid() );
        topDataHandle->SetNeighbour( eNF_Flag::kFlagBot, currentIsSolid );
    }

    if( botDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagBot, botDataHandle->IsSolid() );
        botDataHandle->SetNeighbour( eNF_Flag::kFlagTop, currentIsSolid );
    }

    if( frontDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagFront, frontDataHandle->IsSolid() );
        frontDataHandle->SetNeighbour( eNF_Flag::kFlagBack, currentIsSolid );
    }

    if( backDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagBack, backDataHandle->IsSolid() );
        backDataHandle->SetNeighbour( eNF_Flag::kFlagFront, currentIsSolid );
    }

    if( leftDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagLeft, leftDataHandle->IsSolid() );
        leftDataHandle->SetNeighbour( eNF_Flag::kFlagRight, currentIsSolid );
    }

    if( rightDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagRight, rightDataHandle->IsSolid() );
        rightDataHandle->SetNeighbour( eNF_Flag::kFlagLeft, currentIsSolid );
    }
    */
}


tByte*
cLodSparseChunk::GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
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


 cLodSparseChunk*
cLodSparseChunk::GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
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


void
cLodSparseChunk::DrawVBOs( GLuint iShaderProgramID )
{
    SendUniformDebugColor( iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kTop   , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kBot   , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kFront , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kBack  , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kLeft  , iShaderProgramID );
    DrawVBO( eNeighbourFace_Index::kRight , iShaderProgramID );
}


void
cLodSparseChunk::SetDebugColor( const  sf::Vector3f& iDebugColor )
{
    mDebugColor = iDebugColor;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- VBO Interface


void
cLodSparseChunk::UpdateVBOs()
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


void
cLodSparseChunk::InitVBOs()
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


void
cLodSparseChunk::DestroyVBOs()
{
    glDeleteBuffers( 6, mVBO_ID );
}


void
cLodSparseChunk::UpdateVBO( eNeighbourFace_Index  iVBO_ID_index )
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


void
cLodSparseChunk::DrawVBO( eNeighbourFace_Index  iVBO_ID_index, GLuint iShaderProgramID )
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


void
cLodSparseChunk::SendUniformNormal( eNeighbourFace_Index  iVBO_ID_index, GLuint iShaderProgramID  )
{
    int location = glGetUniformLocation( iShaderProgramID, "normal" );
    auto normal = sgUniformFaceNormals[ int( iVBO_ID_index ) ];
    glUniform3f(location, normal.x, normal.y, normal.z );
}


void
cLodSparseChunk::SendUniformDebugColor( GLuint iShaderProgramID  )
{
    int location = glGetUniformLocation( iShaderProgramID, "debugColor" );
    glUniform3f(location, mDebugColor.x, mDebugColor.y, mDebugColor.z );
}



} // namespace  nDynamic
} // namespace  nVolumetric

