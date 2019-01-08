/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkSTLBinaryWriter_h
#define __mitkSTLBinaryWriter_h

#include "mitkMeshWriter.h"

/// mitkSTLBinaryWriter - a concrete writer for writing a mesh to STL (STereo Lithography) file using binary format
///////////////////////////////////////////////////////////////////////////
/// mitkSTLBinaryWriter writes a mesh to a STL file using binary format.  To use this 
/// writer, the code snippet is:
/// \code
/// mitkIM0Writer *aWriter = new mitkSTLBinaryWriter; 
/// aWriter->SetInput(aMesh); 
/// aWriter->AddFileName(filename); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkSTLBinaryWriter : public mitkMeshWriter
{
public:
    MITK_TYPE(mitkSTLBinaryWriter, mitkMeshWriter)

    virtual void PrintSelf(ostream &os);

    mitkSTLBinaryWriter();

protected:
    virtual ~mitkSTLBinaryWriter();

    virtual bool Execute();

private:
    mitkSTLBinaryWriter(const mitkSTLBinaryWriter&);
    void operator = (const mitkSTLBinaryWriter&);

};


//#define DEFINED_mitkSTLBinaryWriter



#endif

