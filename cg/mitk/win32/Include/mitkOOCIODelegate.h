/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkOoCIODelegate_h
#define __mitkOoCIODelegate_h

#include "mitkThread.h"
#include "mitkSemaphore.h"

template <class UserClass>
class mitkOoCIODelegate
{
public:
    mitkOoCIODelegate(UserClass* UserObject)
    {
        m_UserObject=UserObject;
        m_IOThreadWorking=false;
        m_IOStartSema=new mitkSemaphore;
        m_IOFinishSema=new mitkSemaphore;
        m_IOThread=new MITK_THREAD_MEMBER(mitkOoCIODelegate,this,_IOThreadEntrance);
        m_IOThread->Spawn();
        m_IOFunction=NULL;
    }
    virtual ~mitkOoCIODelegate()
    {
        m_IOThreadWorking=false;
        m_IOStartSema->Post();
        m_IOFinishSema->Post();
        m_IOThread->Wait();
        m_IOThread->Delete();
        m_IOFinishSema->Delete();
        m_IOStartSema->Delete();        
    }
    void IOStart(void (UserClass::*IOFunction)()=NULL)
    {
        if (m_IOThreadWorking) m_IOFinishSema->Wait();
        m_IOFunction=IOFunction;
        m_IOThreadWorking=true;
        m_IOStartSema->Post();
    }
    void IOWait()
    {
        if (m_IOThreadWorking)  
        {
            m_IOFinishSema->Wait();
            m_IOThreadWorking=false;
        }
    }
private:
    void _IOThreadEntrance(void *)
    {
        while(1)
        {
            m_IOStartSema->Wait();
            if (!m_IOThreadWorking) break;
            if (m_IOFunction) (m_UserObject->*m_IOFunction)();
            m_IOFinishSema->Post();
        }

    }
    UserClass* m_UserObject;
    void (UserClass::*m_IOFunction)();
    bool m_IOThreadWorking;
    mitkSemaphore *m_IOStartSema,*m_IOFinishSema;
    mitkThreadDelegate* m_IOThread;
};

#endif

