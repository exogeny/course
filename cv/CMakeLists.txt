cmake_minimum_required(VERSION 3.6)

project(CV)

set(BUILD_ARCH "32")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(BUILD_ARCH "64")
endif()

# support c++ compiler
set(CMAKE_CXX_STANDARD 11)

# gnu gcc compile flag
if(CMAKE_COMPILER_IS_GNUCXX)
  if(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fPIC -Wall")
  else(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O3 -fPIC -Wall")
  endif(DEBUG)
  SET(CMAKE_C_LINK_EXECUTABLE   "${CMAKE_C_LINK_EXECUTABLE} -lstdc++")
  SET(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lstdc++")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/external)

option(USE_SYSTEM_GLUT        "use the system glut libraries"      OFF)
option(USE_SYSTEM_GLEW        "use the system glew libraries"      OFF)
option(USE_SYSTEM_FREE_IMAGE  "use the system FreeImage libraries" OFF)

# Location where external projects will be downloaded
set(DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/downloads"
    CACHE PATH "Location where external projects will be downloaded.")
mark_as_advanced(DOWNLOAD_LOCATION)

include(freeimage)

file (GLOB_RECURSE homework_srcs
  "${PROJECT_SOURCE_DIR}/homework/*.h"
  "${PROJECT_SOURCE_DIR}/homework/*.cc")

include_directories(${freeimage_INCLUDE_DIR})

add_executable(homework ${homework_srcs})
target_link_libraries(homework ${freeimage_STATIC_LIBRARIES})
add_custom_command(
    TARGET homework POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${freeimage_LIBRARIES}
      $<TARGET_FILE_DIR:homework>)
