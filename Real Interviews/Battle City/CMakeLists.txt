cmake_minimum_required (VERSION 3.1)

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

project (BattleCity)

set (sources level.cpp main.cpp)

add_executable(BattleCity ${sources})
