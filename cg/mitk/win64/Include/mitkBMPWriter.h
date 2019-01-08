/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkBMPWriter_h
#define __mitkBMPWriter_h

#include "mitkVolumeWriter.h"

/// mitkBMPWriter - a concrete writer for writing a volume to BMP image files
///////////////////////////////////////////////////////////////////////////
/// mitkBMPWriter writes a volume to a set of BMP image files. Because the
/// volume is a 3D dataset, it may contain many slices. So the file names 
/// must be generated and passed to writer properly. To use this writer,
/// the code snippet is: 
/// \code
/// mitkBMPWriter *aWriter = new mitkBMPWriter; 
/// aWriter->SetInput(aVolume); 
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///     aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkBMPWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkBMPWriter,mitkVolumeWriter)
    
    virtual void PrintSelf(ostream& os);
    
    mitkBMPWriter();    

protected:
    virtual ~mitkBMPWriter();       
    
    virtual bool Execute();
    
    #pragma pack(2)
    typedef struct  tagBITMAPFILEHEADER
    {
        unsigned short  bfType; 
        unsigned long   bfSize; 
        unsigned short  bfReserved1; 
        unsigned short  bfReserved2; 
        unsigned long   bfOffBits;
        unsigned long   biSize;
        unsigned long   biWidth;
        unsigned long   biHeight;
        unsigned short  biPlanes;
        unsigned short  biBitCount;
        unsigned long   biCompression;
        unsigned long   biSizeImage;
        unsigned long   biXPelsPerMeter;
        unsigned long   biYPelsPerMeter;
        unsigned long   biClrUsed;
        unsigned long   biClrImportant;
    }   BITMAPFILEHEADER; 
    #pragma pack()
private:
    mitkBMPWriter(const mitkBMPWriter&){};
    void operator=(const mitkBMPWriter&){};

};


#endif

