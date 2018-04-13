#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"
#include "Core.Volumetric.SparseOctree.Simple3DKey.h"


#include <glm/vec3.hpp>


namespace  nVolumetric      {
namespace  nSparseOctree    {


struct  cDataReportAnalysis;
class   cROMSConfig;


template< class __PARENT, eLod2N __INTRINSIC_LOD, typename __ATOMIC >
class  cData
{

public:
    // Construction / Destruction
    virtual  ~cData();
    cData( __PARENT*  iParent, const  cROMSConfig*  iROMSConfig, const  cSimple3DKey&  iAttributeKey );
    cData( const  cData& ) = delete; // Not-Allowed

public:
    // Pure Virtual Runtime Information
    virtual  eDataType  Type()  const  = 0;

public:
    // Template Data Container Accessors
    eLod2N      Intrinsic_LOD()  const;
    int16_t     Intrinsic_LOD_Size()  const;
    uint64_t    Capacity()  const;

    const  cROMSConfig&  ROMSConfig()  const;
    const  cSimple3DKey&  AttributeKey()  const;

public:
    // Data Accessors
    virtual  __ATOMIC  DefaultValue();
    virtual  __ATOMIC*  Data( uint16_t iX, uint16_t iY, uint16_t iZ )  = 0;
    virtual  void  Write( uint16_t iX, uint16_t iY, uint16_t iZ, const  __ATOMIC&  iValue )  = 0;

public:
    // Data Transform Analysis
    virtual  cDataReportAnalysis  AnteriorReportAnalysisOnSet( uint16_t iX, uint16_t iY, uint16_t iZ, const  __ATOMIC&  iValue )  = 0;
    virtual  cDataReportAnalysis  PosteriorReportAnalysisOnSet( uint16_t iX, uint16_t iY, uint16_t iZ, const  __ATOMIC&  iValue )  = 0;

public:
    // Debug Rendering
    virtual  glm::vec3  WireFrameColor();
    virtual  void  RenderWireFrameStructure();

private:
    // Private Member Data
    __PARENT*               mParent; // Non-Owning
    const  cROMSConfig*     mROMSConfig; // Non-Owning
    const  cSimple3DKey     mAttributeKey;
    const  int16_t          mLOD_Size = static_cast< int16_t >( __INTRINSIC_LOD );
    const  uint64_t         mCapacity = mLOD_size * mLOD_size * mLOD_size;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.Data.tImp.hpp"

