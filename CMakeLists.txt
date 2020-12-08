cmake_minimum_required(VERSION 3.16)
project(uebung5)

set(CMAKE_CXX_STANDARD 14)

#needed for CLion compilation
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(uebung5 main.cpp World.cpp World.h Robot.cpp Robot.h)