cmake_minimum_required(VERSION 3.13)
project(Project_1_Pipes)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_1_Pipes main.cpp lib/Logger.cpp lib/Logger.h mob/Knight.cpp mob/Knight.h mob/Rabbit.cpp mob/Rabbit.h)