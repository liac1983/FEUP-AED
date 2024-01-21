cmake_minimum_required(VERSION 3.10)
project(CLion_CI2_P)

set(CMAKE_CXX_STANDARD 11)

set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(CLion_CI2_P main.cpp Tests/tests.cpp Tests/Graph.h Tests/GraphOps.cpp)

target_link_libraries(CLion_CI2_P gtest gtest_main)
