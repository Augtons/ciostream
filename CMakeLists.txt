cmake_minimum_required(VERSION 3.16)
project(ciostream)

set(CMAKE_C_STANDARD 99)

set(CIO_ROOT "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory("Src")
add_subdirectory("Test")
