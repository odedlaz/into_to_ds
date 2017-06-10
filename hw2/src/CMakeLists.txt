cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        Classifier.cpp
        include/Classifier.h
        DataReader.cpp
        include/DataReader.h
        KNNClassifier.cpp
        include/KNNClassifier.h
        main.cpp
        Perceptron.cpp
        include/Perceptron.h
        include/Point.h
        Tests.cpp
        include/Tests.h
        include/Distance.h
        EuclideanDistance.cpp
        include/EuclideanDistance.h
        ManhattanDistance.cpp
        include/ManhattanDistance.h
        MetaClassifier.cpp
        include/MetaClassifier.h CosineDistance.cpp include/CosineDistance.h)

add_executable(src ${SOURCE_FILES})