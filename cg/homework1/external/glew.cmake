include(ExternalProject)

set(glew_URL          https://jaist.dl.sourceforge.net/project/glew/glew/2.1.0/glew-2.1.0.zip)
set(glew_BUILD        ${CMAKE_CURRENT_BINARY_DIR}/glew)
set(glew_INSTALL      ${glew_BUILD}/install)

if(CMAKE_CL_64)
  set(glew_TARGET  64)
else()
  set(glew_TARGET  32)
endif()

if(WIN32)
  if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
    set(glew_STATIC_LIBRARIES
        debug ${glew_INSTALL}/lib/glew${glew_TARGET}d.lib
        optimized ${glew_INSTALL}/lib/glew${glew_TARGET}.lib)
  else()
    if(CMAKE_BUILD_TYPE EQUAL Debug)
      set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib/glew${glew_TARGET}d.lib)
    else()
      set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib/glew${glew_TARGET}.lib)
    endif()
  endif()
  if(CMAKE_CL_64)
    set(glew_LIBRARIES ${glew_INSTALL}/bin/glew64d.dll)
  else()
    set(glew_LIBRARIES ${glew_INSTALL}/bin/glew32d.dll)
  endif()
else()
  set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib/libglew${glew_TARGET}.a)
endif()
set(glew_INCLUDE_DIRS ${glew_INSTALL}/include)

ExternalProject_Add(glew
  PREFIX            glew
  URL               ${glew_URL}
  URL_HASH          MD5=dff2939fd404d054c1036cc0409d19f1
  DOWNLOAD_DIR      "${DOWNLOAD_LOCATION}"
  BUILD_IN_SOURCE   1
  CONFIGURE_COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/glew/src/glew/build/cmake
  BUILD_BYPRODUCTS  ${glew_STATIC_LIBRARIES}
  INSTALL_COMMAND   ${CMAKE_COMMAND}  -DCMAKE_INSTALL_PREFIX=${glew_INSTALL} 
                                      -DBUILD_TYPE=$(Configuration) 
                                      -P cmake_install.cmake
)