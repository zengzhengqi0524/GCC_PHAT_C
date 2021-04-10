cmake_minimum_required (VERSION 3.17.5)

project (main)

aux_source_directory(. SRC_LIST)

add_executable(main ${SRC_LIST})

target_link_libraries (main m)