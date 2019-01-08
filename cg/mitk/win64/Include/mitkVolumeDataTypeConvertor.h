/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeDataTypeConvertor_h
#define __mitkVolumeDataTypeConvertor_h

#include "mitkVolumeToVolumeFilter.h"

/// mitkVolumeDataTypeConvertor - a filter to convert the type of volume data
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeDataTypeConvertor is a filter to convert the volume data from
/// one type to another.
class MITK_COMMON_API mitkVolumeDataTypeConvertor : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkVolumeDataTypeConvertor, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    mitkVolumeDataTypeConvertor();

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of the output volume. MITK supports various data types.
    /// \param data_type Its valid value and meaning is shown as follows:\n
    /// MITK_CHAR            The data type is char \n
    /// MITK_UNSIGNED_CHAR   The data type is unsigned char \n
    /// MITK_SHORT           The data type is short \n
    /// MITK_UNSIGNED_SHORT  The data type is unsigned short \n
    /// MITK_INT             The data type is int \n
    /// MITK_UNSIGNED_INT    The data type is unsigned int \n
    /// MITK_LONG            The data type is long \n
    /// MITK_UNSIGNED_LONG   The data type is unsigned long \n
    /// MITK_FLOAT           The data type is float \n
    /// MITK_DOUBLE          The data type is double \n
    ///////////////////////////////////////////////////////////////////////////
    void SetOutputDataType(int dataType) { m_OutDataType = dataType; }

protected:
    virtual ~mitkVolumeDataTypeConvertor();

    virtual bool Execute();

    int m_OutDataType;

private:
    mitkVolumeDataTypeConvertor(const mitkVolumeDataTypeConvertor&);
    void operator = (const mitkVolumeDataTypeConvertor&);

};


//#define DEFINED_mitkVolumeDataTypeConvertor



#endif

