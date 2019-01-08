/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





#ifndef __mitkVolumeToMeshFilter_h
#define __mitkVolumeToMeshFilter_h

#include "mitkFilter.h"
#include "mitkRCPtr.h"
#include "mitkVolume.h"
#include "mitkMesh.h"
#include "mitkOoCGlobalSettings.h"

/// mitkVolumeToMeshFilter - abstract class specifies interface for volume to mesh filter
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeToMeshFilter is an abstract class specifies interface for
/// volume to mesh filter. This type of filter has a volume input and 
/// generates a mesh as output.
class MITK_COMMON_API mitkVolumeToMeshFilter : public mitkFilter
{
public:
    MITK_TYPE(mitkVolumeToMeshFilter,mitkFilter)
        
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
    /// Let the reader support out-of-core mesh data.
    /// \param diskPath the path in the disk to cache the mesh data
    /// \param bufSliceNum the number of slices to cache in the main memory
    /// \param supportOoC whether to turn on out-of-core support
    /// \note The parameter diskPath must be specified (not NULL) if you
    ///       really want to turn on out-of-core support, if not, the value
    ///       of supportOoC will be ignored even if it is set to true.
    ///////////////////////////////////////////////////////////////////////
    void SetOoCSupport(char const *diskPath=mitkOoCGlobalSettings::DiskCachePath, unsigned int bufBlockNum = mitkOoCGlobalSettings::BufferedSliceNumber, bool supportOoC = true);
    
    ///////////////////////////////////////////////////////////////////////////
    /// Get the output mesh
    /// \return Return the output mesh
    ///////////////////////////////////////////////////////////////////////////
    mitkMesh* GetOutput();
    
    ///////////////////////////////////////////////////////////////////////////
    /// Set user defined output mesh to replace the default generated mesh.
    /// \param mesh the new output mesh object to be set
    ///////////////////////////////////////////////////////////////////////////
    void SetOutputMesh(mitkMesh *mesh);
    
protected:
    mitkVolumeToMeshFilter();
    virtual ~mitkVolumeToMeshFilter();    
    
    mitkRCPtr<mitkVolume> m_InData;
    mitkMesh *m_OutData;
    
    mitkString *m_DiskPath;
    unsigned int m_BufferedBlockNum;
    
    bool m_NeedOoC;
    
private:
    mitkVolumeToMeshFilter(const mitkVolumeToMeshFilter&);
    void operator=(const mitkVolumeToMeshFilter&);
};

 
//#define DEFINED_mitkVolumeToMeshFilter



#endif


