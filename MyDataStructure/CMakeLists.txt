cmake_minimum_required(VERSION 3.6)
project(MyDataStructure)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp KMP.h KMP.cpp Queue.h Maze.cpp Maze.h nifix2postfix.h nifix2postfix.cpp)
add_executable(MyDataStructure ${SOURCE_FILES})