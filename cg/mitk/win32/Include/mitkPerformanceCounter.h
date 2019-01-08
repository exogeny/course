/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifdef _WIN32
#include <windows.h>
class PerformanceCounter
{
    double dfFreq ;
public:
    PerformanceCounter()
    {
        LARGE_INTEGER litmp;
        QueryPerformanceFrequency(&litmp);
        dfFreq = (double)litmp.QuadPart/1000;
    }
    double GetTime()
    {
        LARGE_INTEGER litmp;
        QueryPerformanceCounter(&litmp);
        return (double)litmp.QuadPart/dfFreq;
    }
};

static PerformanceCounter theCounter;

static inline double GetTime()
{
    return theCounter.GetTime();    
}
#else

#include <sys/time.h>
static inline double GetTime()
{
    struct timeval t_time;
    gettimeofday( &t_time, 0);
    return 1000.0 * t_time.tv_sec + 0.001 * t_time.tv_usec; 
}

#endif

