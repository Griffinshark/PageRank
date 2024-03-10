cmake_minimum_required(VERSION 3.26)
project(PageRank)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

include_directories(test-unit)
include_directories(src)

add_executable(Main
        src/main.cpp # your main
        src/AdjacencyList.cpp src/AdjacencyList.h)

#this one doesn't include main, instead having your test.cpp
add_executable(Tests #this will be named Project1 by default - either change it to Tests or see the comment at the bottom of the file
        test-unit/test.cpp # your test file
        src/AdjacencyList.cpp src/AdjacencyList.h)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
