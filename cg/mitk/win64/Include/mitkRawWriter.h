/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkRawWriter_h
#define __mitkRawWriter_h

#include "mitkVolumeWriter.h"

/// mitkRawWriter - a concrete writer for writing a volume to a single raw file(no any header information).
///////////////////////////////////////////////////////////////////////////
/// mitkRawWriter writes a volume to a single raw file(no any header 
/// information). All the property of volume will lost, including the image
/// width, height, image number, spacing information, etc. You can control
/// the format of output file by setting the endian configuration, planar
/// configuration and header size.
/// \see SetEndian
/// \see SetPlanarCfg
/// \see SetTitleBytes
/// To use this writer, the code snippet is: 
/// \code
/// mitkRawWriter *aWriter = new mitkRawWriter; 
/// aWriter->SetInput(aVolume); 
/// aWriter->AddFileName(filename); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkRawWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkRawWriter,mitkVolumeWriter)
    
    virtual void PrintSelf(ostream& os);
    
    mitkRawWriter();    

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
    /// Set number of bytes in title.
    /// \param n number of bytes in title
    /// \note All the bytes in the title will be set to 00H.
    ///       This title has nothing to do with the image and will be ignored
    ///       when read.
    ///////////////////////////////////////////////////////////////////////
    void SetTitleBytes(int n) { m_TitleBytes = n; }

protected:
    virtual ~mitkRawWriter();    
    
    // Overriding.
    // Execute the reading operation.
    virtual bool Execute();

    bool  m_IsBigEndian;
    bool  m_IsColorByPlane;
    int   m_TitleBytes;

private:
    mitkRawWriter(const mitkRawWriter&);
    void operator=(const mitkRawWriter&);
};



//#define DEFINED_mitkRawWriter



#endif

