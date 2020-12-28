cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code BookManagementSystem/book.h BookManagementSystem/book.cpp BookManagementSystem/main_program.cpp BookManagementSystem/function.cpp BookManagementSystem/function.h)