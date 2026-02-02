# Autor: Jan Englert
# Grupa: Piątek Nieparzysty
# Tytuł: Kalkulator napięć
# Data edycji: 02.02.2026

cmake_minimum_required(VERSION 4.0)
project(CurrentAnalysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(VoltageCalculator main.cpp
        DynamicArray.h
        Matrix.h
        InputReader.cpp
        InputReader.h
        EquationSolver.h)
