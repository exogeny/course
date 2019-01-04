set(cg_homework1_src ${cg_root_folder}/homework1/main.cc)

add_executable(homework1 ${cg_homework1_src})
target_link_libraries(homework1 ${cg_EXTERNAL_LIBRARIES})
add_dependencies(homework1 ${cg_EXTERNAL_DEPENDENCIES})

set(RAW_DATA_IMAGE                    "${cg_root_folder}/homework1/Data/Crate.bmp")

install(TARGETS homework1             DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES ${RAW_DATA_IMAGE}       DESTINATION ${CMAKE_BINARY_DIR}/bin/Data)