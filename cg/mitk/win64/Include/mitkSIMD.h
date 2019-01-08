/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkSIMD_h
#define __mitkSIMD_h

#include "mitkSIMDConfig.h"
#include "mitkGlobal.h"

#ifdef USE_SIMD

#include <xmmintrin.h>  //SSE include file

class CheckSIMDSupport
{
public:
    bool hasMMX;
    bool hasSSE;
    bool hasSSE2;
    bool has3DNow;
    CheckSIMDSupport();
    ~CheckSIMDSupport();
    
};

bool g_IsMMXSupported();
bool g_IsSSESupported();
bool g_IsSSE2Supported();
bool g_Is3DNowSupported();

#endif // USE_SIMD

#endif

