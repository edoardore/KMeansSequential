cmake_minimum_required(VERSION 3.8)
project(KMeansOpenMP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp Cluster.h)
add_executable(KMeansOpenMP ${SOURCE_FILES})

