/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeResizeFilter_h
#define __mitkVolumeResizeFilter_h

#include "mitkVolumeToVolumeFilter.h"

/// mitkVolumeResizeFilter - a concrete filter class to zoom the specified volume
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeResizeFilter is a concrete filter class which inherits from volume to volume filter
/// to zoom the specified volume.
/// This filter needs a volume input and generates a volume output.
/// So you should first input a volume using public member function SetInput(),
/// then you should set zoom parameters using 
/// SetZoomSize(const int, const int, const int)(represents demanded width,height 
/// and image number respectively) or SetZoomRate(const float, const float, const float)
/// (represents zoom rate of demanded width, height and image number respectively, if the 
/// corresponding parameter value is bigger than 1.0, it means "zoom in",
/// and if the corresponding parameter value is smaller than 1.0,it means "zoom out".
/// Two examples using mitkVolumeResizeFilter are given below. \n
/// Example 1: If you want to zoom volume using SetZoomSize()  
/// the code snippet is:
/// \code
/// mitkVolumeResizeFilter *filter = new mitkVolumeResizeFilter;
/// filter->SetInput(inVolume);
/// filter->SetZoomSize(targetwidth,targetheight,targetimagenumber);
/// if (filter->Run())
/// {
///       mitkVolume * outVolume = filter->GetOutput();
///        Using  outVolume... 
/// }
/// \endcode
/// Example 2: If you want to zoom volume using SetZoomRate()  
/// the code snippet is:
/// \code
/// mitkVolumeResizeFilter *filter = new mitkVolumeResizeFilter;
/// filter->SetInput(inVolume);
/// filter->SetZoomRate(widthzoomrate,heightzoomrate,imagenumberzoomrate);
/// if (filter->Run())
/// {
///       mitkVolume * outVolume = filter->GetOutput();
///       Using outVolume...
/// }
/// \endcode
/// \note The inpute size must >= 2x2x2!
class MITK_COMMON_API mitkVolumeResizeFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkVolumeResizeFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    mitkVolumeResizeFilter();

    ///////////////////////////////////////////////////////////////////////////
    /// Call SetProperty() to set property of the target volume(the output volume)
    /// with the specified width,height and image numbers which is demanded by user.
    /// \param xzoomsize The specified target width demanded by user
    /// \param yzoomsize The specified target height demanded by user
    /// \param zzoomsize The specified target image numbers demanded by user
    /// \return Return true if this setting process is successful,otherwise return false.
    /////////////////////////////////////////////////////////////////////////// 
    void SetZoomSize(int const xzoomsize, int const yzoomsize , int const zzoomsize);

    ///////////////////////////////////////////////////////////////////////////
    /// Call SetProperty() to set property of the target volume(the output volume)
    /// with the specified zoom rate in each direction which is demanded by user.
    /// \param xzoomrate The specified zoom rate in direction x demanded by user.
    /// \param yzoomrate The specified zoom rate in direction y demanded by user.
    /// \param zzoomrate The specified zoom rate in direction z demanded by user.
    /// \return Return true if this setting process is successful,otherwise return false.
    /////////////////////////////////////////////////////////////////////////// 
    void SetZoomRate(float const xzoomrate,float const yzoomrate,float const zzoomrate);


protected:
    virtual ~mitkVolumeResizeFilter();
    virtual bool Execute();

    
    // Specify the property(parameters such as width,spacings,data type and so on)
    // of the target volume(the output volume).
    // \return Return true if this setting process is successful,otherwise return false.
    //bool _setProperty();
    
    //int m_InDatacoordinates[3];
    int m_OutDatacoordinates[3];
    //int m_InDataNumberOfChannel;
    //float m_InDataSpacings[3];
    //float m_OutDataSpacings[3];
    //float m_ZoomScale[3];
    //int m_InDataIncrement[3];
    //int m_OutDataIncrement[3];
    //int m_InDataDataType;

    


private:
    mitkVolumeResizeFilter(const mitkVolumeResizeFilter&);
    void operator = (const mitkVolumeResizeFilter&);

};


//#define DEFINED_mitkVolumeResizeFilter



#endif

