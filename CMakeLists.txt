cmake_minimum_required(VERSION 3.21)
project(aoc2021)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

add_executable(aoc2021 main.cpp)

enable_testing()
add_executable(aoc2021_test test.cpp)
target_link_libraries(aoc2021_test gtest_main)
include(GoogleTest)
gtest_discover_tests(aoc2021_test)