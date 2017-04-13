cmake_minimum_required(VERSION 3.6)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

find_library(NTL_LIBRARY ntl)
find_library(GMP_LIBRARY gmp)

set(SOURCE_FILES main.cpp getCPUTime.h)

set(CMAKE_EXE_LINKER_FLAGS "-lntl -lgmpxx -lgmp -lm")

add_executable(Lab3 ${SOURCE_FILES})

target_link_libraries(Lab3 "${NTL_LIBRARY}" "${GMP_LIBRARY}")