/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkSemaphore_h
#define __mitkSemaphore_h

#include "mitkObject.h"
// a non-interfacial abstract class, defining the interface of a semaphore implementor
class mitkSemaphoreImp
{
public:
    mitkSemaphoreImp(){}
    virtual ~mitkSemaphoreImp(){}
    virtual void Wait()=0;
    virtual void Post(int count)=0;

};

/// mitkSemaphore - a class that encapsulates a semaphore
///////////////////////////////////////////////////////////////////////////
/// mitkSemaphore encapsulates a semaphore. 
class MITK_COMMON_API mitkSemaphore: public mitkObject
{
public:
    MITK_TYPE(mitkSemaphore,mitkObject)
    mitkSemaphore(int initialValue=0);
    ///////////////////////////////////////////////////////////////////////////
    /// Wait for the semaphore object and decrease the count
    ///////////////////////////////////////////////////////////////////////////
    void Wait()
    {
        m_Imp->Wait();
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Add count to the semaphore object
    /// \param count Specify the count to be added to the semaphore object
    ///////////////////////////////////////////////////////////////////////////
    void Post(int count=1)
    {
        m_Imp->Post(count);
    }
protected:
    virtual ~mitkSemaphore();
private:
    mitkSemaphore(const mitkSemaphore&);
    void operator = (const mitkSemaphore&); 
    mitkSemaphoreImp *m_Imp;

};

#endif

