cmake_minimum_required(VERSION 3.8)
project(graph)

set(CMAKE_CXX_STANDARD 11)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

set(SOURCE_FILES main.cpp src/graph.cpp src/graph.h src/graphAlgorithms.cpp src/weightedGraph.cpp src/weightedGraph.h)
add_executable(graph ${SOURCE_FILES})

set(TEST_SOURCE_FILES test/graphTest.cpp src/graph.cpp src/graph.h src/graphAlgorithms.cpp src/weightedGraph.cpp src/weightedGraph.h)
add_executable(graphTest ${TEST_SOURCE_FILES})

# add gtest headers
include_directories(/usr/local/include)

# add gtest libraries
link_directories(/usr/local/lib)

ADD_LIBRARY(gtest STATIC IMPORTED)
SET_TARGET_PROPERTIES(gtest PROPERTIES
        IMPORTED_LOCATION /usr/local/lib/libgtest.a)
ADD_LIBRARY(gtest_main STATIC IMPORTED)
SET_TARGET_PROPERTIES(gtest_main PROPERTIES
        IMPORTED_LOCATION /usr/local/lib/libgtest_main.a)
TARGET_LINK_LIBRARIES(graphTest gtest gtest_main)