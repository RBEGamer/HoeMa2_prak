cmake_minimum_required(VERSION 3.7)
project(Praktikum3)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp CMyVektor.cpp CMyVektor.h CDGLSolver.cpp CDGLSolver.h)
add_executable(Praktikum3 ${SOURCE_FILES})