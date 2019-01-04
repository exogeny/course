include(ExternalProject)

set(freeglut_URL          https://github.com/dcnieho/FreeGLUT.git)
set(freeglut_BUILD        ${CMAKE_CURRENT_BINARY_DIR}/freeglut)
set(freeglut_TAG          44cf4b5b85cf6037349c1c8740b2531d7278207d)

set(freeglut_INSTALL      ${CMAKE_CURRENT_BINARY_DIR}/freeglut/install)
set(freeglut_INCLUDE_DIRS ${freeglut_INSTALL}/include)

if(WIN32)
  if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
    set(freeglut_STATIC_LIBRARIES
        debug ${freeglut_INSTALL}/lib/freeglutd.lib
        optimized ${freeglut_INSTALL}/lib/freeglut.lib)
  else()
    if(CMAKE_BUILD_TYPE EQUAL Debug)
      set(freeglut_STATIC_LIBRARIES ${freeglut_INSTALL}/lib/freeglutd.lib)
    else()
      set(freeglut_STATIC_LIBRARIES ${freeglut_INSTALL}/lib/freeglut.lib)
    endif()
  endif()
  set(freeglut_LIBRARIES ${freeglut_INSTALL}/bin/freeglutd.dll)
else()
  set(freeglut_STATIC_LIBRARIES ${freeglut_INSTALL}/lib/libfreeglut.a)
endif()

ExternalProject_Add(freeglut
  PREFIX            freeglut
  GIT_REPOSITORY    ${freeglut_URL}
  GIT_TAG           ${freeglut_TAG}
  DOWNLOAD_DIR      "${DOWNLOAD_LOCATION}"
  BUILD_IN_SOURCE   1
  BUILD_BYPRODUCTS  ${freeglut_STATIC_LIBRARIES}
  INSTALL_DIR       ${freeglut_INSTALL}
  CMAKE_CACHE_ARGS  -DCMAKE_INSTALL_PREFIX:STRING=${freeglut_INSTALL}
                    -DINSTALL_PDB:BOOL=OFF
)