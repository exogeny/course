/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkDICOMReader_h
#define __mitkDICOMReader_h

#include "mitkVolumeReader.h"

// a struct contains a slice
typedef struct _slice
{
    bool        isColorByPxl;
    float       location;
    void       *value;
    mitkString *fileName;
} SLICE;

// a struct contains the basic information of a volume
typedef struct _volumeinfo
{
    int   width;
    int   height;
    int   imageNum;
    int   channelNum;
    int   cellBytes;
    float spacingX;
    float spacingY;
    float spacingZ;
    float windowCenter;
    float windowWidth;
    bool  isUnsigned;
} VOLUMEINFO;

//typedef vector<long> Integers;
//typedef vector<double> Doubles;

class SliceList;

/// mitkDICOMReader - a concrete reader for reading DICOM image files
///////////////////////////////////////////////////////////////////////////
/// mitkDICOMReader reads a set of DICOM image files to a volume. To use
/// this reader, the code snippet is:
/// \code
/// mitkDICOMReader *aReader = new mitkDICOMReader; 
/// aReader->AddFileName(file1); 
/// aReader->AddFileName(file2); 
/// ...  ...  ... 
/// if (aReader->Run())
/// { 
///     mitkVolume *aVolume = aReader->GetOutput(); 
///     Using aVolume
/// }
/// \endcode
/// \warning All of the images must have equal width and height. Otherwise
/// they can't form a volume. The files which have different width or height
/// will be discarded. Now MITK only partly supports the DICOM 3.0 standard.
class MITK_COMMON_API mitkDICOMReader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkDICOMReader,mitkVolumeReader)
    
    virtual void PrintSelf(ostream& os);
    
    mitkDICOMReader();    

protected:
    virtual ~mitkDICOMReader(); 

    // Overriding
    // Execute the reading operation.
    virtual bool Execute();

    // Clear old data.
    void _clear();

    // Pre-process: record slices' locations & sort slices by location.
    int _preProcess(VOLUMEINFO &info);

    // Adjust slices including changing plane configure and inserting new slices.
    //int _adjustSlices(const int width,       const int height, 
    //                const int channelNum,  const int cellBytes,
    //                const bool isUnsigned, const bool isSlice);

    // Read a single file.
    //int _readSingleFile(VOLUMEINFO &info);

    // Read a series.
    //int _readSeries(VOLUMEINFO &info);

    // Write data to a volume.
    int _writeToVolume(VOLUMEINFO &info);


    SliceList *m_Slices;
    float m_MinSpacingZ;
    float m_MaxSpacingZ;
    bool m_IsMultiFrame;
    bool m_NeedInsert;



private:
    mitkDICOMReader(const mitkDICOMReader&);
    void operator=(const mitkDICOMReader&);

};

#endif

