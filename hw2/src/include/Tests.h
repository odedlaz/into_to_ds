//
// Created by annabel@staff.technion.ac.il on 5/5/17.
//

#ifndef CLASSIFICATION_TESTS_H
#define CLASSIFICATION_TESTS_H

#include <string>
#include "Point.h"
#include "Classifier.h"
#include "Distance.h"


class Tests {

public:
    static void loadData(const std::string &filename, std::vector<Point> &data);

    static void KNNTestEuclidean(const std::vector<Point> &all);

    static void KNNTestManhattan(const std::vector<Point> &all);

    static void perceptronTest(const std::vector<Point> &all,
                               double alpha, size_t epochs);

    static void perceptronLogic(const std::vector<Point> &all,
                                double alpha, size_t epochs);

    static void metaClassifierTest(const std::vector<Point> &all);

    enum eTests {
        testKNNEuclidean = 0, testKNNManhattan, testPerceptronLogic, testPerceptron, testMetaClassifier, numOfTests
    };
    static const std::string testNames[numOfTests];

private:
    static double testClassifier(std::vector<Point> &subset, const Classifier &classifier);

    static double trainTestClassifier(const std::vector<Point> &trainingSet,
                                      std::vector<Point> &testingSet,
                                      Classifier &classifier);

    static double evaluateKNN(const std::vector<Point> &all, Distance *pdistance);

    static void fixedSplitThree(const std::vector<Point> &all,
                                std::vector<Point> &training,
                                std::vector<Point> &validation,
                                std::vector<Point> &testing);

    static void fixedSplitTwo(const std::vector<Point> &all,
                              std::vector<Point> &training,
                              std::vector<Point> &testing);

};


#endif //CLASSIFICATION_TESTS_H
