cmake_minimum_required(VERSION 3.13)
project(Proj3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Proj3 main.cpp TLB.cpp TLB.h PageTable.cpp PageTable.h Address.cpp Address.h L1Cache.cpp L1Cache.h L2Cache.cpp L2Cache.h)