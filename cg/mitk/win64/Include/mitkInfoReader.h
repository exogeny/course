/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





#ifndef __mitkInfoReader_h
#define __mitkInfoReader_h

#include "mitkReader.h"

/// mitkInfoReader - an abstract class represents an information reader
///////////////////////////////////////////////////////////////////////////
/// mitkInfoReader is an abstract class represents an information reader.
/// Generally, it reads the header information of some files (e.g. DICOM files).
class MITK_COMMON_API mitkInfoReader : public mitkReader
{
public:
    MITK_TYPE(mitkInfoReader, mitkReader)

    virtual void PrintSelf(ostream &os);

    mitkInfoReader();

protected:
    virtual ~mitkInfoReader();

private:
    mitkInfoReader(const mitkInfoReader&);
    void operator = (const mitkInfoReader&);

};


#endif

