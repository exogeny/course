/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeReader_h
#define __mitkVolumeReader_h

#include "mitkReader.h"
#include "mitkOoCGlobalSettings.h"

class mitkVolume;
//class mitkString;

/// mitkVolumeReader - an abstract class represents a volume reader to read image/volume files
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeReader defines the interface of all of the volume readers.
/// To use a concrete volume reader, for example, mitkBMPReader, the code
/// snippet is: 
/// \code
/// mitkBMPReader *aReader = new mitkBMPReader; 
/// aReader->AddFileName(file1); 
/// aReader->AddFileName(file2); 
/// ...  ...  ... 
/// if (aReader->Run())
/// { 
///     mitkVolume *aVolume = aReader->GetOutput(); 
///     Using aVolume
/// }
/// \endcode
class MITK_COMMON_API mitkVolumeReader : public mitkReader
{
public:
    MITK_TYPE(mitkVolumeReader,mitkReader)

    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////
    /// Let the reader support out-of-core volume data.
    /// \param diskPath the path in the disk to cache the volume data
    /// \param bufSliceNum the number of slices to cache in the main memory
    /// \param supportOoC whether to turn on out-of-core support
    /// \note The parameter diskPath must be specified (not NULL) if you
    ///       really want to turn on out-of-core support, if not, the value
    ///       of supportOoC will be ignored even if it is set to true.
    ///////////////////////////////////////////////////////////////////////
    void SetOoCSupport(char const *diskPath=mitkOoCGlobalSettings::DiskCachePath, unsigned int bufSliceNum = mitkOoCGlobalSettings::BufferedSliceNumber, bool supportOoC = true);

    ///////////////////////////////////////////////////////////////////////
    /// Get the output volume the reader has read.
    /// \return the output volume.
    ///////////////////////////////////////////////////////////////////////
    mitkVolume* GetOutput();

protected:
    mitkVolumeReader();
    virtual ~mitkVolumeReader();    

    mitkVolume *m_OutData;

    mitkString *m_DiskPath;
    unsigned int m_BufferedSliceNum;

    bool m_NeedOoC;

private:
    mitkVolumeReader(const mitkVolumeReader&);
    void operator=(const mitkVolumeReader&);

};


//#define DEFINED_mitkVolumeReader



#endif


