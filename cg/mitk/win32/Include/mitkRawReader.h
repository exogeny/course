/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkRawReader_h
#define __mitkRawReader_h

#include "mitkVolumeReader.h"

/// mitkRawReader - a concrete reader for reading raw volume file(no header information).
///////////////////////////////////////////////////////////////////////////
/// mitkRawReader reads a raw volume file(no any header information) to a
/// volume. Because raw file doesn't has any header information, including
/// width, height, image number, spacing information, etc. , you must set
/// enough information using the series SetXXX functions. To use this reader,
/// the code snippet is: 
/// \code
/// mitkRawReader *aReader = new mitkRawReader; 
/// aReader->SetWidth(w); 
/// aReader->SetHeight(h); 
/// aReader->SetImageNum(d); 
/// aReader->SetSpacingX(sx); 
/// aReader->SetSpacingY(sy); 
/// aReader->SetSpacingZ(sz); 
/// aReader->SetDataType(dt); 
/// aReader->SetChannelNum(cn); 
/// aReader->AddFileName(filename); //Only require one file name 
/// //the above is the required information 
/// if (aReader->Run())
/// { 
///     mitkVolume *aVolume = aReader->GetOutput(); 
///     Using aVolume
/// }
/// \endcode
class MITK_COMMON_API mitkRawReader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkRawReader,mitkVolumeReader)
    
    virtual void PrintSelf(ostream& os);
    
    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////////
    mitkRawReader();    
       
    ///////////////////////////////////////////////////////////////////////
    /// Set image width.
    /// \param w image width
    ///////////////////////////////////////////////////////////////////////
    void SetWidth(int w){ m_Width = w;}
    
    ///////////////////////////////////////////////////////////////////////
    /// Set image height.
    /// \param h image height
    ///////////////////////////////////////////////////////////////////////
    void SetHeight(int h){ m_Height = h;}
    
    ///////////////////////////////////////////////////////////////////////
    /// Set number of images.
    /// \param n image number
    ///////////////////////////////////////////////////////////////////////
    void SetImageNum(int n){ m_ImageNum = n;}
    
    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in x axis, the unit is mm.
    /// \param px the spacing (mm) in two adjacent voxels in x axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingX(float px){ m_Spacings[0] = px; }

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in y axis, the unit is mm.
    /// \param py the spacing (mm) in two adjacent voxels in y axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingY(float py){ m_Spacings[1] = py; }

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in z axis, the unit is mm.
    /// \param pz the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingZ(float pz){ m_Spacings[2] = pz; }

    ///////////////////////////////////////////////////////////////////////
    /// Set number of channel.
    /// \param n number of channel
    /// 1---gray image
    /// 3---RGB image
    /// 4---RGBA image
    ///////////////////////////////////////////////////////////////////////
    void SetChannelNum(int n){ m_ChNum = n; }

    ///////////////////////////////////////////////////////////////////////
    /// Set number of bytes in title (header). These bytes will be skipped.
    /// \param n number of bytes in title (header)
    /// \note This title has nothing to do with the image.
    ///       If the file has a title, the number of bytes must be given
    ///       so that the program can skip the title properly when reading
    ///       the file.
    ///////////////////////////////////////////////////////////////////////
    void SetTitleBytes(int n) { m_TitleBytes = n; }
    
    ///////////////////////////////////////////////////////////////////////
    /// Set endian if depth per pixel is bigger than 8.
    /// \param isBig if the endian configuration is big endian (Mac)
    ///////////////////////////////////////////////////////////////////////
    void SetEndian(bool isBig = false) { m_IsBigEndian = isBig; }

    ///////////////////////////////////////////////////////////////////////////
    /// Provided for convenience, just the same as SetEndian().
    ///////////////////////////////////////////////////////////////////////////
    void SetBigEndian(bool isBig = true) { this->SetEndian(isBig); }

    ///////////////////////////////////////////////////////////////////////////
    /// Provided for convenience, just the same as SetEndian().
    ///////////////////////////////////////////////////////////////////////////
    void SetLittleEndian(bool isBig = false) { this->SetEndian(isBig); }

    ///////////////////////////////////////////////////////////////////////
    /// Set planar configuration.
    /// \param isColorByPlane if the planar configuration is color-by-plane
    /// \note Only used when channel number is bigger than 1.
    ///       For RGB images, if it is color-by-plane, it's means the pixels
    ///       should be stored as "R1 R2 R3 ... G1 G2 G3 ... B1 B2 B3 ...",
    ///       otherwise "R1 G1 B1 R2 G2 B2 ..."
    ///////////////////////////////////////////////////////////////////////
    void SetPlanarCfg(bool isColorByPlane) { m_IsColorByPlane = isColorByPlane; }

    ///////////////////////////////////////////////////////////////////////
    /// Set the data type of these images.
    /// \param dataType the data type of these images, the value should be
    ///        one of follows: \n
    ///        MITK_CHAR             (char)\n
    ///        MITK_UNSIGNED_CHAR    (unsigned char)\n
    ///        MITK_SHORT            (short)\n
    ///        MITK_UNSIGNED_SHORT   (unsigned short)\n
    ///        MITK_INT              (int)\n
    ///        MITK_UNSIGNED_INT     (unsigned int)\n
    ///        MITK_LONG             (long)\n
    ///        MITK_UNSIGNED_LONG    (unsigned long)\n
    ///        MITK_FLOAT            (float)\n
    ///        MITK_DOUBLE           (double)
    ///////////////////////////////////////////////////////////////////////
    void SetDataType(int dataType){ m_DataType = dataType; }

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to float.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToFloat(){this->SetDataType(MITK_FLOAT);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to double.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToDouble(){this->SetDataType(MITK_DOUBLE);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to int.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToInt(){this->SetDataType(MITK_INT);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to unsigned int.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedInt()
    {this->SetDataType(MITK_UNSIGNED_INT);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to long.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToLong(){this->SetDataType(MITK_LONG);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to unsigned long.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedLong()
    {this->SetDataType(MITK_UNSIGNED_LONG);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to short.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToShort(){this->SetDataType(MITK_SHORT);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to unsigned short.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedShort()
    {this->SetDataType(MITK_UNSIGNED_SHORT);}

    ///////////////////////////////////////////////////////////////////////
    /// Set data type to unsigned char.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedChar()
    {this->SetDataType(MITK_UNSIGNED_CHAR);}
    
    ///////////////////////////////////////////////////////////////////////
    /// Set data type to char.
    ///////////////////////////////////////////////////////////////////////
    void SetDataTypeToChar()
    {this->SetDataType(MITK_CHAR);}

protected:
    virtual ~mitkRawReader();   
    
    // Overriding.
    // Execute the reading operation.
    virtual bool Execute();
    
    bool  m_IsBigEndian;
    bool  m_IsColorByPlane;
    int   m_TitleBytes;
    int   m_Width;
    int   m_Height;
    int   m_ImageNum;
    int   m_ChNum;
    int   m_DataType;
    float m_Spacings[3];
    

private:
    mitkRawReader(const mitkRawReader&);
    void operator=(const mitkRawReader&);
    
};


//#define DEFINED_mitkRawReader



#endif


