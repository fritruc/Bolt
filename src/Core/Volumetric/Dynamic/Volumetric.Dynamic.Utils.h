#pragma once

#include <vector>

#include "glm/vec3.hpp"

#include "Volumetric.Dynamic.Types.h"

namespace  nVolumetric {
namespace  nDynamic {

inline  static  eNeighbourFace_Flag  NeighbourFace_FlagFromIndex( eNeighbourFace_Index iNF_Index )   { return  static_cast< eNeighbourFace_Flag >( int( pow( 2, int( iNF_Index ) ) ) ); }

void  GenInterleavedCCWFaceWithColor( eNeighbourFace_Index iFace, std::vector< glm::vec3 >* oData, tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor );

void  InterleavedCCWRightFaceWithColor( std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor );
void  InterleavedCCWLeftFaceWithColor(  std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor );
void  InterleavedCCWTopFaceWithColor(   std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor );
void  InterleavedCCWBotFaceWithColor(   std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor );
void  InterleavedCCWBackFaceWithColor(  std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor );
void  InterleavedCCWFrontFaceWithColor( std::vector< glm::vec3 >* oData,  tBufferDataIndex* ioIndex, const  glm::vec3&  iLocation, const  glm::vec3&  iColor );

glm::vec3  SuperVGAColorFromMaterial( tByte iMaterial );


} // namespace  nDynamic
} // namespace  nVolumetric

