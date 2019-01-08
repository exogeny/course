/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkOoCGlobalSettings_h
#define __mitkOoCGlobalSettings_h

#include "mitkCommonIncludes.h"

struct MITK_COMMON_API mitkOoCGlobalSettings
{
    static unsigned long OoCThreshold;
    static unsigned BufferedSliceNumber;
    static const char* DiskCachePath;
};

#endif

