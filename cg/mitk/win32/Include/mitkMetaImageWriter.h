/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMetaImageWriter_h
#define __mitkMetaImageWriter_h

#include "mitkVolumeWriter.h"

namespace metaio { class MetaImage; } // forward declaration

/// mitkMetaImageWriter -
///////////////////////////////////////////////////////////////////////////
/// mitkMetaImageWriter
///
class MITK_COMMON_API mitkMetaImageWriter : public mitkVolumeWriter
{
public:
    MITK_TYPE(mitkMetaImageWriter, mitkVolumeWriter)

    virtual void PrintSelf(ostream &os);

    mitkMetaImageWriter();

    // Specify the file name of the raw image data.
    void SetRAWFileName(char* fname);
    const char* GetRAWFileName();

    void SetCompression( bool compress ) { this->Compress = compress; }
    bool GetCompression() { return this->Compress; }

    void SetFileDimensionality(int d) { FileDimensionality = d; }
    int GetFileDimensionality() { return FileDimensionality; }

protected:
    virtual ~mitkMetaImageWriter();

    virtual bool Execute();

private:
    mitkMetaImageWriter(const mitkMetaImageWriter&);
    void operator = (const mitkMetaImageWriter&);

    metaio::MetaImage * MetaImagePtr;

    char* RAWFileName;
    bool Compress;
    int FileLowerLeft;
    int FileDimensionality;
};


//#define DEFINED_mitkMetaImageWriter



#endif

