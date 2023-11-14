cmake_minimum_required(VERSION 3.10)
project(aed2223_ci1)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(aed2223_ci1 main.cpp Tests/UverEats.cpp Tests/Restaurant.cpp Tests/Order.cpp Tests/Client.cpp Tests/Driver.cpp Tests/tests.cpp)

target_link_libraries(aed2223_ci1 gtest gtest_main)
