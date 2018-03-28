#pragma once

#include "Volumetric.Dynamic.Utils.h"

namespace  nVolumetric {
namespace  nDynamic {

void
GenInterleavedCCWFaceWithColor( eNeighbourFace_Index iFace, std::vector< glm::vec3 >* oData, tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor )
{
    switch( iFace )
    {
    case eNeighbourFace_Index::kRight:
        InterleavedCCWRightFaceWithColor( oData, ioIndex, iLocation, iColor );
        break;
    case eNeighbourFace_Index::kLeft:
        InterleavedCCWLeftFaceWithColor( oData, ioIndex, iLocation, iColor );
        break;
    case eNeighbourFace_Index::kTop:
        InterleavedCCWTopFaceWithColor( oData, ioIndex, iLocation, iColor );
        break;
    case eNeighbourFace_Index::kBot:
        InterleavedCCWBotFaceWithColor( oData, ioIndex, iLocation, iColor );
        break;
    case eNeighbourFace_Index::kBack:
        InterleavedCCWBackFaceWithColor( oData, ioIndex, iLocation, iColor );
        break;
    case eNeighbourFace_Index::kFront:
        InterleavedCCWFrontFaceWithColor( oData, ioIndex, iLocation, iColor );
        break;
    }
}


void
InterleavedCCWRightFaceWithColor( std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor )
{
    // Two triangles, CCW winding, right face.
    // Alternating: Vertice, Color, Vertice, Color, ...

    //Triangle1
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;

    //Triangle2
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
}


void
InterleavedCCWLeftFaceWithColor( std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor )
{
    // Two triangles, CCW winding, left face.
    // Alternating: Vertice, Color, Vertice, Color, ...

    //Triangle1
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;

    //Triangle2
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
}


void
InterleavedCCWTopFaceWithColor(   std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor )
{
    // Two triangles, CCW winding, top face.
    // Alternating: Vertice, Color, Vertice, Color, ...

    //Triangle1
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;

    //Triangle2
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
}


void
InterleavedCCWBotFaceWithColor( std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor )
{
    // Two triangles, CCW winding, bot face.
    // Alternating: Vertice, Color, Vertice, Color, ...

    //Triangle1
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;

    //Triangle2
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
}


void
InterleavedCCWBackFaceWithColor( std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor )
{
    // Two triangles, CCW winding, back  face.
    // Alternating: Vertice, Color, Vertice, Color, ...

    //Triangle1
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;

    //Triangle2
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 1.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
}


void
InterleavedCCWFrontFaceWithColor( std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor )
{
    // Two triangles, CCW winding, front  face.
    // Alternating: Vertice, Color, Vertice, Color, ...

    //Triangle1
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;

    //Triangle2
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 0.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 0.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
    (*oData)[ (*ioIndex)++ ] = iLocation + glm::vec3( 1.f, 1.f, 0.f );
    (*oData)[ (*ioIndex)++ ] = iColor;
}


glm::vec3
SuperVGAColorFromMaterial( tByte iMaterial )
{
    // Emphasis: 3bits | 3bits | 2bits
    float r = float( ( iMaterial & 0b11100000 ) >> 5 ) / 3.f;
    float g = float( ( iMaterial & 0b00011100 ) >> 2 ) / 7.f;
    float b = float( ( iMaterial & 0b00000011 ) ) / 7.f;
    return  glm::vec3( r, g, b );
}


} // namespace  nDynamic
} // namespace  nVolumetric

