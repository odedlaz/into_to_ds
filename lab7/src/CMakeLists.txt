cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(SOURCE_FILES
        DataReader.cpp
        include/DataReader.h
        Evaluation.cpp
        include/Evaluation.h
        EvaluationMeasures.cpp
        include/EvaluationMeasures.h
        KNN.cpp
        include/KNN.h
        main.cpp
        MinMaxNormalizer.cpp
        include/MinMaxNormalizer.h
        include/Normalizer.h
        Point.cpp
        include/Point.h
        SumNormalizer.cpp
        include/SumNormalizer.h
        ZNormalizer.cpp
        include/ZNormalizer.h)

add_executable(src ${SOURCE_FILES})
