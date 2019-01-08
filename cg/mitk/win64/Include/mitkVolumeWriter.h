/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeWriter_h
#define __mitkVolumeWriter_h

#include "mitkWriter.h"
#include "mitkRCPtr.h"
#include "mitkVolume.h"

/// mitkVolumeWriter - an abstract class represents a volume writer for writing image/volume files to disk 
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeWriter defines the interface of all of the volume writers. 
/// To use a concrete writer, for example, mitkBMPWriter, the code snippet
/// is: 
/// \code
/// mitkBMPWriter *aWriter = new mitkBMPWriter; 
/// aWriter->SetInput(aVolume); 
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///     aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkVolumeWriter : public mitkWriter
{
public:
    MITK_TYPE(mitkVolumeWriter,mitkWriter)

    virtual void PrintSelf(ostream& os);    

    ///////////////////////////////////////////////////////////////////////
    /// Set input volume to write to disk file.
    /// \param inData Input volume
    ///////////////////////////////////////////////////////////////////////
    void SetInput(mitkVolume *inData) {m_InData = inData;}

    ///////////////////////////////////////////////////////////////////////
    /// Get input volume.
    /// \return Return the input volume
    ///////////////////////////////////////////////////////////////////////
    mitkVolume* GetInput() {return m_InData;}

protected:
    mitkVolumeWriter();
    virtual ~mitkVolumeWriter();    

    mitkRCPtr<mitkVolume> m_InData;
private:
    mitkVolumeWriter(const mitkVolumeWriter&);
    void operator=(const mitkVolumeWriter&);

};

 
//#define DEFINED_mitkVolumeWriter



#endif


