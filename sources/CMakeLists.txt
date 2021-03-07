set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cpp)
set(HEADERS
        vector/vector.h)

add_executable(${BINARY}_run ${SOURCES} ${HEADERS})

add_test(NAME ${BINARY} COMMAND ${BINARY})

add_library(${BINARY}_lib STATIC ${SOURCES})