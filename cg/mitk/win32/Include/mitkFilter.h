/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkFilter_h
#define __mitkFilter_h

#include "mitkProcessObject.h"

/// mitkFilter - abstract class specifies interface for filter object
///////////////////////////////////////////////////////////////////////////
/// mitkFilter is an abstract object that specifies behavior and interface
/// of filter objects. Filter object representation a algorithm that process
/// input data and return the output data.
class MITK_COMMON_API mitkFilter : public mitkProcessObject
{
public:
    MITK_TYPE(mitkFilter,mitkProcessObject)

    virtual void PrintSelf(ostream& os);
    
protected:
    mitkFilter();
    virtual ~mitkFilter();
    
private:
    mitkFilter(const mitkFilter&);
    void operator=(const mitkFilter&);
};

#endif


