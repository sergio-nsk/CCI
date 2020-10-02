cmake_minimum_required(VERSION 3.4)

file(GLOB_RECURSE one_file_sources RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

foreach(file_path ${one_file_sources})
  string(REPLACE ".cpp" "" exe_name ${file_path})
  get_filename_component(filename ${exe_name} NAME)
  add_executable(${filename} ${file_path})
  set_target_properties(${filename} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX)
    target_include_directories(${filename} PRIVATE .)
endforeach()
