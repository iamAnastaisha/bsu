cmake_minimum_required(VERSION 3.21)
project(TestClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestClient main.cpp)

add_library(Number_lib STATIC ../Number_lib/library.cpp)
add_library(Vector_lib SHARED ../Vector_lib/library.cpp)

target_link_libraries(TestClient PRIVATE Number_lib)
target_link_libraries(TestClient PRIVATE Vector_lib)