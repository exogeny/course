/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkSPMD_h
#define __mitkSPMD_h

#include "mitkObject.h"

class mitkMutex;
class mitkConditionVariable;
class mitkSPMD;

/// mitkBarrier - A synchronizer for mitkSPMD
///////////////////////////////////////////////////////////////////////////
/// mitkBarrier is a synchronizer for mitkSPMD, it can be created only by
/// SPMD. Is you use SPMD by sub-classing mitkSPMD, please use the protected 
/// member function Synchronize() of mitkSPMD. This class is explicitly used
/// only when you are using one of the delegates of SPMD (mitkSPMDStatic or
/// mitkSPMDMember)
class MITK_COMMON_API mitkBarrier:public mitkObject
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// Called to synchronize threads. The calling thread waits until other
    /// threads created by the same SPMD reach the calling point.
    ///////////////////////////////////////////////////////////////////////////
    void Synchronize();
    friend class mitkSPMD;
private:
    mitkBarrier(int NumberOfThreads);
    virtual ~mitkBarrier();
    mitkBarrier(const mitkBarrier&);
    void operator = (const mitkBarrier&);

    int m_NumberOfThreads;
    int m_Count;
    mitkConditionVariable *m_CV;
};

/// mitkSPMD - A threading tool that implements a SPMD (Single Program 
/// Multiple Data) style multi-thread execution. 
///////////////////////////////////////////////////////////////////////////
/// mitkSPMD is a threading tool that implements a SPMD (Single Program 
/// Multiple Data) style multi-thread execution. mitkSPMD will create
/// a number of threads, and each thread will end up calling the virtual 
/// protected function ThreadExecute with their unique identifier, which 
/// can be used to decide the part of data to be processed, since the 
/// memory is shared among threads. 
class MITK_COMMON_API mitkSPMD:public mitkObject
{
public:
    MITK_TYPE(mitkSPMD,mitkObject)
    ///////////////////////////////////////////////////////////////////////////
    /// Set the number of threads to be created
    /// \param NumberOfThreads Specify the number of threads to be created
    /// must be greater or equal than 1, and the default value is the
    /// GlobalDefaultNumberOfThreads
    ///////////////////////////////////////////////////////////////////////////
    void SetNumberOfThreads(int NumberOfThreads);
    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of threads to be created
    /// \return return the number of threads to be created
    /// the default value is the GlobalDefaultNumberOfThreads
    ///////////////////////////////////////////////////////////////////////////
    int GetNumberOfThreads() const
    {
        return m_NumberOfThreads;
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Perform the SPMD execution
    ///////////////////////////////////////////////////////////////////////////
    void RunSPMD();
    ///////////////////////////////////////////////////////////////////////////
    /// Acquire the default number of threads according to the number of 
    /// hardware processors(cores)
    /// \return Return the global default number of threads
    ///////////////////////////////////////////////////////////////////////////
    static int  GetGlobalDefaultNumberOfThreads();
    
protected:
    mitkSPMD();
    virtual ~mitkSPMD();
    // create thread specific structures here is subclasses
    virtual void SPMDInit(){};
    // call by threads
    virtual void ThreadExecute(int ThreadID)=0;
    // destroy thread specific structures here is subclasses
    virtual void SPMDFinish(){};

    void Synchronize()
    {
        if (m_Barrier) m_Barrier->Synchronize();
    }

    mitkBarrier *GetBarrier(){return m_Barrier;}

private:
    mitkSPMD(const mitkSPMD&);
    void operator = (const mitkSPMD&);
    int m_NumberOfThreads;
    mitkBarrier *m_Barrier;

};

/// mitkSPMDDelegate - The base class of mitkSPMDStatic and mitkSPMDMember, 
///////////////////////////////////////////////////////////////////////////
/// mitkSPMDDelegate - The base class of mitkSPMDStatic and mitkSPMDMember, 
/// which redirect SPMD functions to some user functions. This class allows 
/// user to set a parameter to be passed to the user entrance.
class MITK_COMMON_API mitkSPMDDelegate: public mitkSPMD
{
public:
    MITK_TYPE(mitkSPMDDelegate,mitkSPMD)
    void SetParameter(void *param)
    {
        m_Param=param;
    }
protected:
    mitkSPMDDelegate() {m_Param=NULL;}
    virtual ~mitkSPMDDelegate(){}
    void *GetParameter()
    {
        return m_Param;
    }
private:
    mitkSPMDDelegate(const mitkSPMDDelegate&);
    void operator = (const mitkSPMDDelegate&);
    void *m_Param;
};

/// mitkSPMDStatic - A utility allowing user to conveniently create a
/// delegate SPMD object that redirects SPMD functions to specified
/// static functions or global functions.
///////////////////////////////////////////////////////////////////////////
/// mitkSPMDStatic is a utility allowing user to conveniently create a
/// delegate SPMD object that redirects SPMD functions to specified
/// static functions or global functions.
class mitkSPMDStatic: public mitkSPMDDelegate
{
public:
    mitkSPMDStatic(void (*ThreadedFunction)(int,int,void *,mitkBarrier*),
                        void (*InitFunction)(int,void *)=NULL,
                        void (*FinishFunction)(int,void *)=NULL)
    {
        m_ThreadedFunction=ThreadedFunction;    
        m_InitFunction=InitFunction;
        m_FinishFunction=FinishFunction;        
    }

protected:
    virtual ~mitkSPMDStatic(){}
    virtual void SPMDInit()
    {
        if (m_InitFunction) m_InitFunction(GetNumberOfThreads(),GetParameter());    
    }
    virtual void ThreadExecute(int ThreadID)
    {
        m_ThreadedFunction(ThreadID,GetNumberOfThreads(),GetParameter(),GetBarrier());
    }
    virtual void SPMDFinish()
    {
        if (m_FinishFunction) m_FinishFunction(GetNumberOfThreads(),GetParameter());
    }
private:
    mitkSPMDStatic(const mitkSPMDStatic&);
    void operator = (const mitkSPMDStatic&);
    void (*m_InitFunction)(int,void *);
    void (*m_FinishFunction)(int,void *);
    void (*m_ThreadedFunction)(int,int,void *,mitkBarrier*);
};

/// mitkSPMDMember - A utility allowing user to conveniently create a
/// delegate SPMD object that redirects SPMD functions to specified
/// member functions.
///////////////////////////////////////////////////////////////////////////
/// mitkSPMDMember is a utility allowing user to conveniently create a
/// delegate SPMD object that redirects SPMD functions to specified
/// member functions.
template<class T>
class mitkSPMDMember: public mitkSPMDDelegate
{
public:
    mitkSPMDMember(T* object,void (T::*ThreadedMember)(int,int,void*,mitkBarrier*),
                        void (T::*InitMember)(int,void*)=NULL,
                        void (T::*FinishMember)(int,void*)=NULL)
    {
        m_object=object;
        m_ThreadedMember=ThreadedMember;    
        m_InitMember=InitMember;
        m_FinishMember=FinishMember;
    }
protected:
    virtual ~mitkSPMDMember(){}
    virtual void SPMDInit()
    {
        if (m_InitMember) (m_object->*m_InitMember)(GetNumberOfThreads(),GetParameter());
    }
    virtual void ThreadExecute(int ThreadID)
    {
        (m_object->*m_ThreadedMember)(ThreadID,GetNumberOfThreads(),GetParameter(),GetBarrier());
    }
    virtual void SPMDFinish()
    {
        if (m_FinishMember) (m_object->*m_FinishMember)(GetNumberOfThreads(),GetParameter());
    }
    
private:
    mitkSPMDMember(const mitkSPMDMember&);
    void operator = (const mitkSPMDMember&);    
    T *m_object;
    void (T::*m_InitMember)(int,void*);
    void (T::*m_FinishMember)(int,void*);
    void (T::*m_ThreadedMember)(int,int,void*,mitkBarrier*);
};

#define MITK_SPMD_MEMBER1(Class,ObjectPointer,ThreadedMember)\
mitkSPMDMember<Class>(ObjectPointer,&Class::ThreadedMember)

#define MITK_SPMD_MEMBER2(Class,ObjectPointer,ThreadedMember,InitMember)\
mitkSPMDMember<Class>(ObjectPointer,&Class::ThreadedMember,&Class::InitMember)

#define MITK_SPMD_MEMBER3(Class,ObjectPointer,ThreadedMember,InitMember,FinishMember)\
mitkSPMDMember<Class>(ObjectPointer,&Class::ThreadedMember,&Class::InitMember,&Class::FinishMember)


#endif

