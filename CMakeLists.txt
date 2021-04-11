cmake_minimum_required (VERSION 3.17.5)

project (main)

aux_source_directory(. SRC_LIST)

add_executable(main ${SRC_LIST} enframe.c enframe.h hamming.c)

target_link_libraries (main m)