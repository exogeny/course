/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkMutex_h
#define __mitkMutex_h

#include "mitkObject.h"
// An abstract class defining the interface of a mutex implementor
class mitkMutexImp
{
public:
    mitkMutexImp(){}
    virtual ~mitkMutexImp(){}
    virtual void Lock()=0;
    virtual void Unlock()=0;
};

/// mitkMutex - a class that encapsulates a mutex
///////////////////////////////////////////////////////////////////////////
/// mitkMutex encapsulates a mutex. 
class MITK_COMMON_API mitkMutex: public mitkObject
{
public:
    MITK_TYPE(mitkMutex,mitkObject)
    mitkMutex();
    ///////////////////////////////////////////////////////////////////////////
    /// Lock the mutex object
    ///////////////////////////////////////////////////////////////////////////
    void Lock()
    {
        m_Imp->Lock();
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Unlock the mutex object
    ///////////////////////////////////////////////////////////////////////////
    void Unlock()
    {
        m_Imp->Unlock();
    }
protected:
    virtual ~mitkMutex();
private:
    mitkMutex(const mitkMutex&);
    void operator = (const mitkMutex&);
    mitkMutexImp *m_Imp;
};

#endif

