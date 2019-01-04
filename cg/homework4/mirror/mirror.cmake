set(cg_mirror_src ${cg_root_folder}/homework4/mirror/mirror.cc)

add_executable(mirror ${cg_mirror_src})
target_link_libraries(mirror ${cg_EXTERNAL_LIBRARIES})
add_dependencies(mirror ${cg_EXTERNAL_DEPENDENCIES})
add_dependencies(mirror glext)

set(RAW_DATA_IMAGE                    "${cg_root_folder}/homework4/mirror/Data/marble.jpg")

install(TARGETS mirror                DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES ${RAW_DATA_IMAGE}       DESTINATION ${CMAKE_BINARY_DIR}/bin/Data)