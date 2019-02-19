cmake_minimum_required(VERSION 2.6)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

project(homework)

set(BUILD_ARCH "32")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(BUILD_ARCH "64")
endif()

# gnu gcc compile flag
if(CMAKE_COMPILER_IS_GNUCXX)
  if(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fPIC -Wall")
  else(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -fPIC -Wall")
  endif(DEBUG)
  SET(CMAKE_C_LINK_EXECUTABLE   "${CMAKE_C_LINK_EXECUTABLE} -lstdc++ -lX11 -lXxf86vm -lXi")
  SET(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lstdc++ -lX11 -lXxf86vm -lXi")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_MODULE_PATH ${homework_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/external)
set(CMAKE_INSTALL_PREFIX "${homework_BINARY_DIR}/dist" CACHE PATH "homework install prefix" FORCE)

option(USE_SYSTEM_GLUT        "use the system glut libraries"      OFF)
option(USE_SYSTEM_GLEW        "use the system glew libraries"      OFF)
option(USE_SYSTEM_FREE_IMAGE  "use the system FreeImage libraries" OFF)

if(WIN32)
  find_package(WindowsSDK QUIET)
  if(WINDOWSSDK_FOUND)
    message(STATUS "WINDOWSSDK_PREFERRED_DIR = ${WINDOWSSDK_PREFERRED_DIR}")
    message(STATUS "WINDOWSSDK_PREFERRED_FIRST_DIRS = ${WINDOWSSDK_PREFERRED_FIRST_DIRS}")
    get_windowssdk_include_dirs(${WINDOWSSDK_PREFERRED_DIR} WINSDK_INCLUDE_DIRS)
    get_windowssdk_library_dirs(${WINDOWSSDK_PREFERRED_DIR} WINSDK_LIBRARY_DIRS)

    message(STATUS "WINSDK_INCLUDE_DIRS = ${WINSDK_INCLUDE_DIRS}")
    message(STATUS "WINSDK_LIBRARY_DIRS = ${WINSDK_LIBRARY_DIRS}")

    if("${WINSDK_INCLUDE_DIRS}" STREQUAL "NOTFOUND")
      message(STATUS "WINSDK_INCLUDE_DIRS is not found")
    else()
      find_path(freeglut_INCLUDE_DIR  NAMES GL/glut.h             PATHS ${WINSDK_INCLUDE_DIRS})
      find_path(FREEIMAGE_INCLUDE_DIR NAMES FreeImage.h           PATHS ${WINSDK_INCLUDE_DIRS})
      find_path(GLEW_INCLUDE_DIR      NAMES GL/glew.h             PATHS ${WINSDK_INCLUDE_DIRS})

      find_library(freeglut_STATIC_LIBRARIES   NAMES glut glut32 freeglut  PATHS ${WINSDK_LIBRARY_DIRS})
      find_library(glew_STATIC_LIBRARIES       NAMES glew32                PATHS ${WINSDK_LIBRARY_DIRS})
      find_library(freeimage_STATIC_LIBRARIES  NAMES FreeImage             PATHS ${WINSDK_LIBRARY_DIRS})
    endif()
  endif(WINDOWSSDK_FOUND)
endif(WIN32)

# Location where external projects will be downloaded
set(DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/downloads"
    CACHE PATH "Location where external projects will be downloaded.")
mark_as_advanced(DOWNLOAD_LOCATION)

set(EXTERNAL_DEPENDICES "")
find_package(OpenGL    REQUIRED)
if(USE_SYSTEM_GLUT)
  find_package(GLUT    REQUIRED)
else()
  include(freeglut)
  set(EXTERNAL_DEPENDICES ${EXTERNAL_DEPENDICES} freeglut)
  install(FILES ${freeglut_LIBRARIES} DESTINATION . CONFIGURATIONS Release)
endif()
if(USE_SYSTEM_GLEW)
  find_package(GLEW    REQUIRED)
else()
  include(glew)
  set(EXTERNAL_DEPENDICES ${EXTERNAL_DEPENDICES} glew)
  install(FILES ${glew_LIBRARIES} DESTINATION . CONFIGURATIONS Release)
endif()
if(USE_SYSTEM_FREE_IMAGE)
  find_package(FreeImage REQUIRED)
else()
  include(freeimage)
  set(EXTERNAL_DEPENDICES ${EXTERNAL_DEPENDICES} freeimage)
  install(FILES ${freeimage_LIBRARIES} DESTINATION . CONFIGURATIONS Release)
endif()
find_package(MITK      QUIET)
install(FILES ${MITK_DLL_LIBRARIES} DESTINATION . CONFIGURATIONS Release)

include_directories(
  "include"
  ${OPENGL_INCLUDE_DIR}
  ${freeglut_INCLUDE_DIR})

add_custom_target(copy_data ${CMAKE_COMMAND} -E copy_directory ${homework_SOURCE_DIR}/data ${homework_BINARY_DIR}/data)

install(DIRECTORY data/ DESTINATION data PATTERN ".svn" EXCLUDE)
set(COMMON_SRCS
    src/common/camera.c
    src/common/matrix.c
    src/common/trackball.c
    src/common/vector.c
    src/common/shadow.c)

function(add_homework HOMEWORK_INDEX ISCOPY_DATA)
  set(LIBRARIES ${freeglut_STATIC_LIBRARIES} ${OPENGL_LIBRARIES})
  if(ARGV2)
    set(ADDITIONAL_LIBRARYS ${ARGV})
    list(REMOVE_AT ADDITIONAL_LIBRARYS 0)
    list(REMOVE_AT ADDITIONAL_LIBRARYS 0)
    list(APPEND LIBRARIES ${ADDITIONAL_LIBRARYS})
  endif(ARGV2)
  set(TARGET_NAME "homework${HOMEWORK_INDEX}")
  add_executable(${TARGET_NAME} src/homework${HOMEWORK_INDEX}/main.c ${COMMON_SRCS})
  if("${EXTERNAL_DEPENDICES}" STREQUAL "")
  else()
    add_dependencies(${TARGET_NAME} ${EXTERNAL_DEPENDICES})
  endif()
  if(ISCOPY_DATA)
    add_dependencies(${TARGET_NAME} copy_data)
  endif()
  target_link_libraries(${TARGET_NAME} ${LIBRARIES})
  install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION . CONFIGURATIONS Release)  
endfunction(add_homework)

include_directories(${freeimage_INCLUDE_DIR})
add_homework(1 true ${freeimage_STATIC_LIBRARIES})
add_homework(3 false ${freeimage_STATIC_LIBRARIES})