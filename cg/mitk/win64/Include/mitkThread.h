/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkThread_class
#define __mitkThread_class

#include "mitkObject.h"

class mitkThread;
// an abstract class defining the interface of a thread implementor
class mitkThreadImp
{
public:
    mitkThreadImp(mitkThread *thread,void (mitkThread::*run)());
    virtual ~mitkThreadImp();
    void Spawn()
    {
        _wait();
        _create();
    }
    void Wait()
    {
        _wait();    
    }
    struct ThreadEntrance
    {
        mitkThread *thread;
        void (mitkThread::*run)();
    };      
protected:
    virtual void _create()=0;
    virtual void _wait()=0;
    ThreadEntrance *GetThreadEntrance()
    {
        return &m_ThreadEntrance;
    }
private:
    ThreadEntrance m_ThreadEntrance;

};

/// mitkThread - a class that encapsulates a thread
///////////////////////////////////////////////////////////////////////////
/// mitkThread encapsulates a thread. 
class MITK_COMMON_API mitkThread: public mitkObject
{
public:
    MITK_TYPE(mitkThread,mitkObject)
    ///////////////////////////////////////////////////////////////////////////
    /// Create a thread an start to execute
    ///////////////////////////////////////////////////////////////////////////
    void Spawn()
    {
        m_Imp->Spawn();
    }
    ///////////////////////////////////////////////////////////////////////////
    // Wait for the thread to terminate
    ///////////////////////////////////////////////////////////////////////////
    void Wait()
    {
        m_Imp->Wait();
    }
protected:
    mitkThread();
    virtual ~mitkThread();  
    virtual void Run()=0;
private:
    mitkThread(const mitkThread&);
    void operator = (const mitkThread&);
    mitkThreadImp *m_Imp;
};

/// mitkThreadDelegate - The base class of mitkThreadStatic and mitkThreadMember, 
///////////////////////////////////////////////////////////////////////////
/// mitkThreadDelegate - The base class of mitkThreadStatic and mitkThreadMember, 
/// which redirect thread entrance to some user function. This class allows 
/// user to set a parameter to be passed to the user entrance.
class MITK_COMMON_API mitkThreadDelegate: public mitkThread
{
public:
    MITK_TYPE(mitkThreadDelegate,mitkThread)
    void SetParameter(void *param)
    {
        m_Param=param;
    }
protected:
    mitkThreadDelegate(){m_Param=NULL;}
    virtual ~mitkThreadDelegate(){}
    void *GetParameter()
    {
        return m_Param;
    }
private:
    mitkThreadDelegate(const mitkThreadDelegate&);
    void operator = (const mitkThreadDelegate&);
    void *m_Param;
};

/// mitkThreadStatic - A utility allowing user to conveniently
/// create a delegate thread object that redirects Run to a specified
/// static function or global function.
///////////////////////////////////////////////////////////////////////////
/// mitkThreadStatic is a utility allowing user to conveniently
/// create a delegate thread object that redirects Run to a specified
/// static function or global function.
class mitkThreadStatic: public mitkThreadDelegate
{
public:
    mitkThreadStatic(void (*function)(void*))
    {
        m_Function=function;
    }
protected:
    virtual ~mitkThreadStatic(){}
    virtual void Run()
    {
        m_Function(GetParameter());
    }
private:
    mitkThreadStatic(const mitkThreadStatic&);
    void operator=(const mitkThreadStatic&);
    void (*m_Function)(void *);
};

/// mitkThreadMember - A utility allowing user to conveniently
/// create a delegate thread object that redirects Run to a specified
/// member function.
///////////////////////////////////////////////////////////////////////////
/// mitkThreadMember is a utility allowing user to conveniently
/// create a delegate thread object that redirects Run to a specified
/// member function.
template<class T>
class mitkThreadMember : public mitkThreadDelegate
{
public:
    mitkThreadMember(T* object, void (T::*MemberFunction)(void *))
    {
        m_Object=object;
        m_MemberFunction=MemberFunction;
    }
protected:
    virtual ~mitkThreadMember(){}
    virtual void Run()
    {
        (m_Object->*m_MemberFunction)(GetParameter());
    }
private:
    mitkThreadMember(const mitkThreadMember&);
    void operator = (const mitkThreadMember&);
    T *m_Object;
    void (T::*m_MemberFunction)(void *);
};

#define MITK_THREAD_MEMBER(Class,ObjectPointer,MemberFunction)\
mitkThreadMember<Class>(ObjectPointer,&Class::MemberFunction)

#endif

