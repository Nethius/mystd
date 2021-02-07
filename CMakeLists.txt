cmake_minimum_required(VERSION 3.16)
project(mystd)

set(CMAKE_CXX_STANDARD 20)

include_directories(sources)
add_executable(mystd main.cpp sources/vector/vector.h)