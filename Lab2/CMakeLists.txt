cmake_minimum_required(VERSION 3.6)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp InfiniteInt.h InfiniteInt.cpp gcdLib.h gcdLib.cpp)
add_executable(Lab2 ${SOURCE_FILES})