/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMeshReader_h
#define __mitkMeshReader_h

#include "mitkReader.h"
#include "mitkOoCGlobalSettings.h"

class mitkMesh;

/// mitkMeshReader - an abstract class represents a mesh reader to read mesh files
///////////////////////////////////////////////////////////////////////////
/// mitkMeshReader is an abstract class represents a mesh reader to read mesh files.
/// To use a concrete mesh reader, the code snippet is: 
/// \code
/// mitkSomeMeshReader *aReader = new mitkSomeMeshReader; 
/// aReader->AddFileName(filename); //Only require one file name 
/// if (aReader->Run())
/// {
///     mitkMesh *aMesh = aReader->GetOutput(); 
///     Using aMesh 
/// }
/// \endcode
class MITK_COMMON_API mitkMeshReader : public mitkReader
{
public:
    MITK_TYPE(mitkMeshReader, mitkReader)

    virtual void PrintSelf(ostream &os);

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

    ///////////////////////////////////////////////////////////////////////
    /// Get the output mesh the reader has read.
    /// \return the output volume.
    ///////////////////////////////////////////////////////////////////////
    mitkMesh* GetOutput();

    void SetOutputMesh(mitkMesh *mesh);

protected:
    mitkMeshReader();
    virtual ~mitkMeshReader();

    mitkMesh *m_OutData;
    
    mitkString *m_DiskPath;
    unsigned int m_BufferedBlockNum;

    bool m_NeedOoC;

private:
    mitkMeshReader(const mitkMeshReader&);
    void operator = (const mitkMeshReader&);

};


//#define DEFINED_mitkMeshReader



#endif

