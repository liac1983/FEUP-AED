cmake_minimum_required(VERSION 3.26)
project(Teste_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# Adicione a biblioteca do Google Test
include_directories(your_google_test_include_directory)  # Substitua pelo caminho correto
link_directories(your_google_test_library_directory)      # Substitua pelo caminho correto

add_executable(Teste_2
        graph.cpp
        graph.h
)

# Vincule à biblioteca do Google Test
target_link_libraries(Teste_2 gtest gtest_main)