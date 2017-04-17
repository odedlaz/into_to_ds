cmake_minimum_required(VERSION 3.6)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/Statistics.h Statistics.cpp FeatureVector.cpp include/FeatureVector.h)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(lab2 ${SOURCE_FILES})
