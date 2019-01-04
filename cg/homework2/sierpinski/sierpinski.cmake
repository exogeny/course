set(cg_sierpinski_src ${cg_root_folder}/homework2/sierpinski/sierpinski.cc)

add_executable(sierpinski             ${cg_sierpinski_src})
target_link_libraries(sierpinski      ${cg_EXTERNAL_LIBRARIES})
add_dependencies(sierpinski           ${cg_EXTERNAL_DEPENDENCIES})

install(TARGETS sierpinski            DESTINATION ${CMAKE_BINARY_DIR}/bin)