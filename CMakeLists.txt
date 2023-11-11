cmake_minimum_required(VERSION 3.26)
project(PageRank)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

include_directories(test-unit)
include_directories(src)

add_executable(Main
        src/main.cpp # your main
        src/AdjacencyList.cpp src/AdjacencyList.h
        test-unit/test.cpp)

#this one doesn't include main, instead having your test.cpp
add_executable(Tests #this will be named Project1 by default - either change it to Tests or see the comment at the bottom of the file
        test-unit/test.cpp # your test file
        src/AdjacencyList.cpp src/AdjacencyList.h)
