cmake_minimum_required(VERSION 3.8)
project(workbench)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/arrays.cpp)

add_executable(workbench ${SOURCE_FILES})