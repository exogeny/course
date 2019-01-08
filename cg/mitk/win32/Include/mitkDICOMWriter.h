/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkDICOMWriter_h
#define __mitkDICOMWriter_h

#include "mitkVolumeWriter.h"

/// mitkDICOMWriter - a concrete writer for writing a volume to DICOM image files
///////////////////////////////////////////////////////////////////////////
/// mitkDICOMWriter writes a volume to a set of DICOM image files. Because the
/// volume is a 3D dataset, it may contain many slices. So the file names 
/// must be generated and passed to writer properly. \n
/// DICOM files to be writen will take format as follows: \n
///     Media Storage SOP Class : Not Specified (UID = ""); \n
///     Media Storage SOP Instance : Not Specified (UID = ""); \n
///     Transfer Syntax : Explicit VR Little Endian (UID = "1.2.840.10008.1.2.1"); \n
///     Implementation Class : Not Specified (UID = ""); \n
///     Implementation Version Name : Ignored; \n
///     Source Application Entity Title : Ignored; \n
///     Private Information Creator UID and Private Information : Ignored; \n
///
///     Each file will contain one single image of an image series. \n
/// To use this writer, the code snippet is: 
/// \code
/// mitkDICOMWriter *aWriter = new mitkDICOMWriter; 
/// aWriter->SetInput(aVolume); 
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///     aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkDICOMWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkDICOMWriter,mitkVolumeWriter)
    
    virtual void PrintSelf(ostream& os);
    
    mitkDICOMWriter();    

    ///////////////////////////////////////////////////////////////////////
    /// Set Study UID.
    /// \param uid a const reference to a string contains UID
    ///////////////////////////////////////////////////////////////////////
    void SetStudyUID(const string &uid);

    ///////////////////////////////////////////////////////////////////////
    /// Set Series UID.
    /// \param uid a const reference to a string contains UID
    ///////////////////////////////////////////////////////////////////////
    void SetSeriesUID(const string &uid);

protected:
    virtual ~mitkDICOMWriter(); 
    
    // Overriding.
    // Execute the writing operation.
    virtual bool Execute();

    char m_StudyUID[65];
    char m_SeriesUID[65];

private:
    mitkDICOMWriter(const mitkDICOMWriter&);
    void operator=(const mitkDICOMWriter&);
};
#endif

