cmake_minimum_required(VERSION 3.16)
project(mystd)

set(CMAKE_CXX_STANDARD 20)

include_directories(sources tests)

add_subdirectory(lib/gtest)

set(SOURCES
        main.cpp
        tests/vector/vectorTests.cpp)

set(HEADERS
        sources/vector/vector.h)

set(BINARY ${CMAKE_PROJECT_NAME}_tests)

add_executable(${BINARY} ${SOURCES} ${HEADERS})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest)