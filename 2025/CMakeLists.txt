cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(
    secretentrance
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Day_01)
add_subdirectory(Day_02)
add_subdirectory(Day_03)
add_subdirectory(Day_04)
add_subdirectory(Day_05)