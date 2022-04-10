cmake_minimum_required(VERSION 3.21)
project(matr_linux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(matr_linux main.cpp Functions.h)