/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkBinaryFilter_h
#define __mitkBinaryFilter_h

#include "mitkVolumeToVolumeFilter.h"

/// mitkBinaryFilter - a filter to get binary data from a source volume
///////////////////////////////////////////////////////////////////////////
/// mitkBinaryFilter is a filter to get binary data of a source volume. The
/// data type of the output volume is MITK_UNSIGNED_CHAR. All non-zero values
/// of the source volume are set to 255. Zeros are not changed.
class MITK_COMMON_API mitkBinaryFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkBinaryFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////
    mitkBinaryFilter();

    ///////////////////////////////////////////////////////////////////////
    /// Get the cubage of the output object (non zero parts).
    ///////////////////////////////////////////////////////////////////////
    float GetCubage();

protected:
    virtual ~mitkBinaryFilter();

    virtual bool Execute();

private:
    mitkBinaryFilter(const mitkBinaryFilter&);
    void operator = (const mitkBinaryFilter&);

};

#endif

