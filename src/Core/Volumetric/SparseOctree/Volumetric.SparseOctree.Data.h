#pragma once


#include "Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


// Forward Declaration of cROMSConfig
class  cROMSConfig;


// PreCheckAnalysis Spider Struct
struct  cDataReportAnalysis
{
    enum  eTransformOperationStatus
    {
        kRequired,
        kNotRequired,
    };

    enum  eProcessOperationStatus
    {
        kProcess,
        kDiscard,
    };

    cDataReportAnalysis( eTransformOperationStatus    iTransformOperationStatus,
                           eProcessOperationStatus      iProcessOperationStatus,
                           eType       iFromType,
                           eSubType    iFromSubType,
                           eType       iToType,
                           eSubType    iToSubType ) :
    mTransformOperationStatus( iTransformOperationStatus ),
    mProcessOperationStatus( iProcessOperationStatus ),
    mFromType( iFromType ),
    mFromSubType( iFromSubType ),
    mToType( iToType ),
    mToSubType( iToSubType )
    {
    }

    cDataReportAnalysis( eTransformOperationStatus    iTransformOperationStatus,
                           eProcessOperationStatus      iProcessOperationStatus ) :
    mTransformOperationStatus( iTransformOperationStatus ),
    mProcessOperationStatus( iProcessOperationStatus ),
    mFromType( eType() ),
    mFromSubType( eSubType() ),
    mToType( eType() ),
    mToSubType( eSubType() )
    {
    }

    eTransformOperationStatus   mTransformOperationStatus;
    eProcessOperationStatus     mProcessOperationStatus;
    eType       mFromType;
    eSubType    mFromSubType;

    eType       mToType;
    eSubType    mToSubType;
};


template< eLod2N LOD, typename Atomic >
class  cData
{

protected:
    // Construction / Destruction
    virtual  ~cData();
    cData( const  cROMSConfig*  iROMSConfig );
    cData( const  cData& ) = delete;

public:
    // Pure Virtual Runtime Information
    virtual  bool       Compressed()    const  = 0;
    virtual  eType      Type()          const  = 0;
    virtual  eSubType   SubType()       const  = 0;

public:
    // Template Data Container Accessors
    eLod2N  LOD()       const;
    tSize   Size()      const;
    tVolume Capacity()  const;

    const  cROMSConfig&  ROMSConfig()  const;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const          = 0;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   = 0;

private:
    // Data Transform Analysis
    virtual  cDataReportAnalysis  AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )  = 0;

private:
    // Private Member Data
    const  tVolume  mCapacity  =  LOD * LOD * LOD;
    const  cROMSConfig*  mROMSConfig; // Non-Owning

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.Data.tImp.hpp"

