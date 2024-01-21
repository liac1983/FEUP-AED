cmake_minimum_required(VERSION 3.10)
project(aed2324_ci1_v1)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(aed2324_ci1_v1 main.cpp Tests/tests.cpp Tests/callCenter.cpp Tests/agent.cpp Tests/client.cpp Tests/order.cpp)

target_link_libraries(aed2324_ci1_v1 gtest gtest_main)
