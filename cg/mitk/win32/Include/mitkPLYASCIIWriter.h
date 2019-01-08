/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkPLYASCIIWriter_h
#define __mitkPLYASCIIWriter_h

#include "mitkMeshWriter.h"

/// mitkPLYASCIIWriter - a concrete writer for writing a mesh to PLY files with ASCII format
///////////////////////////////////////////////////////////////////////////
/// mitkPLYASCIIWriter is a concrete writer for writing a mesh to PLY files
/// with ASCII format. PLY is a file format developed by Stanford University
/// for exchanging data like meshes and 3D scans. 
/// To use this writer, the code snippet is: 
/// \code
/// mitkPLYASCIIWriter *aWriter = new mitkPLYASCIIWriter; 
/// aWriter->SetInput(aMesh); 
/// aWriter->AddFileName(filename); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkPLYASCIIWriter : public mitkMeshWriter
{
public:
    MITK_TYPE(mitkPLYASCIIWriter, mitkMeshWriter)

    virtual void PrintSelf(ostream &os);

    mitkPLYASCIIWriter();

protected:
    virtual ~mitkPLYASCIIWriter();

    virtual bool Execute();

private:
    mitkPLYASCIIWriter(const mitkPLYASCIIWriter&);
    void operator = (const mitkPLYASCIIWriter&);

};


//#define DEFINED_mitkPLYASCIIWriter



#endif

