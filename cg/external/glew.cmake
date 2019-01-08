include(ExternalProject)

set(glew_URL          https://jaist.dl.sourceforge.net/project/glew/glew/2.1.0/glew-2.1.0.zip)
set(glew_BUILD        ${CMAKE_CURRENT_BINARY_DIR}/glew/src/glew)
set(glew_INSTALL      ${CMAKE_CURRENT_BINARY_DIR}/glew/install)

if(WIN32)
  if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
    set(glew_STATIC_LIBRARIES
        debug ${glew_INSTALL}/lib/glew${BUILD_ARCH}d.lib
        optimized ${glew_INSTALL}/lib/glew${BUILD_ARCH}.lib)
  else()
    if(CMAKE_BUILD_TYPE EQUAL Debug)
      set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib/glew${BUILD_ARCH}d.lib)
    else()
      set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib/glew${BUILD_ARCH}.lib)
    endif()
  endif()
  set(glew_LIBRARIES ${glew_INSTALL}/bin/glew${BUILD_ARCH}$<$<CONFIG:Debug>:d>.dll)
else()
  set(glew_LIBRARIES ${glew_INSTALL}/lib${BUILD_ARCH}/libGLEW.so.2.1.0)
  set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib${BUILD_ARCH}/libGLEW$<$<CONFIG:Debug>:d>.a)
endif()
set(glew_INCLUDE_DIRS ${glew_INSTALL}/include)

ExternalProject_Add(glew
  PREFIX            glew
  URL               ${glew_URL}
  URL_HASH          MD5=dff2939fd404d054c1036cc0409d19f1
  DOWNLOAD_DIR      "${DOWNLOAD_LOCATION}"
  BUILD_IN_SOURCE   1
  CONFIGURE_COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/glew/src/glew/build/cmake
  PATCH_COMMAND     ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/patches/glew/CMakeLists.txt ${glew_BUILD}/build/cmake
  INSTALL_COMMAND   ${CMAKE_COMMAND}  -DCMAKE_INSTALL_PREFIX=${glew_INSTALL} 
                                      -DCMAKE_BUILD_TYPE:STRING=Release
                                      -P cmake_install.cmake
)