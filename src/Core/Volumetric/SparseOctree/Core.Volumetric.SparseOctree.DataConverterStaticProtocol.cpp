#include "Core.Volumetric.SparseOctree.DataConverterStaticProtocol.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


#define KEY_EXISTS( iMap, iKey )            ( ! ( iMap.find( iKey ) == iMap.end() ) )


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cDataConverterStaticProtocol::~cDataConverterStaticProtocol()
{
}


cDataConverterStaticProtocol::cDataConverterStaticProtocol() :
    mProcessMap()
{
    mProcessMap[ eDataType::kEmpty ]    = &cDataConverterStaticProtocol::ConvertToEmpty;
    mProcessMap[ eDataType::kFull ]     = &cDataConverterStaticProtocol::ConvertToFull;
    mProcessMap[ eDataType::kSparse ]   = &cDataConverterStaticProtocol::ConvertToSparse;
    mProcessMap[ eDataType::kRaw ]      = &cDataConverterStaticProtocol::ConvertToRaw;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------- Conversion Protocol Selection


void  cDataConverterStaticProtocol::ProcessDataReportAnalysis( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    if( !iDataReportAnalysis.mConversionRequired )
        return;

    auto type = iDataReportAnalysis.mTo;
    if( KEY_EXISTS( mProcessMap, type ) )
            ( this->*( mProcessMap[ type ] ) )( iDataReportAnalysis );
    else
        assert( false );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

