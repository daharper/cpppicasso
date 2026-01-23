cmake_minimum_required(VERSION 4.1)
project(cpppicasso)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpppicasso main.cpp
        Canvas.h
        Palette.h
        Utils.h)
