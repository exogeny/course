include(ExternalProject)

set(glew_URL          http://sourceforge.mirrorservice.org/g/gl/glew/glew/2.1.0/glew-2.1.0.zip)
set(glew_BUILD        ${CMAKE_CURRENT_BINARY_DIR}/glew/src/glew)
set(glew_INSTALL      ${CMAKE_CURRENT_BINARY_DIR}/glew/install)

if(WIN32)
  set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib/glew32.lib)
  set(glew_LIBRARIES ${glew_INSTALL}/bin/glew32.dll)
else()
  set(glew_LIBRARIES ${glew_INSTALL}/lib${BUILD_ARCH}/libGLEW.so.2.1.0)
  set(glew_STATIC_LIBRARIES ${glew_INSTALL}/lib${BUILD_ARCH}/libGLEW.a)
endif()
set(glew_INCLUDE_DIRS ${glew_INSTALL}/include)

if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(Platform        x64)
  else()
    set(Platform        Win32)
  endif()
  ExternalProject_Add(glew
    PREFIX            glew
    URL               ${glew_URL}
    URL_HASH          MD5=dff2939fd404d054c1036cc0409d19f1
    DOWNLOAD_DIR      "${DOWNLOAD_LOCATION}"
    BUILD_IN_SOURCE   1
    CONFIGURE_COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/glew/src/glew/build/cmake -A ${Platform}
    CMAKE_CACHE_ARGS  -DCMAKE_BUILD_TYPE:STRING=Release
    BUILD_COMMAND     msbuild glew.sln /p:Configuration=Release /p:Platform=${Platform}
    PATCH_COMMAND     ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/patches/glew/CMakeLists.txt ${glew_BUILD}/build/cmake
    INSTALL_COMMAND   ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${glew_INSTALL}
                                       -P cmake_install.cmake
)
else()
  ExternalProject_Add(glew
    PREFIX            glew
    URL               ${glew_URL}
    URL_HASH          MD5=dff2939fd404d054c1036cc0409d19f1
    DOWNLOAD_DIR      "${DOWNLOAD_LOCATION}"
    BUILD_IN_SOURCE   1
    CONFIGURE_COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/glew/src/glew/build/cmake
    CMAKE_CACHE_ARGS  -DCMAKE_BUILD_TYPE:STRING=Release
    PATCH_COMMAND     ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/patches/glew/CMakeLists.txt ${glew_BUILD}/build/cmake
    INSTALL_COMMAND   ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${glew_INSTALL}
                                       -P cmake_install.cmake
)
endif()