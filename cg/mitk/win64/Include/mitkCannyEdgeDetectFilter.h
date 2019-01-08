/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





#ifndef __mitkCannyEdgeDetectFilter_h
#define __mitkCannyEdgeDetectFilter_h

#include "mitkVolumeToVolumeFilter.h"

class MITK_COMMON_API mitkCannyEdgeDetectFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkCannyEdgeDetectFilter,mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    mitkCannyEdgeDetectFilter();

    void SetHighThreshold (float highThreshold);
    void SetLowThreshold (float lowThreshold);
    
protected:
    virtual ~mitkCannyEdgeDetectFilter();
    virtual bool Execute();

    float m_HighThreshold,m_LowThreshold;


private:
    mitkCannyEdgeDetectFilter(const mitkCannyEdgeDetectFilter&);
    void operator = (const mitkCannyEdgeDetectFilter&);


};

#endif

