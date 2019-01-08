/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkCacheVolumeWriter_h
#define __mitkCacheVolumeWriter_h

#include "mitkVolumeWriter.h"

/// mitkCacheVolumeWriter - a volume writer for reusing out-of-core volume cache files
///////////////////////////////////////////////////////////////////////////
/// mitkCacheVolumeWriter is a volume writer for reusing out-of-core volume
/// cache files. It will generate a config file which contains the volume
/// parameters and the out-of-core settings. It also tell the input volume
/// to keep the cache files. This file can be read and 
/// resolved by mitkCacheVolumeReader.
/// To use this writer, the code snippet is: 
/// \code
/// mitkCacheVolumeWriter *aWriter = new mitkCacheVolumeWriter; 
/// aWriter->SetInput(aVolume); 
/// aWriter->AddFileName(filename); 
/// aWriter->SetConfigFileToBinary(isBin);
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkCacheVolumeWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkCacheVolumeWriter, mitkVolumeWriter)

    virtual void PrintSelf(ostream &os);

    mitkCacheVolumeWriter();

    ///////////////////////////////////////////////////////////////////////
    /// Set the config file to binary file.  Binary config file gives
    /// a quick and accurate reading.
    /// \param b whether or not to set the config file to binary
    ///////////////////////////////////////////////////////////////////////
    void SetConfigFileToBinary(bool b=true) { m_IsCfgFileBinary = b; }

protected:
    virtual ~mitkCacheVolumeWriter();

    virtual bool Execute();

    bool _writeBinaryFile(char const *filename);

    bool m_IsCfgFileBinary;

private:
    mitkCacheVolumeWriter(const mitkCacheVolumeWriter&);
    void operator = (const mitkCacheVolumeWriter&);

};


//#define DEFINED_mitkCacheVolumeWriter



#endif

