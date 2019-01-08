# - try to find FreeImage library and include files
#  FREEIMAGE_INCLUDE_DIR, where to find FreeImage.h, etc.
#  FREEIMAGE_LIBRARIES, the libraries to link against
#  FREEIMAGE_FOUND, if false, do not try to use FreeImage.


if (WIN32)
  FIND_PATH(FREEIMAGE_INCLUDE_DIR NAMES FreeImage.h PATHS ${FREEIMAGE_DIR} ${GLUT_INCLUDE_DIR})
  FIND_LIBRARY(FREEIMAGE_FreeImage_LIBRARY NAMES FreeImage PATHS ${FREEIMAGE_DIR})
  if (not FREEIMAGE_INCLUDE_DIR)
    set(FREEIMAGE_DIR "FreeImage" CACHE PATH "Path to FreeImage header and library files")
  endif (not FREEIMAGE_INCLUDE_DIR)
else (WIN32)
  if (APPLE)
    # These values for Apple could probably do with improvement.
    FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h
      /System/Library/Frameworks/FreeImage.framework/Versions/A/Headers
      /usr/include
      /usr/local/include)
    set(FREEIMAGE_FreeImage_LIBRARY "-framework FreeImage" CACHE STRING "FreeImage library for OSX") 
  else (APPLE)
    FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h
      /usr/include
      /usr/openwin/share/include
      /usr/openwin/include
      /opt/graphics/OpenGL/include
      /opt/graphics/OpenGL/contrib/libglut)
    FIND_LIBRARY(FREEIMAGE_FreeImage_LIBRARY NAMES FreeImage freeimage
      /usr/lib
      /usr/openwin/lib)
  endif (APPLE)
endif (WIN32)

set(FREEIMAGE_FOUND "NO")
if(FREEIMAGE_INCLUDE_DIR)
  if(FREEIMAGE_FreeImage_LIBRARY)
    set(FREEIMAGE_LIBRARIES ${FREEIMAGE_FreeImage_LIBRARY})
    set(FREEIMAGE_FOUND "YES")
    
    #The following deprecated settings are for backwards compatibility with CMake1.4
    set (FREEIMAGE_LIBRARY ${FREEIMAGE_LIBRARIES})
    set (FREEIMAGE_INCLUDE_PATH ${FREEIMAGE_INCLUDE_DIR})
    
  endif(FREEIMAGE_FreeImage_LIBRARY)
endif(FREEIMAGE_INCLUDE_DIR)

MARK_AS_ADVANCED(
  FREEIMAGE_INCLUDE_DIR
  FREEIMAGE_LIBRARIES)