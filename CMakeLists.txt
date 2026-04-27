cmake_minimum_required(VERSION 4.1)
project(Labbar)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Labbar
        functions.cpp
        functions.h
        main.cpp
        reader.cpp
        reader.h)
