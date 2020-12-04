cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code test.cpp test_header.cpp test_header.h)