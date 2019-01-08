/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkPLYReader_h
#define __mitkPLYReader_h

#include "mitkMeshReader.h"

/// mitkPLYReader - a concrete reader for reading a PLY file
///////////////////////////////////////////////////////////////////////////
/// mitkPLYReader is a concrete reader for reading a PLY file.
/// PLY is a file format developed by Stanford University for
/// exchanging data like meshes and 3D scans. To use this writer,
/// the code snippet is: 
/// \code
/// mitkPLYReader *aReader = new mitkPLYReader; 
/// aReader->AddFileName(filename); 
/// if (aReader->Run())
/// {
///     mitkMesh *aMesh = aReader->GetOutput();
///     Using aMesh
/// }
/// \endcode
class MITK_COMMON_API mitkPLYReader : public mitkMeshReader
{
public:
    MITK_TYPE(mitkPLYReader, mitkMeshReader)

    virtual void PrintSelf(ostream &os);

    mitkPLYReader();

    void SetVertexReadBufferSize(unsigned int n) { m_VertReadBufSize = n; }
    void SetFaceReadBufferSize(unsigned int n) { m_FaceReadBufSize = n; }

protected:
    virtual ~mitkPLYReader();

    virtual bool Execute();

    unsigned int m_VertReadBufSize;
    unsigned int m_FaceReadBufSize;

private:
    mitkPLYReader(const mitkPLYReader&);
    void operator = (const mitkPLYReader&);

};


//#define DEFINED_mitkPLYReader



#endif

