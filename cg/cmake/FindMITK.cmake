# - try to find MITK library and include files
#  MITK_INCLUDE_DIR, where to find mitkObject.h, etc.
#  MITK_LIBRARY_DIR, where to find MITK library files
#  MITK_LIBRARIES, the libraries to link against
#  MITK_FOUND, if false, do not try to use MITK.

if(WIN32)
  set(MITK_DIR         ${homework_SOURCE_DIR}/mitk/win${BUILD_ARCH})
  set(MITK_INCLUDE_DIR ${MITK_DIR}/Include)
  set(MITK_LIBRARY_DIR ${MITK_DIR}/Lib)
  if(WIN32)
    FIND_LIBRARY(MITK_mitk_LIBRARY NAMES mitkCommon PATHS ${MITK_LIBRARY_DIR})
    set(MITK_DLL_LIBRARIES ${MITK_LIBRARY_DIR}/mitkCommon.dll)
  else(WIN32)
    message("Not support the mitk on this platform.")
  endif(WIN32)
endif()

set(MITK_FOUND "NO")
if(MITK_INCLUDE_DIR AND MITK_LIBRARY_DIR)
  if(MITK_mitk_LIBRARY)
    set(MITK_LIBRARIES ${MITK_mitk_LIBRARY})
    set(MITK_FOUND "YES")

    #The following deprecated settings are for backwards compatibility with CMake1.4
    set(MITK_LIBRARY ${MITK_LIBRARIES})
    set(MITK_INCLUDE_PATH ${MITK_INCLUDE_DIR})
  endif(MITK_mitk_LIBRARY)
endif(MITK_INCLUDE_DIR AND MITK_LIBRARY_DIR)

MARK_AS_ADVANCED(
  MITK_INCLUDE_DIR
  MITK_LIBRARY_DIR
  MITK_LIBRARIES)
