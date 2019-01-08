/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkPLYBinaryWriter_h
#define __mitkPLYBinaryWriter_h

#include "mitkMeshWriter.h"

/// mitkPLYBinaryWriter - a concrete writer for writing a mesh to PLY files with binary format
///////////////////////////////////////////////////////////////////////////
/// mitkPLYBinaryWriter is a concrete writer for writing a mesh to PLY files
/// with binary format. PLY is a file format developed by Stanford University
/// for exchanging data like meshes and 3D scans. To use this writer,
/// the code snippet is: 
/// \code
/// mitkPLYASCIIWriter *aWriter = new mitkPLYASCIIWriter; 
/// aWriter->SetInput(aMesh); 
/// aWriter->AddFileName(filename); 
/// aWriter->SetBigEndian(true); //Default is little endian
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkPLYBinaryWriter : public mitkMeshWriter
{
public:
    MITK_TYPE(mitkPLYBinaryWriter, mitkMeshWriter)

    virtual void PrintSelf(ostream &os);

    mitkPLYBinaryWriter();

//  void SetVertexWriteBufferSize(unsigned int n) { m_VertWriteBufSize = n; }
//  void SetFaceWriteBufferSize(unsigned int n) { m_FaceWriteBufSize = n; }

    void SetBigEndian(bool bigEndian = true) { m_IsBigEndian = bigEndian; }

protected:
    virtual ~mitkPLYBinaryWriter();

    virtual bool Execute();

//  unsigned int m_VertWriteBufSize;
//  unsigned int m_FaceWriteBufSize;

    bool m_IsBigEndian;

private:
    mitkPLYBinaryWriter(const mitkPLYBinaryWriter&);
    void operator = (const mitkPLYBinaryWriter&);

};


//#define DEFINED_mitkPLYBinaryWriter



#endif

