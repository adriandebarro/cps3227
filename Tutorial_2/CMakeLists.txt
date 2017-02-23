cmake_minimum_required(VERSION 3.6)
project(Tutorial_2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAG} -Wall -std=c99")
set(SOURCE_FILES main.c ./student/student.c ./student/studentcollection.c)
add_executable(Tutorial_2 ${SOURCE_FILES})