/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkAnalyzeImageWriter_h
#define __mitkAnalyzeImageWriter_h

#include "mitkAnalyzeImageReader.h"
#include "mitkVolumeWriter.h"


/// mitkAnalyzeImageWriter -
///////////////////////////////////////////////////////////////////////////
/// mitkAnalyzeImageWriter
///
class MITK_COMMON_API mitkAnalyzeImageWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkAnalyzeImageWriter, mitkVolumeWriter)

    virtual void PrintSelf(ostream &os);

    mitkAnalyzeImageWriter();

protected:
    virtual ~mitkAnalyzeImageWriter();

    virtual bool Execute();

    bool WriteInfo();
    bool WriteData();

private:
    mitkAnalyzeImageWriter(const mitkAnalyzeImageWriter&);
    void operator = (const mitkAnalyzeImageWriter&);

    struct dsr  m_Hdr;
};

#endif

