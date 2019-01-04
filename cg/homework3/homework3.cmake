set(cg_sphere_src ${cg_root_folder}/homework3/sphere.cc)
set(cg_transform_src ${cg_root_folder}/homework3/transform.cc)

add_executable(sphere             ${cg_sphere_src})
target_link_libraries(sphere      ${cg_EXTERNAL_LIBRARIES})
add_dependencies(sphere           ${cg_EXTERNAL_DEPENDENCIES})

add_executable(transform          ${cg_transform_src})
target_link_libraries(transform   ${cg_EXTERNAL_LIBRARIES})
add_dependencies(transform        ${cg_EXTERNAL_DEPENDENCIES})

install(TARGETS sphere            DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(TARGETS transform         DESTINATION ${CMAKE_BINARY_DIR}/bin)