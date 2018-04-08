#include "Core.Volumetric.SparseOctree.RawData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cRawData< LOD, Atomic >::~cRawData()
{
    for( int i = 0; i < LOD; ++i )
    {
        for( int j = 0; j < LOD; ++j )
        {
            delete  mCore[i][j];
        }
        delete  mCore[i];
    }
    delete  mCore;
}


template< eLod2N LOD, typename Atomic >
inline  cRawData< LOD, Atomic >::cRawData( const  cROMSConfig*  iROMSConfig, const  Atomic& iFillValue ) :
    cData< LOD, Atomic >( iROMSConfig )
{
    mCore = new  Atomic**[ LOD ];
    for( int i = 0; i < LOD; ++i )
    {
        mCore[i] = new Atomic*[ LOD ];
        for( int j = 0; j < LOD; ++j )
        {
            mCore[i][j] = new Atomic[ LOD ];
        }
    }
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cRawData< LOD, Atomic >::Compressed()  const
{
    return  false;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cRawData< LOD, Atomic >::Type()  const
{
    return  eType::kRaw;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cRawData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    auto size = tSize( LOD );
    assert( iX > 0 && iX < size );
    assert( iY > 0 && iY < size );
    assert( iZ > 0 && iZ < size );
    return  mCore[ iX ][ iY ][ iZ ];
}


template< eLod2N LOD, typename Atomic >
inline  void  cRawData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    auto size = tSize( LOD );
    assert( iX > 0 && iX < size );
    assert( iY > 0 && iY < size );
    assert( iZ > 0 && iZ < size );
    mCore[ iX ][ iY ][ iZ ] = iValue;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cRawData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( iValue == Get( iX, iY ,iZ ) )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
    else
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess );

}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

