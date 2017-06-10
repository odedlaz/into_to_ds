//
// Created by annabel@staff.technion.ac.il on 5/5/17.
//

#include "include/Tests.h"
#include "include/KNNClassifier.h"
#include <fstream>
#include <string>
#include "include/KNNClassifier.h"
#include "include/Perceptron.h"
#include <iostream>
#include <algorithm>
#include "include/DataReader.h"
#include "include/EuclideanDistance.h"
#include "include/ManhattanDistance.h"
#include "include/MetaClassifier.h"

using std::string;
using std::cout;
using std::endl;

const std::string Tests::testNames[numOfTests] = {"testKNNEuclidean", "testKNNManhattan", "testPerceptronLogic",
                                                  "testPerceptron", "testMetaClassifier"};

void Tests::loadData(const string &filename, std::vector<Point> &data) {
    DataReader dr;
    dr.read(filename, data);
}

double Tests::testClassifier(std::vector<Point> &subset, const Classifier &classifier) {
    for (size_t i = 0; i < subset.size(); i++) {
        classifier.predict(subset[i]);
    }
    return classifier.accuracy(subset);
}

double Tests::trainTestClassifier(const std::vector<Point> &trainingSet,
                                  std::vector<Point> &testingSet,
                                  Classifier &classifier) {
    if (trainingSet.empty() || testingSet.empty())
        return 0;

    if (!classifier.train(trainingSet))
        return 0;

    return testClassifier(testingSet, classifier);
}

double Tests::evaluateKNN(const std::vector<Point> &all, Distance *pdistance) {
    const size_t kvalues = 5;
    size_t k_neigbours[kvalues] = {1, 3, 5, 7, 10};
    double accuracy[kvalues] = {0, 0, 0, 0, 0};
    std::vector<Point> training;
    std::vector<Point> validation;
    std::vector<Point> testing;
    fixedSplitThree(all, training, testing, validation);
    for (size_t i = 0; i < kvalues; i++) {
        KNNClassifier knn(k_neigbours[i], pdistance);
        accuracy[i] = trainTestClassifier(training, validation, knn);
    }
    double *ptr = std::max_element(accuracy, accuracy + kvalues);
    size_t k_position = ptr - accuracy;
    KNNClassifier knn(k_neigbours[k_position], pdistance);
    double acc_final = trainTestClassifier(training, testing, knn);
    knn.printResults(testing);
    return acc_final;
}

void Tests::KNNTestEuclidean(const std::vector<Point> &all) {
    EuclideanDistance *ptrDistance = new EuclideanDistance();
    cout << "KNN Euclidean distance accuracy is:" << evaluateKNN(all, ptrDistance) << endl;
    delete ptrDistance;

}

void Tests::KNNTestManhattan(const std::vector<Point> &all) {
    ManhattanDistance *ptrDistance = new ManhattanDistance();
    cout << "KNN Manhattan distance accuracy is:" << evaluateKNN(all, ptrDistance) << endl;
    delete ptrDistance;
}

void Tests::perceptronTest(const std::vector<Point> &all,
                           double alpha, size_t epochs) {
    size_t dimension = all[0].getDimension();
    Perceptron perceptron(dimension, alpha, epochs);
    perceptron.init();
    perceptron.printWeights();
    std::vector<Point> training;
    std::vector<Point> testing;
    fixedSplitTwo(all, training, testing);
    double accuracy = trainTestClassifier(training, testing, perceptron);
    perceptron.printWeights();
    perceptron.printResults(testing);
    cout << "Perceptron accuracy is:" << accuracy << endl;
}

void Tests::perceptronLogic(const std::vector<Point> &all,
                            double alpha, size_t epochs) {
    size_t dimension = all[0].getDimension();
    Perceptron perceptron(dimension, alpha, epochs);
    perceptron.init();
    perceptron.printWeights();
    perceptron.train(all);
    perceptron.printWeights();
}

/*void Tests::metaClassifierTest(const std::vector<Point> &all) {
    Distance *ptrDistance = new EuclideanDistance();
    MetaClassifier metaClassifier(3, all, ptrDistance);
    std::vector<Point> training;
    std::vector<Point> testing;
    fixedSplitTwo(all, training, testing);
    cout << "MetaClassifier accuracy is:" << trainTestClassifier(training, testing, metaClassifier) << endl;
}*/

void Tests::metaClassifierTest(const std::vector<Point> &all) {
    Distance *pdistance = new EuclideanDistance();
    const size_t kvalues = 5;
    size_t k_neigbours[kvalues] = {1, 3, 5, 7, 10};
    double accuracy[kvalues] = {0, 0, 0, 0, 0};
    std::vector<Point> training;
    std::vector<Point> testing;
    fixedSplitTwo(all, training, testing);

    for (size_t i = 0; i < kvalues; i++) {
        MetaClassifier metaClassifier(k_neigbours[i], all, pdistance);
        accuracy[i] = trainTestClassifier(training, testing, metaClassifier);
    }

    double *ptr = std::max_element(accuracy, accuracy + kvalues);
    size_t k_position = ptr - accuracy;
    MetaClassifier cls(k_neigbours[k_position], all, pdistance);
    double acc_final = trainTestClassifier(training, testing, cls);
    cout << "MetaClassifier accuracy is:" << acc_final << endl;
}

void Tests::fixedSplitThree(const std::vector<Point> &all,
                            std::vector<Point> &training,
                            std::vector<Point> &validation,
                            std::vector<Point> &testing) {
    size_t train_size = (all.size() * 60) / 100;  // 60 percent of samples go to training
    size_t val_size = (all.size() * 10) / 100;    // 10 percent to validation
    size_t test_size = all.size() - (train_size + val_size); //the rest goes for testing
    std::copy(all.begin(), all.begin() + train_size, back_inserter(training));
    std::copy(all.begin() + train_size, all.begin() + train_size + val_size, back_inserter(validation));
    std::copy(all.begin() + train_size + val_size, all.end(), back_inserter(testing));
}

void Tests::fixedSplitTwo(const std::vector<Point> &all,
                          std::vector<Point> &training,
                          std::vector<Point> &testing) {
    size_t train_size = (all.size() * 70) / 100; //70 percent of samples go to training
    std::copy(all.begin(), all.begin() + train_size, back_inserter(training));
    std::copy(all.begin() + train_size, all.end(), back_inserter(testing));
}