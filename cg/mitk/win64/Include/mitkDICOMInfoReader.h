/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkDICOMInfoReader_h
#define __mitkDICOMInfoReader_h

#include "mitkInfoReader.h"
#include "mitkDICOMStructure.h"

class DcmFile;

/// mitkDICOMInfoReader - a concrete reader for reading element information in DICOM files
///////////////////////////////////////////////////////////////////////////
/// mitkDICOMInfoReader is a concrete reader for reading element information
/// in DICOM files To use this reader, the code snippet is:
/// \code
/// mitkDICOMInfoReader *aReader = new mitkDICOMInfoReader; 
/// aReader->AddFileName(filename); //Only one file will be processed at a time
/// if (aReader->Run())
/// { 
///     DICOMELEMENT aElement;
///     if (aReader->GetDataElement(somedicomtag, aElement)
///     {
///         Using aElement
///     }
/// }
/// \endcode
class MITK_COMMON_API mitkDICOMInfoReader : public mitkInfoReader
{
public:
    MITK_TYPE(mitkDICOMInfoReader, mitkInfoReader)

    virtual void PrintSelf(ostream &os);

    mitkDICOMInfoReader();

    ///////////////////////////////////////////////////////////////////////////
    /// Get data element in the DICOM file.
    /// \param tag the tag of the data element to get from file
    /// \param element the DICOMELEMENT structure to contain the data element found
    ///        from the file (if the element has not been found, the value is 
    ///        unchanged)
    /// \return Return true if the data element is found in the file. 
    ///////////////////////////////////////////////////////////////////////////
    bool GetDataElement(unsigned long tag, DICOMELEMENT &element);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the description of the tag.
    /// \param tag the tag value
    /// \return Return the string of description of the tag.
    ///         Return NULL if the description of the tag has not been found.
    ///////////////////////////////////////////////////////////////////////////
    static const char* GetDescription(unsigned long tag);

protected:
    virtual ~mitkDICOMInfoReader();

    virtual bool Execute();

    DcmFile *m_DcmFile;

private:
    mitkDICOMInfoReader(const mitkDICOMInfoReader&);
    void operator = (const mitkDICOMInfoReader&);

};

#endif

