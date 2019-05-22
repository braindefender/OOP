cmake_minimum_required(VERSION 3.14)
project(OOP)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP main.cpp Container.h Base.h Shapes.cpp Shapes.h Factory.cpp Factory.h)