cmake_minimum_required(VERSION 3.27)

project("4.Trees&Graphs" LANGUAGES CXX C)

file(GLOB_RECURSE one_file_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

foreach(file_path ${one_file_sources})
  get_filename_component(filename "${file_path}" NAME)
  add_executable("${filename}" "${file_path}")
  set_target_properties("${filename}" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX)
    target_include_directories("${filename}" PRIVATE ..)
endforeach()

file(GLOB_RECURSE one_file_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

foreach(file_path ${one_file_sources})
  get_filename_component(filename "${file_path}" NAME)
  add_executable("${filename}" "${file_path}")
  set_target_properties("${filename}" PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    LINKER_LANGUAGE C)
    target_include_directories("${filename}" PRIVATE ..)
endforeach()
