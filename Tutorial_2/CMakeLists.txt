cmake_minimum_required(VERSION 3.9)
project(Tutorial_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(tut2 main.c student/student.c student/studentcollection.c)