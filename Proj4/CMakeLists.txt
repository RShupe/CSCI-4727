cmake_minimum_required(VERSION 3.13)
project(Proj4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Proj4 main.cpp lib/Logger.cpp lib/Logger.h mob/Knight.cpp mob/Knight.h mob/Rabbit.cpp mob/Rabbit.h)