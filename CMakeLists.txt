cmake_minimum_required(VERSION 3.21)
project(Project3_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project3_starter_files
        main.cpp
        Project3.cpp
        UTString.h)
