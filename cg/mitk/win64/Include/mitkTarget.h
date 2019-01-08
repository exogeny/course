/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkTarget_h
#define __mitkTarget_h

#include "mitkProcessObject.h"

/// mitkTarget - abstract class specifies interface for Target object
///////////////////////////////////////////////////////////////////////////
/// mitkTarget is an abstract object that specifies behavior and interface
/// of mapper objects. Mapper object representas end point for a data processing
/// pipeline, e.g. view or writer. It only accepts input data and either displays
/// the input data to a view or writes the input data to a disk file.
class MITK_COMMON_API mitkTarget : public mitkProcessObject
{
public:
    MITK_TYPE(mitkTarget,mitkProcessObject)

    virtual void PrintSelf(ostream& os);    

protected:
    mitkTarget();
    virtual ~mitkTarget();    

private:
    mitkTarget(const mitkTarget&);
    void operator=(const mitkTarget&);

};


//#define DEFINED_mitkTarget



#endif


