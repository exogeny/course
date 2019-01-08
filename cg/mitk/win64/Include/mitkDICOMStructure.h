/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkDICOMStructure_h
#define __mitkDICOMStructure_h

typedef struct _dicom_element
{
    union 
    {
        unsigned long tag;
        struct 
        {
            unsigned short elementNum;
            unsigned short groupNum;
        };
    };
    unsigned long  length;
    void          *value;
    unsigned short VR;
    bool           isSequence;

} DICOMELEMENT;

 
#endif

