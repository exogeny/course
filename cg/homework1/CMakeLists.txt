cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(homework1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

# External dependencies
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/external)

# Location where external projects will be downloaded
set(DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/downloads"
    CACHE PATH "Location where external projects will be downloaded.")
mark_as_advanced(DOWNLOAD_LOCATION)

# Include the external dependencies
include(glew)
include(freeglut)
include(freeimage)

include_directories(${glew_INCLUDE_DIRS})
include_directories(${freeglut_INCLUDE_DIRS})
include_directories(${freeimage_INCLUDE_DIRS})

FILE(GLOB SOURCES "*.cc")
ADD_EXECUTABLE(homework1 ${SOURCES})

TARGET_LINK_LIBRARIES(homework1 ${glew_STATIC_LIBRARIES})
TARGET_LINK_LIBRARIES(homework1 ${freeglut_STATIC_LIBRARIES})
TARGET_LINK_LIBRARIES(homework1 ${freeimage_STATIC_LIBRARIES})

set(RAW_DATA_IMAGE                    "DATA/Crate.bmp")

INSTALL(TARGETS homework1             DESTINATION ${CMAKE_BINARY_DIR}/bin)
INSTALL(FILES ${glew_LIBRARIES}       DESTINATION ${CMAKE_BINARY_DIR}/bin)
INSTALL(FILES ${freeglut_LIBRARIES}   DESTINATION ${CMAKE_BINARY_DIR}/bin)
INSTALL(FILES ${freeimage_LIBRARIES}  DESTINATION ${CMAKE_BINARY_DIR}/bin)
INSTALL(FILES ${RAW_DATA_IMAGE}       DESTINATION ${CMAKE_BINARY_DIR}/bin/DATA)