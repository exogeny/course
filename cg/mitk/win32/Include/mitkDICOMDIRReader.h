/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkDICOMDIRReader
#define __mitkDICOMDIRReader

#include "mitkReader.h"
class mitkDICOMDIRTree;

/// mitkDICOMDIRReader - A reader class that reads a DICOMDIR file from disk
///////////////////////////////////////////////////////////////////////////
/// mitkDICOMDIRReader is a reader class that reads a DICOMDIR file from disk.
/// The result is stored as mitkDICOMDIRTree
class MITK_COMMON_API mitkDICOMDIRReader:public mitkReader
{
public:
    MITK_TYPE(mitkDICOMDIRReader,mitkReader);
    mitkDICOMDIRReader(); 
    ///////////////////////////////////////////////////////////////////////////
    /// Get the output data
    /// \return Return the output data
    ///////////////////////////////////////////////////////////////////////////
    virtual mitkDICOMDIRTree* GetOutput();

protected:
    virtual ~mitkDICOMDIRReader();
    virtual bool Execute();
private:
    mitkDICOMDIRTree* m_TreeData;
};

#endif 