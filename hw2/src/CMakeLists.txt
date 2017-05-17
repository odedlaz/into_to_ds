cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        Classifier.cpp
        Classifier.h
        DataReader.cpp
        DataReader.h
        KNNClassifier.cpp
        KNNClassifier.h
        main.cpp
        Perceptron.cpp
        Perceptron.h
        Point.cpp
        Point.h
        Tests.cpp
        Tests.h)

add_executable(src ${SOURCE_FILES})