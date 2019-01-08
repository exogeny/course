/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkTIFFWriter_h
#define __mitkTIFFWriter_h

#include "mitkVolumeWriter.h"

/// mitkTIFFWriter - a concrete writer for writing a volume to TIFF image files
///////////////////////////////////////////////////////////////////////////
/// mitkTIFFWriter writes a volume to a set of TIFF image files. Because the
/// volume is a 3D dataset, it may contain many slices. So the file names 
/// must be generated and passed to writer properly. To use this writer,
/// the code snippet is: 
/// \code
/// mitkTIFFWriter *aWriter = new mitkTIFFWriter; 
/// aWriter->SetInput(aVolume); 
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///     aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkTIFFWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkTIFFWriter,mitkVolumeWriter)
    
    virtual void PrintSelf(ostream& os);
    
    mitkTIFFWriter();    

protected:
    virtual ~mitkTIFFWriter();          
    
    virtual bool Execute();
    
private:
    mitkTIFFWriter(const mitkTIFFWriter&){};
    void operator=(const mitkTIFFWriter&){};

};


//#define DEFINED_mitkTIFFWriter



#endif

