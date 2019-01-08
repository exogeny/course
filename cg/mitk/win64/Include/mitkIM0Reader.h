/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkIM0Reader_h
#define __mitkIM0Reader_h

#include "mitkVolumeReader.h"

/// mitkIM0Reader - a concrete reader for reading IM0 volume file
///////////////////////////////////////////////////////////////////////////
/// mitkIM0Reader reads a IM0 volume file to a volume. IM0 file is a 3D data
/// file, and the spacing information can be obtained from the file header.
/// To use this reader, the code snippet is: 
/// \code
/// mitkIM0Reader *aReader = new mitkIM0Reader; 
/// aReader->AddFileName(filename); //Only require one file name 
/// if (aReader->Run())
/// { 
///     mitkVolume *aVolume = aReader->GetOutput(); 
///     Using aVolume
/// }
/// \endcode
/// \warning The IM0 file format is originally used in 3DVIEWNIX software
/// developed by MIPG group, University of Pennsylvania. Maybe the file
/// format is copyrighted. Please use it in your own risk.
class MITK_COMMON_API mitkIM0Reader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkIM0Reader,mitkVolumeReader)
  

    mitkIM0Reader(){};      

protected:
    virtual ~mitkIM0Reader();
    virtual bool Execute();    

private:
    void operator=(const mitkIM0Reader&);
    mitkIM0Reader(const mitkVolumeReader&);

};

#endif


