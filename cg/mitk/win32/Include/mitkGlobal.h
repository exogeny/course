/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





///////////////////////////////////////////////////////////////////////////
/// \mainpage
/// MITK stands for <b>M</b>edical <b>I</b>maging <b>T</b>ool<b>K</b>it.
/// It is a C++ library for integrated medical image processing and
/// analyzing developed by the
/// <A HREF="http://www.3dmed.net/" TARGET="_blank">Medical Image Processing Group</A>,
/// <A HREF="http://compsys.ia.ac.cn/" TARGET="_blank">Key Laboratory
/// of Complex Systems and Intelligence Science</A>,
/// <A HREF="http://www.ia.ac.cn/" TARGET="_blank">Institute of Automation</A>,
/// the Chinese Academy of Sciences. The development of MITK is inspired
/// by the big success of open source softwares
/// <A HREF="http://www.vtk.org/" TARGET="_blank">VTK</A> and
/// <A HREF="http://www.itk.org/" TARGET="_blank">ITK</A>, and its main
/// purpose is to provide medical image community a consistent framework
/// to combine the function of medical image segmentation, registration
/// and visualization. Much as the style of VTK, MITK uses the traditional
/// Object-Oriented design methods, and doesn't use the Generic Programming
/// style used by ITK. So the syntax and interface of MITK is simple and
/// intuitive. Now MITK is a free software and can be used freely for
/// research and education purpose. We hope that MITK will become another
/// available choice for the medical imaging community.
///////////////////////////////////////////////////////////////////////////

#ifndef __mitkGlobal_h
#define __mitkGlobal_h

#include "mitkCommonIncludes.h"
#include <math.h>
#include <assert.h>

#include <string.h>

#ifdef MITK_OS_LINUX
#include <strings.h>
#define stricmp strcasecmp
#endif

//I/O Stream & string
#include <iostream> 
#include <sstream>
#include <fstream>  
#include <iomanip>  
#include <string> 
#include <vector>

// Need these in global namespace so the same code will work with ansi
// and old-style streams.
using std::dec;
using std::hex;
using std::setw;
using std::setfill;
using std::cerr;
using std::cout;
using std::cin;
using std::ios;
using std::endl;
using std::ostream;
using std::istream;
using std::ostringstream;
using std::istringstream;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::string;
using std::vector;

typedef unsigned int index_type;
typedef unsigned int size_type;

typedef string mitkString;
typedef vector<string> mitkStringList;

// Some constants used throughout the code
#define MITK_LARGE_FLOAT 1.0e+38F
#define MITK_LARGE_INTEGER 2147483647 // 2^31 - 1

// These types are returned by GetDataType to indicate pixel type.
#define MITK_VOID            0
#define MITK_BIT             1
#define MITK_CHAR            2
#define MITK_UNSIGNED_CHAR   3
#define MITK_SHORT           4
#define MITK_UNSIGNED_SHORT  5
#define MITK_INT             6
#define MITK_UNSIGNED_INT    7
#define MITK_LONG            8
#define MITK_UNSIGNED_LONG   9
#define MITK_FLOAT          10
#define MITK_DOUBLE         11

// Some constant required for correct template performance
#define MITK_BIT_MIN 0
#define MITK_BIT_MAX 1
#define MITK_CHAR_MIN -128
#define MITK_CHAR_MAX 127
#define MITK_UNSIGNED_CHAR_MIN 0
#define MITK_UNSIGNED_CHAR_MAX 255
#define MITK_SHORT_MIN -32768
#define MITK_SHORT_MAX 32767
#define MITK_UNSIGNED_SHORT_MIN 0
#define MITK_UNSIGNED_SHORT_MAX 65535
#define MITK_INT_MIN (-MITK_LARGE_INTEGER-1)
#define MITK_INT_MAX MITK_LARGE_INTEGER
#define MITK_UNSIGNED_INT_MIN 0
#define MITK_UNSIGNED_INT_MAX 4294967295UL
#define MITK_LONG_MIN (-MITK_LARGE_INTEGER-1)
#define MITK_LONG_MAX MITK_LARGE_INTEGER
#define MITK_UNSIGNED_LONG_MIN 0
#define MITK_UNSIGNED_LONG_MAX 4294967295UL
#define MITK_FLOAT_MIN -MITK_LARGE_FLOAT
#define MITK_FLOAT_MAX MITK_LARGE_FLOAT
#define MITK_DOUBLE_MIN -1.0e+99L
#define MITK_DOUBLE_MAX  1.0e+99L

// These types are returned to distinguish data object types
#define MITK_DATA_OBJECT                 0
#define MITK_VOLUME                   1000
#define MITK_IC_VOLUME                1001
#define MITK_OOC_VOLUME               1002
#define MITK_PARALLEL_PROJECT_DATA    1003
#define MITK_OUT_OF_CORE_PARALLEL_PROJECT_DATA  1004
#define MITK_COHERENT_VOLUME          1005

#define MITK_MESH                     2000
#define MITK_TRIANGLE_MESH            2001
#define MITK_IC_TRIANGLE_MESH         2002
#define MITK_OOC_TRIANGLE_MESH        2003
#define MITK_HE_MESH                  2004
#define MITK_HE_TRIANGLE_MESH         2005
#define MITK_HE_IC_TRIANGLE_MESH      2006
#define MITK_HE_OOC_TRIANGLE_MESH     2007

#define MITK_RAW_DATA                 3000
#define MITK_CT_PROJECTION_DATA       3001
#define MITK_2D_BEAM_PD               3002
#define MITK_2D_BEAM_IC_PD            3003
#define MITK_2D_BEAM_OOC_PD           3004
#define MITK_2D_BEAM_REAL_TIME_PD     3005
#define MITK_CONE_BEAM_PD             3006
#define MITK_CONE_BEAM_IC_PD          3007
#define MITK_CONE_BEAM_OOC_PD         3008
#define MITK_CONE_BEAM_REAL_TIME_PD   3009
#define MITK_TRACKED_BSCAN_DATA       3010
#define MITK_TRACKED_BSCAN_IC_DATA    3011
#define MITK_TRACKED_BSCAN_OOC_DATA   3012


#define MITK_IMAGE                    5001
#define MITK_PIECEWISE_FUNCTION       5002
#define MITK_IMAGE_DATA               5003
#define MITK_IMAGE_RAWCT              5004
#define MITK_POLY_DATA                5005
#define MITK_RAWCT_DATA               5006

#define MITK_LEFTBUTTON    0
#define MITK_MIDDLEBUTTON  1
#define MITK_RIGHTBUTTON   2

#define MITK_CTRLKEY         0
#define MITK_SHIFTKEY        1
#define MITK_CTRLANDSHIFTKEY 2

#define MITK_NEAREST_INTERPOLATION 0
#define MITK_LINEAR_INTERPOLATION  1 
#define MITK_BILINEAR_INTERPOLATION 2

#define MITK_FLOAT_PI  3.14159265358979323846f
#define MITK_DOUBLE_PI 3.14159265358979323846
//
// These swap macros are used for processing endian problem
//
#define Swap16(shortX) shortX = ((shortX & 0x00FF) << 8) | ((shortX & 0xFF00) >> 8)

#define Swap32(intX) \
      intX = ((intX & 0x000000FF) << 24) \
           | ((intX & 0x0000FF00) << 8) \
           | ((intX & 0x00FF0000) >> 8) \
           | ((intX & 0xFF000000) >> 24)

#define Swap64(lowX,highX) \
{     Swap32(lowX); \
      Swap32(highX); \
      unsigned long swaptmp = lowX; \
      lowX = highX; \
      highX = swaptmp; \
}

//
// Macro for floor of x
//
#define mitkFloorFuncMacro(x)   (((x) < 0.0)?((int)((x)-1.0)):((int)(x)))

//
// Macro for rounding x
//
#define mitkRoundFuncMacro(x)   (int)((x)+0.5)

//
// Macro for tri-linear interpolation - do four linear interpolations on
// edges, two linear interpolations between pairs of edges, then a final
// interpolation between faces
//
#define mitkTrilinFuncMacro(v,x,y,z,a,b,c,d,e,f,g,h)         \
{       t00 =   a + (x)*(b-a);      \
        t01 =   c + (x)*(d-c);      \
        t10 =   e + (x)*(f-e);      \
        t11 =   g + (x)*(h-g);      \
        t0  = t00 + (y)*(t01-t00);  \
        t1  = t10 + (y)*(t11-t10);  \
        v   =  t0 + (z)*(t1-t0); }

//
// This macro is used for  print information in non-member methods
// mitkGenericMessage("this is debug info" << this->SomeVariable);
//
#define mitkGenericMessage(x) \
{     ostringstream mitkmsg; \
      mitkmsg << x << "\n"; \
      mitkDisplayMessage(mitkmsg.str().c_str());}

//
// This macro is used to print out debug message in a member function
// of mitkObject derived class
// mitkDebugMessage("this is debug info" << this->SomeVariable);
//
#define mitkDebugMessage(x) \
{ if (this->m_Debug ) \
    { ostringstream mitkmsg; \
      mitkmsg << "Debug: In " __FILE__ ", line " << __LINE__ << "\n" << this->GetClassname() << " (" << this << "): " << x  << "\n\n"; \
      mitkDisplayMessage(mitkmsg.str().c_str());}}

//
// This macro is used to print out warning message in a member function
// of mitkObject derived class
// mitkWarningMessage("Warning message" << variable);
//
#define mitkWarningMessage(x) \
{     ostringstream mitkmsg; \
      mitkmsg << "Warning: In " __FILE__ ", line " << __LINE__ << "\n" << this->GetClassname() << " (" << this << "): " << x << "\n\n"; \
      mitkDisplayMessage(mitkmsg.str().c_str());}

//
// This macro is used to print out error message in a member function
// of mitkObject derived class
// mitkErrorMessage("Error message" << variable);
//
#define mitkErrorMessage(x) \
{     ostringstream mitkmsg; \
      mitkmsg << "ERROR: In " __FILE__ ", line " << __LINE__ << "\n" << this->GetClassname() << " (" << this << "): " << x << "\n\n"; \
      mitkDisplayMessage(mitkmsg.str().c_str());\
      mitkObject::BreakOnError();}

#define MITK_TYPE(thisClass,superclass) \
  virtual const char *GetClassname() const {return #thisClass;} \
  static int IsTypeOf(const char *type) \
  { \
    if ( !strcmp(#thisClass,type) ) \
      { \
      return 1; \
      } \
    return superclass::IsTypeOf(type); \
  } \
  virtual int IsA(const char *type) \
  { \
    return this->thisClass::IsTypeOf(type); \
  } \
  static thisClass* SafeDownCast(mitkObject *o) \
  { \
    if ( o && o->IsA(#thisClass) ) \
      { \
      return static_cast<thisClass *>(o); \
      } \
    return NULL;\
  } 

MITK_COMMON_API char const* mitkGetDataTypeName(int dataType); 
MITK_COMMON_API int mitkGetDataTypeFromName(char const *name);

#include "mitk_nl/mitk_nl_vector.h"

typedef double                  ScalarParameterType;
typedef float                   ScalarPixelType;
typedef int                     ScalarIndexType;
typedef mitk_nl_vector<double>  VectorParameterType;
typedef mitk_nl_vector<float>   VectorPixelType;
typedef mitk_nl_vector<int>     VectorIndexType;

#define MITK_VER_OOC

#endif


