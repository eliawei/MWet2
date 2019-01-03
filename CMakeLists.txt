cmake_minimum_required(VERSION 3.5)
project(Hash)

set(CMAKE_CXX_STANDARD 11)

add_executable(Hash main.cpp Hash.cpp Hash.h DynamicArr.cpp DynamicArr.h List.h Image.h
        Image.cpp exceptions.h)