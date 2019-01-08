/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkDataObject_h
#define __mitkDataObject_h

#include "mitkObject.h"

/// mitkDataObject - an abstract class to represents a data object in MITK
///////////////////////////////////////////////////////////////////////////
/// mitkDataObject is an abstract class to represents a data object in MITK.
/// And in MITK, you have only two kinds of data object to deal with.
/// \see mitkVolume
/// \see mitkMesh
class MITK_COMMON_API mitkDataObject : public mitkObject
{
public:
    MITK_TYPE(mitkDataObject,mitkObject)

    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////////
    /// Delete the allocated memory (if any) and initialize to default status.
    /// \note Pure virtual function. Its concrete subclass must implement
    /// this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Return the data object type.
    /// \return Always return MITK_DATA_OBJECT
    /// \note Pure virtual function. Its concrete subclass must implement
    /// this function and return its data object type.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const {return MITK_DATA_OBJECT;}

    ///////////////////////////////////////////////////////////////////////////
    /// Return the actual memory size occupied by this data object. The unit is BYTE.
    /// \return Return the actual memory size occupied by this data object.
    /// The unit is BYTE.
    /// \note Pure virtual function. Its concrete subclass must implement
    /// this function and return its memory size.
    ///////////////////////////////////////////////////////////////////////////
    virtual unsigned long long GetActualMemorySize() const = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// \warning Internal function. Don't call it directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void ShallowCopy(mitkDataObject *src) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// \warning Internal function. Don't call it directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DeepCopy(mitkDataObject *src) = 0;    

protected:
    mitkDataObject();    
    virtual ~mitkDataObject();

private:
    mitkDataObject(const mitkDataObject&);
    void operator=(const mitkDataObject&);
};


#endif



