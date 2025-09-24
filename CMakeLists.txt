cmake_minimum_required(VERSION 3.30)

project(GoogleDawnBinaries VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(external)
add_subdirectory(demo)
