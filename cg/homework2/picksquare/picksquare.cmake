set(cg_picksquare_src ${cg_root_folder}/homework2/picksquare/picksquare.cc)

add_executable(picksquare             ${cg_picksquare_src})
target_link_libraries(picksquare      ${cg_EXTERNAL_LIBRARIES})
add_dependencies(picksquare           ${cg_EXTERNAL_DEPENDENCIES})

install(TARGETS picksquare            DESTINATION ${CMAKE_BINARY_DIR}/bin)
