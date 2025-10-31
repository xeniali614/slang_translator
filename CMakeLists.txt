cmake_minimum_required(VERSION 3.20)
project(slang_translator)

set(CMAKE_CXX_STANDARD 14)

add_executable(slang_translator main.cpp Slang.cpp Slang.h)