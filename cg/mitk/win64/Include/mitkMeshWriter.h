/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMeshWriter_h
#define __mitkMeshWriter_h

#include "mitkWriter.h"
#include "mitkMesh.h"
#include "mitkRCPtr.h"

/// mitkMeshWriter - an abstract class represents a mesh writer for writing mesh data to disk
///////////////////////////////////////////////////////////////////////////
/// mitkMeshWriter is an abstract class represents a mesh writer for writing 
/// mesh data to disk. To use a concrete mesh reader, the code snippet is: 
/// \code
/// mitkSomeMeshWriter *aWriter = new mitkSomeMeshWriter; 
/// aWriter->SetInput(aMesh);
/// aWriter->AddFileName(filename); //Only require one file name 
/// aWriter->Run()
/// \endcode
class MITK_COMMON_API mitkMeshWriter : public mitkWriter
{
public:
    MITK_TYPE(mitkMeshWriter, mitkWriter)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////
    /// Set input mesh to write to disk file.
    /// \param inData Input volume
    ///////////////////////////////////////////////////////////////////////
    void SetInput(mitkMesh *inData) {m_InData = inData;}

    ///////////////////////////////////////////////////////////////////////
    /// Get input mesh.
    /// \return Return the input volume
    ///////////////////////////////////////////////////////////////////////
    mitkMesh* GetInput() {return m_InData;}

protected:
    mitkMeshWriter();
    virtual ~mitkMeshWriter();

    mitkRCPtr<mitkMesh> m_InData;

private:
    mitkMeshWriter(const mitkMeshWriter&);
    void operator = (const mitkMeshWriter&);

};


//#define DEFINED_mitkMeshWriter



#endif

