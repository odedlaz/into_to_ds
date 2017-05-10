cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        include/DataReader.h
        include/Evaluation.h
        include/EvaluationMeasures.h
        include/KNN.h
        include/Point.h
        DataReader.cpp
        Evaluation.cpp
        EvaluationMeasures.cpp
        KNN.cpp
        main.cpp
        Point.cpp)

add_executable(src ${SOURCE_FILES})