cmake_minimum_required(VERSION 3.8)
project(lab06)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c imp.h node.c)
add_executable(lab06 ${SOURCE_FILES})