cmake_minimum_required(VERSION 3.21)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)

add_executable(Sudoku stack/stack.h stack/stack.c sudoku.h sudoku.c types.h helpers.h helpers.c main.c)
