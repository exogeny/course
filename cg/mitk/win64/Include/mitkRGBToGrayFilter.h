/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkRGBToGrayFilter_h
#define __mitkRGBToGrayFilter_h

#include "mitkVolumeToVolumeFilter.h"

/// mitkRGBToGrayFilter - a filter to transfer RGB volume to gray volume
///////////////////////////////////////////////////////////////////////////
/// mitkRGBToGrayFilter is a filter to transfer RGB volume (with 3 channels)
/// to gray volume (with 1 channel). The equation of the transform is:
/// \par
/// \f$\mathbf{GRAY}=c_{\mathbf{RED}}*\mathbf{RED}+c_{\mathbf{GREEN}}*\mathbf{GREEN}+c_{\mathbf{BLUE}}*\mathbf{BLUE}\f$
/// where \f$c_{\mathbf{RED}}+c_{\mathbf{GREEN}}+c_{\mathbf{BLUE}}=1.0\f$.
/// \par
/// You can set \f$c_{\mathbf{RED}}\f$, \f$c_{\mathbf{GREEN}}\f$
/// and \f$c_{\mathbf{BLUE}}\f$ by SetCoefficients().
class MITK_COMMON_API mitkRGBToGrayFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkRGBToGrayFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    mitkRGBToGrayFilter();

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of the output volume. MITK supports various data type.
    /// \param data_type Its valid value and meaning is shown as follows:\n
    /// MITK_CHAR            The data type is char \n
    /// MITK_UNSIGNED_CHAR   The data type is unsigned char \n
    /// MITK_SHORT           The data type is short \n
    /// MITK_UNSIGNED_SHORT  The data type is unsigned short \n
    /// MITK_INT             The data type is int \n
    /// MITK_UNSIGNED_INT    The data type is unsigned int \n
    /// MITK_LONG            The data type is long \n
    /// MITK_UNSIGNED_LONG   The data type is unsigned long \n
    /// MITK_FLOAT           The data type is float \n
    /// MITK_DOUBLE          The data type is double \n
    ///////////////////////////////////////////////////////////////////////////
    void SetOutputDataType(int dataType) { this->GetOutput()->SetDataType(dataType); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the transform coefficients. The coefficients will be normalized first
    /// so that \f$c_{\mathbf{RED}}+c_{\mathbf{GREEN}}+c_{\mathbf{BLUE}}=1.0\f$.
    /// The final transform will be:
    /// \par
    /// \f$\mathbf{GRAY}=c_{\mathbf{RED}}*\mathbf{RED}+c_{\mathbf{GREEN}}*\mathbf{GREEN}+c_{\mathbf{BLUE}}*\mathbf{BLUE}\f$.
    /// \param coefRed red coefficient
    /// \param coefGreen green coefficient
    /// \param coefBlue blue coefficient
    ///////////////////////////////////////////////////////////////////////////
    void SetCoefficients(float coefRed, float coefGreen, float coefBlue);

protected:
    virtual ~mitkRGBToGrayFilter();

    virtual bool Execute();

    float m_CoefRed;
    float m_CoefGreen;
    float m_CoefBlue;

private:
    mitkRGBToGrayFilter(const mitkRGBToGrayFilter&);
    void operator = (const mitkRGBToGrayFilter&);

};


//#define DEFINED_mitkRGBToGrayFilter



#endif

