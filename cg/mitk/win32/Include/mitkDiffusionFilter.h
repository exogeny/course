/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkDiffusionFilter_h
#define __mitkDiffusionFilter_h

#include "mitkVolumeToVolumeFilter.h"
/// mitkDiffusionFilter - a class used to diffuse the mitkVolume data (2D or 3D)  
///////////////////////////////////////////////////////////////////////////
/// mitkDiffusionFilter- a filter class derived from mitkVolumeToVolumeFilter,we use
/// this filter to smooth an image(2D) or a mitkVolume object(3D), the process is quite 
/// efficient, and the result is quite good contrast to the simplicity of the algorithm
/// if the parameters are appropriately set. The algorithm is based on the 
/// following article:
/// \li Pietro PPerona and Jitendra Malik,
///     "Scale-Space and Edge Detection Using Anisotropic Diffusion,"
///     \e IEEE \e Trans. \e Pattern \e Anal. \e Machine \e Intell.,
///     Vol. 12, No. 7, pp. 629-639, 1990
class MITK_COMMON_API mitkDiffusionFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkDiffusionFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    mitkDiffusionFilter();
    ////////////////////////////////////////////////////////////////////////////////////
    /// Set the class member variable m_K.
    /// \param param represents the extend of the intensity change of the data. a larger param 
    /// usually means a more impressive diffusion while at the same time cause more blur
    /// in the edge.
    /// \note if you want to get a better result, we recommend you choose a small param 
    /// between 10 and 20 (this is not always true, you need to try yourself), and after 
    /// several iterations you will get what you want.
    ////////////////////////////////////////////////////////////////////////////////////
    void Setm_K(double param=200);

    ////////////////////////////////////////////////////////////////////////////////////
    /// Set the class member variable m_TimeInterval.
    /// \param dt represents the time between the neighboring iterations.
    /// \note A larger dt will cause a more obvious diffusion while the edge area is also
    /// greatly blured. If dt is too large (usually: dt>1), the iterations will not converge.
    ////////////////////////////////////////////////////////////////////////////////////
    void SetTimeInterval(float dt=0.20);
    
    ////////////////////////////////////////////////////////////////////////////////////
    /// Set the class member variable m_Enable3D,determine the diffusion type(2D or 3D). 
    /// \param Is3D represents the diffusion type(true:3D false:2D).
    ////////////////////////////////////////////////////////////////////////////////////
    void SetDiffusionType(bool Is3D=false){
            m_Enable3D=Is3D;}    
    
protected:
    virtual ~mitkDiffusionFilter();
    bool Execute();

    double m_K;
    float  m_TimeInterval;
    bool   m_Enable3D;      

private:
    mitkDiffusionFilter(const mitkDiffusionFilter&);
    void operator = (const mitkDiffusionFilter&);
};


#endif

