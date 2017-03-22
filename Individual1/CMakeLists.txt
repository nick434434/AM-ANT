cmake_minimum_required(VERSION 3.6)
project(Individual1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 11)

find_library(MPIR_LIBRARY mpir)
find_library(MPIRXX_LIBRARY mpirxx)

set(SOURCE_FILES main.cpp getCPUTime.h)
add_executable(Individual1 "${SOURCE_FILES}")

target_link_libraries(Individual1 "${MPIR_LIBRARY}" "${MPIRXX_LIBRARY}")
