cmake_minimum_required(VERSION 3.6)
project(lab3_KMeans)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Kmeans.cpp Kmeans.h Cluster.cpp Cluster.h Point.cpp Point.h)
add_executable(lab3_KMeans ${SOURCE_FILES})