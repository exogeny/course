/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkRCPtr_h
#define __mitkRCPtr_h

/// mitkRCPtr - a smart pointer class
///////////////////////////////////////////////////////////////////////////
/// mitkRCPtr is a smart pointer class
template<class T>
class mitkRCPtr
{
public:
    mitkRCPtr(T* realPtr = 0)
    {
        m_Pointee = realPtr;
        if(m_Pointee)   m_Pointee->AddReference();
    }

    ~mitkRCPtr()
    {
        if(m_Pointee)    m_Pointee->RemoveReference();
    }
    
    mitkRCPtr& operator=(T* realPtr);

    T* operator->() const {return m_Pointee;}
    T& operator*() const  {return *m_Pointee;} 
    operator T*() {return m_Pointee;}
    operator T const *() const {return m_Pointee;}
private:
    T *m_Pointee; 

    mitkRCPtr(const mitkRCPtr&) {}
    void operator=(const mitkRCPtr&) {} 
};
//---------------------------------------------------------------------------
template<class T>
inline mitkRCPtr<T>& mitkRCPtr<T>::operator=(T* realPtr)
{
    if(realPtr == m_Pointee) return *this;
    if(m_Pointee) m_Pointee->RemoveReference();
    m_Pointee = realPtr;
    if (m_Pointee) m_Pointee->AddReference();
    return *this;
}
//---------------------------------------------------------------------------

 
//#define DEFINED_mitkRCPtr



#endif

