/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkBMPReader_h
#define __mitkBMPReader_h

#include "mitkVolumeReader.h"

/// mitkBMPReader - a concrete reader for reading BMP image files
///////////////////////////////////////////////////////////////////////////
/// mitkBMPReader reads a set of BMP image files to a volume. Because BMP
/// file doesn't have the spacing information, you must set them using the
/// SetSpacingX, SetSpacingY, SetSpacingZ functions. To use this reader,
/// the code snippet is: 
/// \code
/// mitkBMPReader *aReader = new mitkBMPReader; 
/// aReader->SetSpacingX(sx); 
/// aReader->SetSpacingY(sy); 
/// aReader->SetSpacingZ(sz); 
/// aReader->AddFileName(file1);
/// aReader->AddFileName(file2);
/// ...  ...  ... 
/// if (aReader->Run())
/// { 
///     mitkVolume *aVolume = aReader->GetOutput(); 
///     Using aVolume
/// }
/// \endcode
/// \warning All of the images must have equal width and height. Otherwise
/// they can't form a volume. Now MITK only supports 8 bits and 24 bits 
/// BMP files.
class MITK_COMMON_API mitkBMPReader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkBMPReader,mitkVolumeReader)
    
    virtual void PrintSelf(ostream& os);
    
    mitkBMPReader();
    
    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in x axis, the unit is mm.
    /// \param px the spacing (mm) in two adjacent voxels in x axis.
    /////////////////////////////////////////////////////////////////////// 
    void SetSpacingX(float px){ m_Spacings[0] = px ;}

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in y axis, the unit is mm.
    /// \param py the spacing (mm) in two adjacent voxels in y axis.
    /////////////////////////////////////////////////////////////////////// 
    void SetSpacingY(float py){ m_Spacings[1] = py ;}

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in z axis, the unit is mm.
    /// \param pz the spacing (mm) in two adjacent voxels in z axis.
    /////////////////////////////////////////////////////////////////////// 
    void SetSpacingZ(float pz){ m_Spacings[2] = pz ;}

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in x, y, z axis respectively, the unit is mm.
    /// \param px the spacing (mm) in two adjacent voxels in x axis.
    /// \param py the spacing (mm) in two adjacent voxels in y axis.
    /// \param pz the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacings(float s[3])
    {
        m_Spacings[0] = s[0];
        m_Spacings[1] = s[1];
        m_Spacings[2] = s[2];
    }
    
protected:
    virtual ~mitkBMPReader();    
    
    virtual bool Execute();
    
    #pragma pack(2)
    typedef struct tagBITMAPFILEHEADER
    { 
        unsigned short    bfType; 
        unsigned long   bfSize; 
        unsigned short    bfReserved1; 
        unsigned short    bfReserved2; 
        unsigned long   bfOffBits; 
    } BITMAPFILEHEADER;
    #pragma pack()  


    typedef struct tagBITMAPINFOHEADER
    {
        unsigned long  biSize; 
        unsigned long   biWidth; 
        unsigned long   biHeight; 
        unsigned short   biPlanes; 
        unsigned short   biBitCount; 
        unsigned long  biCompression; 
        unsigned long  biSizeImage; 
        unsigned long   biXPelsPerMeter; 
        unsigned long   biYPelsPerMeter; 
        unsigned long  biClrUsed; 
        unsigned long  biClrImportant; 
    } BITMAPINFOHEADER;


    typedef struct tag_bmp_core_header
    {
        unsigned long   bcSize; 
        unsigned short  bcWidth; 
        unsigned short  bcHeight; 
        unsigned short  bcPlanes; 
        unsigned short  bcBitCount; 
    } BMP_CORE_HEADER;  

    float m_Spacings[3];
  
private:
    mitkBMPReader(const mitkBMPReader&){};
    void operator=(const mitkBMPReader&){};
    
};

#endif

