/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkGaussianDerivativeImageFilter_h
#define __mitkGaussianDerivativeImageFilter_h

#include "mitkVolumeToVolumeFilter.h"

class _GaussianDerivative;
class mitkVolumeIteratorBase;

/// mitkGaussianDerivativeImageFilter - a concrete class for implementation of Gaussian Derivative Filter
///////////////////////////////////////////////////////////////////////////
/// mitkGaussianDerivativeImageFilter - a concrete class for implementation of 
/// Gaussian Derivative Recursive Filter. It is used for calculating the gradient 
/// intensity of a image. The derivative based optimize method in registration 
/// framework will use this gradient intensities to compute the gradient descent 
/// direction.
/// 
/// In registration framework, this filter inputs the moving volume and outputs
/// the gradient volume (2-channels in 2D and 3-channels in 3D).
///
class MITK_COMMON_API mitkGaussianDerivativeImageFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkGaussianDerivativeImageFilter, mitkVolumeToVolumeFilter)  
    virtual void PrintSelf(ostream &os);

    //////////////////////////////////////////////////////////////////////////
    /// Constructor.
    //////////////////////////////////////////////////////////////////////////
    mitkGaussianDerivativeImageFilter();

    //////////////////////////////////////////////////////////////////////////
    /// Deconstructor.
    //////////////////////////////////////////////////////////////////////////
    virtual ~mitkGaussianDerivativeImageFilter();

    //////////////////////////////////////////////////////////////////////////
    /// Set the data type for output volume.Default is MITK_FLOAT.
    /// \param dataType Specify the output volume's data type.
    //////////////////////////////////////////////////////////////////////////
    void SetOutputDatatype(int dataType) {m_OutputDataType = dataType;}

    void SetRegion(const VectorIndexType& r) { m_Region = r; }

    void SetNormalizeAcrossScale(bool f);

    void SetSigma(ScalarParameterType s);

protected:  
    bool Update();
    virtual bool Execute(); 
    bool RunOnADirection(mitkVolumeIteratorBase* inDataIterator, unsigned int direction, unsigned int order);

    mitkVolumeIteratorBase* m_InputIterator;
    mitkVolumeIteratorBase* m_OutputIterator;

    _GaussianDerivative*    m_DerivativeAdaptor;

    VectorIndexType         m_Region;
    unsigned int            m_ImageDimension;
    int                     m_Dimensions[3];
    float                   m_Spacings[3];
    int                     m_OutputDataType;           

private:
    mitkGaussianDerivativeImageFilter(const mitkGaussianDerivativeImageFilter&);
    void operator = (const mitkGaussianDerivativeImageFilter&);

};

#endif

