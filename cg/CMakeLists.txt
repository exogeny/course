cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(cg)

# Compiler Flags
if(CMAKE_COMPILER_IS_GNUCXX)
  if(DEBUG)
    set(CMAKE_CXX_FLAGS "-g -O0 -fPIC -lstdc++ -Wall")
    set(CMAKE_C_FLAGS "-g -O0 -fPIC -Wall")
  else()
    set(CMAKE_CXX_FLAGS "-g -O3 -fPIC -lstdc++ -Wall")
    set(CMAKE_C_FLAGS "-g -O3 -fPIC -Wall")
  endif()
endif()

# set the g++ version 11
if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  endif()
else()
  set(CMAKE_CXX_STANDARD 11)
endif()

set(cg_root_folder ${cg_SOURCE_DIR})

# External dependencies
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/external)

# Location where external projects will be downloaded
set(DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/downloads"
    CACHE PATH "Location where external projects will be downloaded.")
mark_as_advanced(DOWNLOAD_LOCATION)

# Include the external dependencies
include(glew)
include(glext)
include(freeglut)
include(freeimage)

include_directories(${glew_INCLUDE_DIRS})
include_directories(${freeglut_INCLUDE_DIRS})
include_directories(${freeimage_INCLUDE_DIRS})
include_directories(include)

set(cg_EXTERNAL_LIBRARIES
    ${glew_STATIC_LIBRARIES}
    ${freeglut_STATIC_LIBRARIES}
    ${freeimage_STATIC_LIBRARIES})

set(cg_EXTERNAL_DEPENDENCIES
    glew
    freeglut
    freeimage)

include(homework1/homework1.cmake)
include(homework3/homework3.cmake)
include(homework4/homework4.cmake)

install(FILES ${glew_LIBRARIES}       DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES ${freeglut_LIBRARIES}   DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES ${freeimage_LIBRARIES}  DESTINATION ${CMAKE_BINARY_DIR}/bin)