cmake_minimum_required(VERSION 3.5)
project(fraktal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp bitmap.h bitmap.cpp)
add_executable(fraktal ${SOURCE_FILES})