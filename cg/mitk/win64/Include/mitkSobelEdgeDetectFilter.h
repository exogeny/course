/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkSobelEdgeDetectFilter_h
#define __mitkSobelEdgeDetectFilter_h

#include "mitkVolumeToVolumeFilter.h"

/// mitkSobelEdgeDetectFilter - a class used to detect the edge in an image
///////////////////////////////////////////////////////////////////////////
/// mitkSobelEdgeDetectFilter is a filter based on the sobel edge detect method.
/// this filter comprise the considerations of both the vertical trend and the 
/// horizontal trend.the result is also quite good contrast to its simplicity.But,
/// sometimes the processed image may present a little discontinuity.
class MITK_COMMON_API mitkSobelEdgeDetectFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkSobelEdgeDetectFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    mitkSobelEdgeDetectFilter();

    ///////////////////////////////////////////////////////////////////////////////
    /// Set the member variable m_Threshold.
    /// \param Threshold represent the cut value,the value below Threshold is set
    /// to 0,and the value above Threshold is set to 255.
    /// \warning you need to choose an appropriate value(<50) to get a satisfying result.
    ///////////////////////////////////////////////////////////////////////////////
    void SetThreshold(float Threshold){m_Threshold=Threshold;}

protected:
    virtual ~mitkSobelEdgeDetectFilter();
    virtual bool Execute();

    float    m_Threshold;
private:
    mitkSobelEdgeDetectFilter(const mitkSobelEdgeDetectFilter&);
    void operator = (const mitkSobelEdgeDetectFilter&);

};


//#define DEFINED_mitkSobelEdgeDetectFilter



#endif

