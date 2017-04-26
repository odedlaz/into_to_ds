cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        BSS.cpp
        include/BSS.h
        Cluster.cpp
        include/Cluster.h
        ClusterReader.cpp
        include/ClusterReader.h
        EvaluationMeasure.cpp
        include/EvaluationMeasure.h
        main.cpp
        Point.cpp
        include/Point.h
        Purity.cpp
        include/Purity.h
        SilhouetteCoeff.cpp
        include/SilhouetteCoeff.h
        TSS.cpp
        include/TSS.h
        WSS.cpp
        include/WSS.h)

add_executable(src ${SOURCE_FILES})