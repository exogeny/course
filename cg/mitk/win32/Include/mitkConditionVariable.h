/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkConditionVariable_h
#define __mitkConditionVariable_h

#include "mitkObject.h"
// An abstract class defining the interface of a  implementor
class mitkConditionVariableImp
{
public:
    mitkConditionVariableImp(){}
    ~mitkConditionVariableImp(){}

    virtual void LockMutex()=0;
    virtual void UnlockMutex()=0;
    virtual void Wait()=0;
    virtual void BroadCast()=0;
};

/// mitkConditionVariable - a class that encapsulates a condition variable
///////////////////////////////////////////////////////////////////////////
/// mitkConditionVariable encapsulates a condition variable. 
class MITK_COMMON_API mitkConditionVariable : public mitkObject
{
public:
    MITK_TYPE(mitkConditionVariable,mitkObject)
    mitkConditionVariable();
    void LockMutex()
    {
        m_Imp->LockMutex();
    }
    void UnlockMutex()
    {
        m_Imp->UnlockMutex();
    }
    void Wait()
    {
        m_Imp->Wait();
    }
    void BroadCast()
    {
        m_Imp->BroadCast();
    }
protected:
    virtual ~mitkConditionVariable();
private:
    mitkConditionVariable(const mitkConditionVariable&);
    void operator = (const mitkConditionVariable&);
    mitkConditionVariableImp *m_Imp;
};
#endif


