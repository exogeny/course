/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





#ifndef __mitkGaussianFilter_h
#define __mitkGaussianFilter_h

#include "mitkVolumeToVolumeFilter.h"

/// mitkGaussianFilter - a concrete class for implementation of Gaussian Smooth Filter
///////////////////////////////////////////////////////////////////////////
/// mitkGaussianFilter - a concrete class for implementation of Gaussian Smooth Filter.
///
class MITK_COMMON_API mitkGaussianFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkGaussianFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);
        
    mitkGaussianFilter();

    /////////////////////////////////////////////////////////////////////////////////
    /// Set the dimension of Gaussian Filter.
    /// \param Dimensionality Specify the dimension. Default is 3.
    /////////////////////////////////////////////////////////////////////////////////
    void SetDimensionality(int Dimensionality);

    /////////////////////////////////////////////////////////////////////////////////
    /// Set the standard deviation of Gaussian Filter.
    /// \param StandardDeviation Specify the standard deviation. Default is 1.
    /////////////////////////////////////////////////////////////////////////////////
    void SetStandardDeviation(float StandardDeviation);


protected:
    virtual ~mitkGaussianFilter();
    virtual bool Execute();


    int m_Dimensionality;
    float m_StandardDeviation;

private:
    mitkGaussianFilter(const mitkGaussianFilter&);
    void operator = (const mitkGaussianFilter&);
    
};


#endif



