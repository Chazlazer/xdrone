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

# Add main.cpp explicitly
add_executable(main
    main.cpp
    ${SOURCES}
)

# Link WiringPi
target_link_libraries(main wiringPi)