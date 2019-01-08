/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkObject_h
#define __mitkObject_h

#include "mitkGlobal.h"

class mitkList;
class mitkObserver;

/// mitkObject - abstract base class for most objects in MITK
///////////////////////////////////////////////////////////////////////////
/// mitkObject is the base class for most objects in MITK. It provides several
/// base services for all of MITK objects. \n
/// The first base service is the RTTI(Run Time Type Information). 
/// Please see the  GetClassname(), IsTypeOf(), IsA(), SafeDownCast() \n
/// The second base service is the debugging information.
/// Please see the  DebugOn(), DebugOff(), GetDebug(), SetDebug(), BreakOnError(),
/// PrintSelf() \n
/// The third base service is the memory management, including Reference Counting 
/// and Garbage Collection.
/// Please see the AddReference(), RemoveReference(), GetReferenceCount(),
/// Delete() \n
/// The fourth base service is the support of the observer design pattern, which 
/// makes the updating user interface to reflect the internal status of a MITK
/// object possible.
/// Please see the AddObserver(), RemoveObserver(), RemoveAllObservers()
/// \note The deconstructor of mitkObject and all of its subclasses is protected. This
/// means that a object in MITK must be allocated in the heap using new operator. If
/// you define a local MITK object in the stack, the compiler will generate an error
/// information. 
class MITK_COMMON_API mitkObject
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// Get the class name as a string. The purpose is to support RTTI.
    /// \return Return the class name of this object. For mitkObject, it always 
    /// return "mitkObject"
    ///////////////////////////////////////////////////////////////////////////
    virtual const char *GetClassname() const {return "mitkObject";}

    ///////////////////////////////////////////////////////////////////////////
    /// Decide if this class is one type of the specified class
    /// \param name The name of specified class 
    /// \return Return 1 if this class is the same type of (or a subclass of)
    /// the specified class. Returns 0 otherwise.
    ///////////////////////////////////////////////////////////////////////////
    static int IsTypeOf(const char *name);

    ///////////////////////////////////////////////////////////////////////////
    /// Decide if this class is one type of the specified class
    /// \param name The name of specified class
    /// \return Return 1 if this class is the same type of (or a subclass of)
    /// the specified class. Returns 0 otherwise.
    ///////////////////////////////////////////////////////////////////////////
    virtual int IsA(const char *name);

    ///////////////////////////////////////////////////////////////////////////
    /// Safely cast the specified object to mitkObject*
    /// \param o The specified object
    /// \return If success, return the casted o, otherwise return NULL.
    ///////////////////////////////////////////////////////////////////////////
    static mitkObject *SafeDownCast(mitkObject *o);

    ///////////////////////////////////////////////////////////////////////////
    /// Turn debugging output on.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DebugOn();

    ///////////////////////////////////////////////////////////////////////////
    /// Turn debugging output off.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DebugOff();

    ///////////////////////////////////////////////////////////////////////////
    /// Get the value of the debug flag.
    /// \return Return zero, the debug flag is off, otherwise the debug flag is on.
    ///////////////////////////////////////////////////////////////////////////
    unsigned char GetDebug();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the value of the debug flag.
    /// \param debugFlag If debugFlag is zero, set the debug flag to off, otherwise
    /// set the debug flag to on.
    ///////////////////////////////////////////////////////////////////////////
    void SetDebug(unsigned char debugFlag);

    ///////////////////////////////////////////////////////////////////////////
    /// This method is called when mitkErrorMessage executes.
    ///////////////////////////////////////////////////////////////////////////
    static void BreakOnError();

    ///////////////////////////////////////////////////////////////////////////
    /// Print this object to an ostream.
    /// \param os The specified ostream to output information.
    ///////////////////////////////////////////////////////////////////////////
    void Print(ostream& os);

    ///////////////////////////////////////////////////////////////////////////
    /// Print the necessary information about this object for the debugging purpose.
    /// \param os The specified ostream to output information.
    ///////////////////////////////////////////////////////////////////////////
    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////
    /// Attach an observer to this object.
    /// \param observer pointer to an mitkObserver to attach
    ///////////////////////////////////////////////////////////////////////
    void AddObserver(mitkObserver *observer);

    ///////////////////////////////////////////////////////////////////////
    /// Detach an observer from this object.
    /// \param observer pointer to an mitkObserver to detach
    ///////////////////////////////////////////////////////////////////////
    void RemoveObserver(mitkObserver *observer);

    ///////////////////////////////////////////////////////////////////////
    /// Detach all observers from this object.
    ///////////////////////////////////////////////////////////////////////
    void RemoveAllObservers();

    ///////////////////////////////////////////////////////////////////////
    /// Add 1 to the referenct count. Only when the reference count of a MITK
    /// object is equal to 0, it can be deleted.    
    ///////////////////////////////////////////////////////////////////////
    void AddReference();

    ///////////////////////////////////////////////////////////////////////
    /// Remove 1 to the referenct count. If reference count is equal to zero
    /// after remove 1, then this object is deleted automatically.
    ///////////////////////////////////////////////////////////////////////
    void RemoveReference();

    ///////////////////////////////////////////////////////////////////////
    /// Get current referenct count of this object. Only when the reference
    /// count of a MITK object is equal to 0, it can be deleted.    
    /// \return Return the reference count of this object.
    ///////////////////////////////////////////////////////////////////////
    int  GetReferenceCount()    {return m_ReferenceCount;}
    
    ///////////////////////////////////////////////////////////////////////
    /// If current reference count is equal to 0, delete this object, otherwise,
    /// nothing happens. 
    /// \note Usually a MITK object can only be deleted through two ways. One 
    /// is to call RemoveReference(), and the other is to call Delete(). But
    /// RemoveReference() is usually called internally to implement the reference
    /// counting design pattern, so Delete() is the correct function to call
    /// if you want to delete a MITK object.
    ///////////////////////////////////////////////////////////////////////
    void Delete();

protected:
    mitkObject();    
    virtual ~mitkObject();

    void _updateObservers();

    int m_Debug;     // Enable debug messages
    int m_ReferenceCount;

    mitkList *m_Observers;

private:

    friend ostream& operator << (ostream& os, mitkObject& o);
    mitkObject(const mitkObject&);
    void operator = (const mitkObject&);
};

 
//#define DEFINED_mitkObject



#endif


