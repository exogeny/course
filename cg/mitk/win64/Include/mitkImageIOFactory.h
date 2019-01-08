/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkImageIOFactory_h
#define __mitkImageIOFactory_h

#include "mitkProcessObject.h"
#include "mitkVolume.h"
#include "mitkOoCGlobalSettings.h"

#if defined(MITK_CC_MSVC)
    #pragma warning(disable:4251)
#endif

#define MITK_IMAGE_IO_READ      1
#define MITK_IMAGE_IO_WRITE     2

/// mitkImageIOFactory -
///////////////////////////////////////////////////////////////////////////
/// mitkImageIOFactory
///
class MITK_COMMON_API mitkImageIOFactory : public mitkProcessObject
{
public:
    MITK_TYPE(mitkImageIOFactory, mitkProcessObject)

    virtual void PrintSelf(ostream &os);

    mitkImageIOFactory(int mode);

    // NOTE: single file read and write only
    void SetFileName(const char* name);
    void SetFileName(const std::string & name);

    void SetSpacings(float x, float y, float z)
    { m_VoxelSpacing[0] = x; m_VoxelSpacing[1] = y; m_VoxelSpacing[2] = z; }

    void SetDimensions(int x, int y, int z)
    { m_Dimension[0] = x; m_Dimension[1] = y; m_Dimension[2] = z; }

    void SetNumberOfChannels(unsigned int n)
    { m_NumberOfChannels = n; }

    void SetDataType(int type)
    { m_DataType = type; }

    void SetInput(mitkVolume* vol);

    mitkVolume* GetOutput();

    enum FileFormat{ BMP, JPEG, TIFF, IM0, DICOM, RAW, META, HDR, NETCDF, UNKNOWN };

    FileFormat GetFileFormat();

#ifdef MITK_VER_OOC
    void SetOoCSupport(char const *diskPath=mitkOoCGlobalSettings::DiskCachePath, unsigned int bufSliceNum = mitkOoCGlobalSettings::BufferedSliceNumber, bool supportOoC = true);

protected:  
    std::string         m_DiskPath;
    unsigned int        m_BufferedSliceNum;
    bool                m_NeedOoC;
#endif

protected:
    mitkImageIOFactory();
    virtual ~mitkImageIOFactory();

    virtual bool Execute();

    bool ReadFromFile();
    bool WriteToFile();

    std::string GetFilenameName(const std::string& filename);
    std::string GetFilenameLastExtension(const std::string& filename);
    std::string GetFilenameWithoutLastExtension(const std::string& filename);
    bool FileIsDirectory(const char* name);
    bool FileExists(const char* filename, bool isFile = false);

    mitkVolume*     m_IOVolumePtr;
    int             m_Mode;
    std::string     m_Filename;

    // image info for raw file
    float           m_VoxelSpacing[3];
    int             m_Dimension[3];
    unsigned int    m_NumberOfChannels;
    int             m_DataType;

private:
    mitkImageIOFactory(const mitkImageIOFactory&);
    void operator = (const mitkImageIOFactory&);

};

#endif

