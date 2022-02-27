cmake_minimum_required(VERSION 3.21)
project(TestClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestClient main.cpp)

include_directories(../Number_lib/library.h)
include_directories(../Vector_lib/library.h)

add_library(Number_lib STATIC ../Number_lib/library.cpp ../Number_lib/cmake-build-debug/libNumber_lib.a)
add_library(Vector_lib SHARED ../Vector_lib/library.cpp ../Vector_lib/cmake-build-debug/libVector_lib.so)

target_link_libraries(TestClient PUBLIC Number_lib)
target_link_libraries(TestClient PUBLIC Vector_lib)