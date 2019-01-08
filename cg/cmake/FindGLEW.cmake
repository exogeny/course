# Copyright (c) 2009 Boudewijn Rempt <boud@valdyas.org>                                                                                          
#                                                                                                                                                
# Redistribution and use is allowed according to the terms of the BSD license.                                                                   
# For details see the accompanying COPYING-CMAKE-SCRIPTS file. 
# 
# - try to find glew library and include files
#  GLEW_INCLUDE_DIR, where to find GL/glew.h, etc.
#  GLEW_LIBRARIES, the libraries to link against
#  GLEW_FOUND, if false, do not try to use GLEW.
# Also defined, but not for general use are:
#  GLEW_GLEW_LIBRARY = the full path to the glew library.

if(WIN32)
  if(CYGWIN)
    FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h)
    FIND_LIBRARY(GLEW_GLEW_LIBRARY glew32
      ${OPENGL_LIBRARY_DIR}
      /usr/lib/w32api
      /usr/X11R6/lib)
  else(CYGWIN)
    FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h
      ${GLEW_ROOT_PATH}/include)
    FIND_LIBRARY(GLEW_GLEW_LIBRARY
      NAMES glew glew32
      PATHS
      ${GLEW_ROOT_PATH}/lib
      ${OPENGL_LIBRARY_DIR})
  endif(CYGWIN)
else (WIN32)

  if(APPLE)
# These values for Apple could probably do with improvement.
    FIND_PATH(GLEW_INCLUDE_DIR glew.h
      /System/Library/Frameworks/GLEW.framework/Versions/A/Headers
      ${OPENGL_LIBRARY_DIR}
      /usr/local/include/GL
   )
    set(GLEW_GLEW_LIBRARY "-framework GLEW" CACHE STRING "GLEW library for OSX")
  else (APPLE)
    FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h
      /usr/include/GL
      /usr/openwin/share/include
      /usr/openwin/include
      /usr/X11R6/include
      /usr/include/X11
      /opt/graphics/OpenGL/include
      /opt/graphics/OpenGL/contrib/libglew)
    FIND_LIBRARY(GLEW_GLEW_LIBRARY GLEW
      /usr/openwin/lib
      /usr/X11R6/lib)
  endif (APPLE)
endif (WIN32)

set(GLEW_FOUND "NO")
if(GLEW_INCLUDE_DIR)
  if(GLEW_GLEW_LIBRARY)
    # Is -lXi and -lXmu required on all platforms that have it?
    # ifnot, we need some way to figure out what platform we are on.
    set(GLEW_LIBRARIES ${GLEW_GLEW_LIBRARY})
    set(GLEW_FOUND "YES")

#The following deprecated settings are for backwards compatibility with CMake1.4
    set (GLEW_LIBRARY ${GLEW_LIBRARIES})
    set (GLEW_INCLUDE_PATH ${GLEW_INCLUDE_DIR})

  endif(GLEW_GLEW_LIBRARY)
endif(GLEW_INCLUDE_DIR)

if(GLEW_FOUND)
  if(NOT GLEW_FIND_QUIETLY)
    message(STATUS "Found Glew: ${GLEW_LIBRARIES}")
  endif(NOT GLEW_FIND_QUIETLY)
else(GLEW_FOUND)
  if(GLEW_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find Glew")
  endif(GLEW_FIND_REQUIRED)
endif(GLEW_FOUND)

MARK_AS_ADVANCED(
  GLEW_INCLUDE_DIR
  GLEW_GLEW_LIBRARY
  GLEW_Xmu_LIBRARY
  GLEW_Xi_LIBRARY)
