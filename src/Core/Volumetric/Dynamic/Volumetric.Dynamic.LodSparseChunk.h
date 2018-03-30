#pragma once

#include "Volumetric.Dynamic.Types.h"

#include <GL/glew.h>
#include <gl/GLU.h>
#include <SFML/OpenGL.hpp>

#include <glm/vec3.hpp>

namespace  nVolumetric {
namespace  nDynamic {


template< uint32_t N >
class  cLodSparseChunk
{

public:
    // Construction / Destruction
    ~cLodSparseChunk();
    cLodSparseChunk();
    cLodSparseChunk( const  cLodSparseChunk& ) = delete;

public:
    // Volume Information
    uint16_t    Size()              const;
    uint32_t    Capacity()          const;
    uint32_t    OccupiedVolume()    const;
    bool        IsFull()            const;
    bool        IsEmpty()           const;

public:
    // Volume Manipulation
    void    Fill( tByte iMaterial );

public:
    // Material Accessors
    bool    IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )       const;
    tByte   GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )   const;
    void    SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue );

public:
    // Neighbour Accessors
    cLodSparseChunk*    GetNeighbour( eNeighbourFace_Index  iNeighbourIndex )  const;
    void                SetNeighbour( eNeighbourFace_Index  iNeighbourIndex, cLodSparseChunk* iAdress );

private:
    // Data Manipulation
    tByte*              DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ );

    tByte*              GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    cLodSparseChunk*    GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );

public:
    // Naive Rendering
    void  DrawVBOs( GLuint iShaderProgramID );
    void  SetDebugColor( const  glm::vec3& iDebugColor );

public:
    // VBO Interface
    void  UpdateVBOs();

private:
    // Private OpenGL Object Building
    void  InitVBOs();
    void  DestroyVBOs();
    void  UpdateVBO( eNeighbourFace_Index  iVBO_ID_index );

private:
    // Private OpenGL Object Rendering
    void  DrawVBO( eNeighbourFace_Index  iVBO_ID_index, GLuint iShaderProgramID  );
    void  SendUniformNormal( eNeighbourFace_Index  iVBO_ID_index, GLuint iShaderProgramID  );
    void  SendUniformDebugColor( GLuint iShaderProgramID  );

private:
    // Private Data Members
    const  uint32_t                 mCapacity = N * N * N;
    uint32_t                        mOccupiedVolume;
    cLodSparseChunk*                mNeighbour[6] = { 0, 0, 0, 0, 0, 0 };   // six neighbours
    tByte                           mData[N][N][N];

    GLuint                          mVBO_ID[6] = { 0, 0, 0, 0, 0, 0 };
    GLuint                          mNVerticesVBOElem;
    GLuint                          mNColorsVBOElem;
    GLuint                          mVerticesMsize;
    glm::vec3                       mDebugColor;
};


} // namespace  nDynamic
} // namespace  nVolumetric

