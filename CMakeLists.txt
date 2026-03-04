cmake_minimum_required(VERSION 3.10)

project(xdrone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/source
)

# Source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/source/*.cpp
)

add_executable(main
    main.cpp
    ${SOURCES}
)

# Find RF24 library
find_library(RF24_LIB
    NAMES rf24
    PATHS /usr/local/lib
)

# Link libraries
target_link_libraries(main
    wiringPi
    ${RF24_LIB}
    pthread
)