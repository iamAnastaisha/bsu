cmake_minimum_required(VERSION 3.21)
project(Vector_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(Vector_lib SHARED library.cpp)

add_library(Number_lib STATIC library.cpp ../Number_lib/cmake-build-debug/libNumber_lib.a)


target_link_libraries(Vector_lib PUBLIC Number_lib)