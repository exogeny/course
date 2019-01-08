include(ExternalProject)

set(freeimage_DIR          ${CMAKE_CURRENT_BINARY_DIR}/freeimage/src/freeimage)
set(freeimage_URL          https://jaist.dl.sourceforge.net/project/freeimage/Source%20Distribution/3.18.0/FreeImage3180.zip)
set(freeimage_BUILD        ${CMAKE_CURRENT_BINARY_DIR}/freeimage)


if(MSVC)
  # set build type
  if(DEBUG)
    set(Configuration Debug)
  else()
    set(Configuration Release)
  endif()

  # set window sdk version
  if(CMAKE_VERSION VERSION_LESS "3.4")
    set(SDKVERSION      ${CMAKE_SYSTEM_VERSION})
  else()
    set(SDKVERSION      ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
  endif()

  # set compile version
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(Platform        X64)
  else()
    set(Platform        Win32)
  endif()

  # set tool sets
  set(TOOLSETVERSION  ${CMAKE_VS_PLATFORM_TOOLSET})
  if(MSVC_VERSION LESS 1900)
    set(SLNNAME	        ${freeimage_DIR}/FreeImage.2013.sln)
  else()
    set(SLNNAME	        ${freeimage_DIR}/FreeImage.2017.sln)
  endif()
  set(BUILD_FREEIMAGE msbuild ${SLNNAME}  /p:Platform=${Platform}
                                          /p:Configuration=${Configuration}
                                          /p:PlatformToolset=${TOOLSETVERSION} 
                                          /p:WindowsTargetPlatformVersion=${SDKVERSION})
else()
  set(BUILD_FREEIMAGE make)
endif()

set(freeimage_DIST_DIR ${freeimage_DIR}/Dist)
if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(freeimage_INCLUDE_DIR       ${freeimage_DIST_DIR}/x64)
    set(freeimage_LIBRARIES         ${freeimage_DIST_DIR}/x64/FreeImage.dll)
    set(freeimage_STATIC_LIBRARIES  ${freeimage_DIST_DIR}/x64/FreeImage.lib)
  else()
    set(freeimage_INCLUDE_DIR       ${freeimage_DIST_DIR}/x32)
    set(freeimage_LIBRARIES         ${freeimage_DIST_DIR}/x32/FreeImage.dll)
    set(freeimage_STATIC_LIBRARIES  ${freeimage_DIST_DIR}/x32/FreeImage.lib)
  endif()
endif()

ExternalProject_Add(freeimage
  PREFIX              freeimage
  URL                 ${freeimage_URL}
  URL_HASH            MD5=f8ba138a3be233a3eed9c456e42e2578
  DOWNLOAD_DIR        "${DOWNLOAD_LOCATION}"
  CONFIGURE_COMMAND   ""
  BUILD_IN_SOURCE     1
  BUILD_COMMAND       ${BUILD_FREEIMAGE}
  BUILD_BYPRODUCTS    ${freeimage_STATIC_LIBRARIES}
  INSTALL_COMMAND     "")