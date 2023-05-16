cmake_minimum_required(VERSION 3.10)

project(testCOLREGS VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)

add_library(COLREGsLib COLREGs.cpp)

add_executable(test main.cpp)
target_link_libraries(test PUBLIC COLREGsLib)

