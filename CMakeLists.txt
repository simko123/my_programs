cmake_minimum_required(VERSION 3.24)
project(my_programs)

set(CMAKE_CXX_STANDARD 14)

include_directories(cpp/pt_labs/lab3)

add_executable(my_programs
        cpp/fl_programs/task1.cpp
        cpp/fl_programs/task2.cpp
        cpp/fl_programs/task3.cpp
        cpp/fl_programs/task4.cpp
        cpp/fl_programs/task5.cpp
        cpp/pt_labs/lab1/lab1.cpp
        cpp/pt_labs/lab2/cooler_lab2.cpp
        cpp/pt_labs/lab2/lab2.cpp
        cpp/pt_labs/lab3/main.cpp
        cpp/pt_labs/lab3/matrix.cpp
        cpp/pt_labs/lab3/matrix.hpp
        cpp/pt_labs/lab3/vector.cpp
        cpp/pt_labs/lab3/vector.hpp)
