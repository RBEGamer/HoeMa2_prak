cmake_minimum_required(VERSION 3.7)
project(MATHE_P5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp magic_random.cpp magic_random.h lotto.cpp lotto.h)
add_executable(MATHE_P5 ${SOURCE_FILES})