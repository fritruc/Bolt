#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


struct  cDataReportAnalysis
{
    cDataReportAnalysis( bool  iConversionRequired,
                         bool  iProcessingRequired,
                         eDataType iFromType,
                         eDataType iToType ) :
    mConversionRequired( iConversionRequired ),
    mProcessingRequired( iProcessingRequired ),
    mFrom( iFromType ),
    mTo( iToType )
    {
    }

    cDataReportAnalysis( bool iConversionRequired,
                         bool iProcessingRequired ) :
    mConversionRequired( iConversionRequired ),
    mProcessingRequired( iProcessingRequired )
    {
    }

    bool  mConversionRequired;
    bool  mProcessingRequired;
    eDataType mFrom;
    eDataType mTo;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

