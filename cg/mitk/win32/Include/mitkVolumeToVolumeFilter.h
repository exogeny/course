/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeToVolumeFilter_h
#define __mitkVolumeToVolumeFilter_h

#include "mitkFilter.h"
#include "mitkRCPtr.h"
#include "mitkVolume.h"
#include "mitkOoCGlobalSettings.h"

/// mitkVolumeToVolumeFilter - abstract class specifies interface for volume to volume filter
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeToVolumeFilter is an abstract class specifies interface for
/// volume to volume filter. This type of filter has a volume input and 
/// generates a volume as output.
class MITK_COMMON_API mitkVolumeToVolumeFilter : public mitkFilter
{
public:
    MITK_TYPE(mitkVolumeToVolumeFilter,mitkFilter)

    virtual void PrintSelf(ostream& os);  

    ///////////////////////////////////////////////////////////////////////////
    /// Set the input volume
    /// \param inData Specify the input volume
    ///////////////////////////////////////////////////////////////////////////
    void SetInput(mitkVolume *inData) {m_InData = inData;}

    ///////////////////////////////////////////////////////////////////////////
    /// Get the input volume
    /// \return Return the input volume
    ///////////////////////////////////////////////////////////////////////////
    mitkVolume* GetInput() {return m_InData;}

    ///////////////////////////////////////////////////////////////////////
    /// Let the reader support out-of-core volume data.
    /// \param diskPath the path in the disk to cache the volume data
    /// \param bufSliceNum the number of slices to cache in the main memory
    /// \param supportOoC whether to turn on out-of-core support
    /// \note The parameter diskPath must be specified (not NULL) if you
    ///       really want to turn on out-of-core support, if not, the value
    ///       of supportOoC will be ignored even if it is set to true.
    ///////////////////////////////////////////////////////////////////////
    void SetOoCSupport(char const *diskPath=mitkOoCGlobalSettings::DiskCachePath, unsigned int bufSliceNum = mitkOoCGlobalSettings::BufferedSliceNumber, bool supportOoC = true);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the output volume
    /// \return Return the output volume
    ///////////////////////////////////////////////////////////////////////////
    mitkVolume* GetOutput();

protected:
    virtual ~mitkVolumeToVolumeFilter();
    mitkVolumeToVolumeFilter();    

    mitkRCPtr<mitkVolume> m_InData;
    mitkVolume *m_OutData;

    mitkString *m_DiskPath;
    unsigned int m_BufferedSliceNum;

    bool m_NeedOoC;
    
private:
    mitkVolumeToVolumeFilter(const mitkVolumeToVolumeFilter&);
    void operator=(const mitkVolumeToVolumeFilter&);

};

 
//#define DEFINED_mitkVolumeToVolumeFilter


#endif


