/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMetaImageReader_h
#define __mitkMetaImageReader_h

#include "mitkVolumeReader.h"

namespace metaio { class MetaImage; } // forward declaration 

/// mitkMetaImageReader -
///////////////////////////////////////////////////////////////////////////
/// mitkMetaImageReader
///
class MITK_COMMON_API mitkMetaImageReader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkMetaImageReader, mitkVolumeReader)

    virtual void PrintSelf(ostream &os);

    mitkMetaImageReader();

    const char * GetFileExtensions() { return ".mhd .mha"; }

    const char * GetDescriptiveName() { return "MetaIO Library: MetaImage"; } 

    void SetFileDimensionality(int d) { FileDimensionality = d; }
    int GetFileDimensionality() { return FileDimensionality; }

    void SetNumberOfScalarComponents(int n) { NumberOfScalarComponents = n; }
    int GetNumberOfScalarComponents() { return NumberOfScalarComponents; }

    void SetDataExtent(int d[6]) { for(int i=0;i<6;i++) DataExtent[i] = d[i]; }
    int* GetDataExtent() { return DataExtent; }

    void SetDataSpacing(double s[3]) { for(int i=0;i<3;i++) DataSpacing[i] = s[i]; }
    double* GetDataSpacing() { return DataSpacing; }

    void SetDataOrigin(double o[3]) { for(int i=0;i<3;i++) DataOrigin[i] = o[i]; }
    double* GetDataOrigin() { return DataOrigin; }

    void SetHeaderSize(unsigned long size) { HeaderSize = size; }
    unsigned long GetHeaderSize() { return HeaderSize; }


protected:
    virtual ~mitkMetaImageReader();

    virtual bool Execute();
    bool ReadInfo();
    bool ReadData();

private:
    mitkMetaImageReader(const mitkMetaImageReader&);
    void operator = (const mitkMetaImageReader&);

    int FileDimensionality;
    int DataScalarType;
    int NumberOfScalarComponents;
    int DataExtent[6];
    double DataSpacing[3];
    double DataOrigin[3];
    unsigned long HeaderSize;
    int FileLowerLeft;

    metaio::MetaImage *MetaImagePtr;

public:
    double GantryAngle;
    char PatientName[255];
    char PatientID[255];
    char Date[255];
    char Series[255];
    char Study[255];
    char ImageNumber[255];
    char Modality[255];
    char StudyID[255];
    char StudyUID[255];
    char TransferSyntaxUID[255];

    double RescaleSlope;
    double RescaleOffset;
    int BitsAllocated;
    char DistanceUnits[255];
    char AnatomicalOrientation[255];

};


//#define DEFINED_mitkMetaImageReader



#endif

