cmake_minimum_required(VERSION 4.0)
project(CurrentAnalysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(CurrentAnalysis main.cpp
        DynamicArray.h
        Matrix.cpp
        Matrix.h
        InputReader.cpp
        InputReader.h)
