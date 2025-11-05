cmake_minimum_required(VERSION 3.28)
project(homework-2)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp
        matrix.cpp
        matrix.h)
