/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMeshToMeshFilter_h
#define __mitkMeshToMeshFilter_h

#include "mitkFilter.h"
#include "mitkRCPtr.h"
#include "mitkMesh.h"
#include "mitkOoCGlobalSettings.h"

/// mitkMeshToMeshFilter - abstract class specifies interface for mesh to mesh filter
///////////////////////////////////////////////////////////////////////////
/// mitkMeshToMeshFilter is an abstract class specifies interface for
/// mesh to mesh filter. This type of filter has a mesh input and 
/// generates a mesh as output.
class MITK_COMMON_API mitkMeshToMeshFilter : public mitkFilter
{
public:
    MITK_TYPE(mitkMeshToMeshFilter, mitkFilter)
        
        virtual void PrintSelf(ostream &os);
    
    ///////////////////////////////////////////////////////////////////////////
    /// Set the input mesh.
    /// \param mesh specify the input mesh
    ///////////////////////////////////////////////////////////////////////////
    void SetInput(mitkMesh *mesh) { m_InData = mesh; }
    
    ///////////////////////////////////////////////////////////////////////////
    /// Get the input mesh
    /// \return Return the input mesh.
    ///////////////////////////////////////////////////////////////////////////
    mitkMesh* GetInput() { return m_InData; }
    
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
    /// \return Return the output mesh.
    ///////////////////////////////////////////////////////////////////////////
    mitkMesh* GetOutput()
    { if (m_OutData) return m_OutData; return (m_OutData=this->_createOutMesh()); }
    
    ///////////////////////////////////////////////////////////////////////////
    /// Set user defined output mesh to replace the default generated mesh.
    /// \param mesh the new output mesh object to be set
    ///////////////////////////////////////////////////////////////////////////
    void SetOutputMesh(mitkMesh *mesh);

protected:
    mitkMeshToMeshFilter();
    virtual ~mitkMeshToMeshFilter();

    virtual mitkMesh* _createOutMesh() = 0;

    mitkRCPtr<mitkMesh> m_InData;
    mitkMesh *m_OutData;

    mitkString *m_DiskPath;
    unsigned int m_BufferedBlockNum;
    
    bool m_NeedOoC;


private:
    mitkMeshToMeshFilter(const mitkMeshToMeshFilter&);
    void operator = (const mitkMeshToMeshFilter&);

};


//#define DEFINED_mitkMeshToMeshFilter



#endif

