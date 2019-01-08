/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2008-12-31 
  Version:   $Version: 2.2
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences
  Last Modified by: Zhang Xing

=========================================================================*/
#ifndef __mitkSTLReader_h
#define __mitkSTLReader_h

#include "mitkMeshReader.h"

/// mitkSTLReader - a concrete reader for reading a STL file
///////////////////////////////////////////////////////////////////////////
/// mitkSTLReader is a concrete reader for reading a STL file.
/// the code snippet is: 
/// \code
/// mitkSTLReader *aReader = new mitkSTLReader; 
/// aReader->AddFileName(filename); 
/// if (aReader->Run())
/// {
///     mitkMesh *aMesh = aReader->GetOutput();
///     Using aMesh
/// }
/// \endcode
class MITK_COMMON_API mitkSTLReader: public mitkMeshReader
{
public:
    MITK_TYPE(mitkSTLReader, mitkMeshReader)

    virtual void PrintSelf(ostream &os);

    mitkSTLReader();

protected:
    virtual ~mitkSTLReader();

    virtual bool Execute();

private:
    bool OpenBinary(const char * filename, mitkMesh *mesh);  //open binary STL file
    bool OpenAscii(const char * filename, mitkMesh *mesh);   //open ASCII STL file
    mitkSTLReader(const mitkSTLReader&);
    void operator = (const mitkSTLReader&);

};

//#ifdef MITK_DLL_EXPORT
//#define DEFINED_mitkSTLReader
//#include "mitkTemplateExport.h"
//#endif      // MITK_DLL_EXPORT

#endif
