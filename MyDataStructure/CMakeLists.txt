cmake_minimum_required(VERSION 3.6)
project(MyDataStructure)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp KMP.h KMP.cpp Queue.h Maze.cpp Maze.h nifix2postfix.h nifix2postfix.cpp LinkedList.h DLinkedList.h BinaryTree.h LinkedBTree.h QuickSort.h CountSort.h Random_Select.h MultiTree.h BinarySearchTree.h BTree.h LostTree.h LostTree.cpp MinMaxLeap.h Graph.cpp Graph.h)
add_executable(MyDataStructure ${SOURCE_FILES})