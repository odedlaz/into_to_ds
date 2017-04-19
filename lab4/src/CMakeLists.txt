cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        AgglomerativeClustering.cpp
        include/AgglomerativeClustering.h
        Cluster.cpp
        include/Cluster.h
        main.cpp
        include/PairDistance.h
        Point.cpp
        include/Point.h)

add_executable(src ${SOURCE_FILES})