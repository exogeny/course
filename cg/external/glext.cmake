include(ExternalProject)

set(glext_DIR          ${CMAKE_CURRENT_BINARY_DIR}/glext/src/glext)
set(glext_URL          https://netix.dl.sourceforge.net/project/glextwin32/glext_src.zip)
set(glext_BUILD        ${CMAKE_CURRENT_BINARY_DIR}/glext)

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
  if(CMAKE_CL_64)
    set(Platform        X64)
  else()
    set(Platform        Win32)
  endif()

  # set tool sets
  set(TOOLSETVERSION  ${CMAKE_VS_PLATFORM_TOOLSET})
  set(SLNNAME         ${glext_DIR}/glext/glext.vcxproj)

  set(BUILD_GLEXT msbuild ${SLNNAME}  /p:Platform=${Platform}
                                      /p:Configuration=${Configuration}
                                      /p:PlatformToolset=${TOOLSETVERSION} 
                                      /p:WindowsTargetPlatformVersion=${SDKVERSION})
else()
  set(BUILD_GLEXT make)
endif()

ExternalProject_Add(glext
  PREFIX              glext
  URL                 ${glext_URL}
  URL_HASH            MD5=c42c567da4d53582d38ea02da8f06e41
  DOWNLOAD_DIR        "${DOWNLOAD_LOCATION}"
  CONFIGURE_COMMAND   ""
  BUILD_IN_SOURCE     1
  BUILD_COMMAND       ${BUILD_GLEXT}
  BUILD_BYPRODUCTS    ${glext_STATIC_LIBRARIES}
  INSTALL_COMMAND     "")