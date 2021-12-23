cmake_minimum_required(VERSION 3.21)
project(aoc2021)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_BUILD_TYPE DEBUG)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} main.cpp)

enable_testing()
add_executable(${PROJECT_NAME}_test test.cpp)
target_link_libraries(${PROJECT_NAME}_test gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)