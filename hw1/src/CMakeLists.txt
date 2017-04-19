cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        Cluster.cpp
        include/Cluster.h
        Kmeans.cpp
        include/Kmeans.h
        KMedoids.cpp
        include/KMedoids.h
        main.cpp
        Point.cpp
        include/Point.h
        SeedsGenerator.cpp
        include/SeedsGenerator.h
        tests/Tests.cpp
        tests/include/Tests.h)

add_executable(src ${SOURCE_FILES})