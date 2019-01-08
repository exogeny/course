/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkNetCDFImageReader_h
#define __mitkNetCDFImageReader_h

#include "mitkVolumeReader.h"

struct TokenName
{
    char*   VolumeData_var;
    char*   Hist1D_var;             // deprecated
    char*   Channels_dim;
    char*   Width_dim;
    char*   Height_dim;
    char*   Slice_dim;
    char*   Time_dim;               // deprecated
    char*   Spacing_att;
    char*   VoxelType_att;
    char*   VoxelUnit_att;          // deprecated
    char*   Origin_att;             // deprecated
    char*   TransformMatrix_att;    // deprecated
    char*   Description_att;
};

/// mitkNetCDFImageReader -
///////////////////////////////////////////////////////////////////////////
/// mitkNetCDFImageReader
///
class MITK_COMMON_API mitkNetCDFImageReader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkNetCDFImageReader, mitkVolumeReader)

    virtual void PrintSelf(ostream &os);

    mitkNetCDFImageReader();

protected:
    virtual ~mitkNetCDFImageReader();

    virtual bool Execute();

private:
    mitkNetCDFImageReader(const mitkNetCDFImageReader&);
    void operator = (const mitkNetCDFImageReader&);

    struct TokenName    m_TokenName;

};


//#define DEFINED_mitkNetCDFImageReader



#endif

