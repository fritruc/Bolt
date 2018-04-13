#pragma once


#include "Core.Volumetric.SparseOctree.Data.h"
#include "Core.Volumetric.SparseOctree.DataReportAnalysis.h"
#include "Core.Volumetric.SparseOctree.Types.h"


#include <map>


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cDataConverterStaticProtocol
{

protected:
    // Construction / Destruction
    ~cDataConverterStaticProtocol();
    cDataConverterStaticProtocol();
    cDataConverterStaticProtocol( const  cDataConverterStaticProtocol& ) = delete;

public:
    // Conversion Protocol Selection
    static  void  ProcessDataReportAnalysis( const  cDataReportAnalysis&  iDataReportAnalysis );

private:
    // Conversion Protocol Functions
    static  void  ConvertToEmpty(  const  cDataReportAnalysis&  iDataReportAnalysis );
    static  void  ConvertToFull(   const  cDataReportAnalysis&  iDataReportAnalysis );
    static  void  ConvertToSparse( const  cDataReportAnalysis&  iDataReportAnalysis );
    static  void  ConvertToRaw(    const  cDataReportAnalysis&  iDataReportAnalysis );

private:
    // Data Members
    typedef  void  ( cDataConverterStaticProtocol::*tFctPtr )( const  cDataReportAnalysis& );
    typedef std::map< eDataType, tFctPtr >  tProcessMap;

    static tProcessMap  mProcessMap;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

