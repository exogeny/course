/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkSource_h
#define __mitkSource_h

#include "mitkProcessObject.h"

/// mitkSource - abstract class specifies interface for source object
///////////////////////////////////////////////////////////////////////////
/// mitkSource is an abstract object that specifies behavior and interface
/// of source objects. Source objects are creators of data objects, including
/// reader and procedual source.
class MITK_COMMON_API mitkSource : public mitkProcessObject
{
public:
    MITK_TYPE(mitkSource,mitkProcessObject)

    virtual void PrintSelf(ostream& os);    

protected:
    mitkSource();
    virtual ~mitkSource();
    
private:
    mitkSource(const mitkSource&);
    void operator=(const mitkSource&);

};



//#define DEFINED_mitkSource



#endif





