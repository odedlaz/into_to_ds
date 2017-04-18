cmake_minimum_required(VERSION 3.6)
project(intro_to_ds_hw1)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp include/Cluster.h Cluster.cpp include/KMedoids.h KMedoids.cpp include/Point.h Point.cpp tests/include/Tests.h tests/Tests.cpp include/Kmeans.h Kmeans.cpp include/SeedsGenerator.h SeedsGenerator.cpp)
add_executable(lab3_KMeans ${SOURCE_FILES})
