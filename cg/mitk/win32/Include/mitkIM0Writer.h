/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkIM0Writer_h
#define __mitkIM0Writer_h

#include "mitkVolumeWriter.h"

/// mitkIM0Writer - a concrete writer for writing a volume to IM0 volume file
///////////////////////////////////////////////////////////////////////////
/// mitkIM0Writer writes a volume to a single IM0 file. Because the IM0 file
/// format can contain 3D dataset, a single file name is sufficient for this
/// writer to work. To use this writer, the code snippet is: 
/// \code
/// mitkIM0Writer *aWriter = new mitkIM0Writer; 
/// aWriter->SetInput(aVolume); 
/// aWriter->AddFileName(filename); 
/// aWriter->Run(); 
/// \endcode
/// \warning The IM0 file format is originally used in 3DVIEWNIX software
/// developed by MIPG group, University of Pennsylvania. Maybe the file
/// format is copyrighted. Please use it in your own risk.
class MITK_COMMON_API mitkIM0Writer : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkIM0Writer,mitkVolumeWriter)

    mitkIM0Writer(){};


protected:
    virtual ~mitkIM0Writer();
    virtual bool Execute();

private:
    void operator=(const mitkIM0Writer&);
    mitkIM0Writer(const mitkVolumeWriter&);
};


#endif


