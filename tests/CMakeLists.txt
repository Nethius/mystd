set(BINARY ${CMAKE_PROJECT_NAME}_tests)

set(SOURCES
        main.cpp
        vectorTests.cpp)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)