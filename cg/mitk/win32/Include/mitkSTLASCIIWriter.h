/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkSTLASCIIWriter_h
#define __mitkSTLASCIIWriter_h

#include "mitkMeshWriter.h"

/// mitkSTLASCIIWriter - a concrete writer for writing a mesh to STL (STereo Lithography) file using ASCII format
///////////////////////////////////////////////////////////////////////////
/// mitkSTLASCIIWriter writes a mesh to a STL file using ASCII format.  To use this 
/// writer, the code snippet is:
/// \code
/// mitkIM0Writer *aWriter = new mitkSTLASCIIWriter; 
/// aWriter->SetInput(aMesh); 
/// aWriter->AddFileName(filename); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkSTLASCIIWriter : public mitkMeshWriter
{
public:
    MITK_TYPE(mitkSTLASCIIWriter, mitkMeshWriter)

    virtual void PrintSelf(ostream &os);

    mitkSTLASCIIWriter();

protected:
    virtual ~mitkSTLASCIIWriter();

    virtual bool Execute();

private:
    mitkSTLASCIIWriter(const mitkSTLASCIIWriter&);
    void operator = (const mitkSTLASCIIWriter&);

};


//#define DEFINED_mitkSTLASCIIWriter



#endif

