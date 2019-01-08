/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkCacheVolumeReader_h
#define __mitkCacheVolumeReader_h

#include "mitkVolumeReader.h"

/// mitkCacheVolumeReader - a volume reader for reading out-of-core volume cache files
///////////////////////////////////////////////////////////////////////////
/// mitkCacheVolumeReader is a volume reader to read out-of-core volume cache files.
/// It directly reuses the existed cache files of an out-of-core volume and
/// makes the reading process fast. To use this reader,
/// the code snippet is: 
/// \code
/// mitkCacheVolumeReader *aReader = new mitkCacheVolumeReader; 
/// aReader->AddFileName(file); // a config file contains the volume parameters
/// if (aReader->Run())
/// { 
///     mitkVolume *aVolume = aReader->GetOutput(); 
///     Using aVolume
/// }
/// \endcode
/// \note Use mitkCacheVolumeWriter to generate the config file which contains
///       the volume parameters and 
///       tell the mitkOoCVolume keep the cache files.
class MITK_COMMON_API mitkCacheVolumeReader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkCacheVolumeReader, mitkVolumeReader)

    virtual void PrintSelf(ostream &os);

    mitkCacheVolumeReader();

    ///////////////////////////////////////////////////////////////////////
    /// Set if the config file is a binary file. Binary config file gives
    /// a quick and accurate reading.
    /// \param b whether the config file is binary
    ///////////////////////////////////////////////////////////////////////
    void SetConfigFileToBinary(bool b=true) { m_IsCfgFileBinary = b; }

protected:
    virtual ~mitkCacheVolumeReader();
    
    virtual bool Execute();

    bool m_IsCfgFileBinary;

private:
    mitkCacheVolumeReader(const mitkCacheVolumeReader&);
    void operator = (const mitkCacheVolumeReader&);

};


#endif

