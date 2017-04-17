cmake_minimum_required(VERSION 3.6)
project(lab3_KMeans)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Kmeans.cpp include/Kmeans.h Cluster.cpp include/Cluster.h Point.cpp include/Point.h)
add_executable(lab3_KMeans ${SOURCE_FILES})
