/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkNetCDFImageWriter_h
#define __mitkNetCDFImageWriter_h

#include "mitkVolumeWriter.h"
#include "mitkNetCDFImageReader.h"

/// mitkNetCDFImageWriter -
///////////////////////////////////////////////////////////////////////////
/// mitkNetCDFImageWriter
///
class MITK_COMMON_API mitkNetCDFImageWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkNetCDFImageWriter, mitkVolumeWriter)

    virtual void PrintSelf(ostream &os);

    mitkNetCDFImageWriter();

protected:
    virtual ~mitkNetCDFImageWriter();

    virtual bool Execute();

private:
    mitkNetCDFImageWriter(const mitkNetCDFImageWriter&);
    void operator = (const mitkNetCDFImageWriter&);

    struct TokenName    m_TokenName;

};


//#define DEFINED_mitkNetCDFImageWriter



#endif

