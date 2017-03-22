cmake_minimum_required(VERSION 3.6)
project(Lab1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tests.h InfiniteInt.h InfiniteInt.cpp make_graphs.h getCPUTime.h)
add_executable(Lab1 ${SOURCE_FILES})