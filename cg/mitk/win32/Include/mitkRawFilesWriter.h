/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkRawFilesWriter_h
#define __mitkRawFilesWriter_h

#include "mitkVolumeWriter.h"

/// mitkRawFilesWriter - a concrete writer for writing a volume to a a series of raw files.
///////////////////////////////////////////////////////////////////////////
/// mitkRawFilesWriter writes a volume to a series of raw files (one slice per file with no header 
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
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///     aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkRawFilesWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkRawFilesWriter, mitkVolumeWriter)

    virtual void PrintSelf(ostream &os);

    mitkRawFilesWriter();
    
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
    virtual ~mitkRawFilesWriter();
    
    // Overriding.
    // Execute the reading operation.
    virtual bool Execute();

    bool  m_IsBigEndian;
    bool  m_IsColorByPlane;
    int   m_TitleBytes;

private:
    mitkRawFilesWriter(const mitkRawFilesWriter&);
    void operator = (const mitkRawFilesWriter&);

};


//#define DEFINED_mitkRawFilesWriter

#endif

