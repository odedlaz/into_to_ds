#!/usr/bin/env bash
set -e

function finish {
   echo "not all diffs passed!"
}

trap finish ERR

./src ../data/pima-indians-diabetes.mm testKNNEuclidean | diff ../data/outputs/diabetes_KNN_E -
./src ../data/pima-indians-diabetes.mm testKNNManhattan | diff ../data/outputs/diabetes_KNN_M -
./src ../data/pima-indians-diabetes.mm testPerceptron | diff ../data/outputs/diabetes_Perceptron -

./src ../data/heart.dat.mm testKNNEuclidean | diff ../data/outputs/heart_KNN_E -
./src ../data/heart.dat.mm testKNNManhattan | diff ../data/outputs/heart_KNN_M -
./src ../data/heart.dat.mm testPerceptron | diff ../data/outputs/heart_Perceptron -

./src ../data/and.data testPerceptronLogic | diff ../data/outputs/and.out -
./src ../data/xor.data testPerceptronLogic | diff ../data/outputs/xor.out -


