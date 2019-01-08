/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkObserver_h
#define __mitkObserver_h

#include "mitkObject.h"

/// mitkObserver - abstract base class for observers
///////////////////////////////////////////////////////////////////////////
/// mitkObserver is an abstract class for observers. All mitkObjects can
/// attach observers. You can derive from this class to get an actual 
/// observer processing the interaction between an mitkObject and the user
/// interface.
class MITK_COMMON_API mitkObserver : public mitkObject
{
public:
    MITK_TYPE(mitkObserver, mitkObject)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////
    /// Update the observer according to the changes of the mitkObject it
    /// is attached to. A working observer should implement this pure virtual
    /// function.
    ///////////////////////////////////////////////////////////////////////
    virtual void Update() = 0;

protected:
    mitkObserver();
    virtual ~mitkObserver();

private:
    mitkObserver(const mitkObserver&);
    void operator = (const mitkObserver&);

};


//#define DEFINED_mitkObserver



#endif

