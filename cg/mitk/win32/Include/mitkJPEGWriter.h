/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkJPEGWriter_h
#define __mitkJPEGWriter_h

#include "mitkVolumeWriter.h"

/// mitkJPEGWriter - a concrete writer for writing a volume to JPEG image files
///////////////////////////////////////////////////////////////////////////
/// mitkJPEGWriter writes a volume to a set of JPEG image files. Because the
/// volume is a 3D dataset, it may contain many slices. So the file names 
/// must be generated and passed to writer properly. To use this writer,
/// the code snippet is: 
/// \code
/// mitkJPEGWriter *aWriter = new mitkJPEGWriter; 
/// aWriter->SetInput(aVolume); 
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///     aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkJPEGWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkJPEGWriter,mitkVolumeWriter)
    
    virtual void PrintSelf(ostream& os);
    
    mitkJPEGWriter();    

    ///////////////////////////////////////////////////////////////////////
    /// Set the quality of output JPEG images.
    /// \param quality The quality of output JPEG images. The maximum value
    /// is 100, and the default value is 95.
    ///////////////////////////////////////////////////////////////////////
    void SetQuality(int quality) {m_Quality = quality;}


protected: 
    virtual ~mitkJPEGWriter();  
    
    virtual bool Execute();
    
private:
    mitkJPEGWriter(const mitkJPEGWriter&){};
    void operator=(const mitkJPEGWriter&){};

    int m_Quality;
    
};


//#define DEFINED_mitkJPEGWriter



#endif





