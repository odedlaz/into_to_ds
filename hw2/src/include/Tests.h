#ifndef CLASSIFICATION_TESTS_H
#define CLASSIFICATION_TESTS_H

#include <string>
#include "Point.h"
#include "Classifier.h"
#include "Distance.h"


class Tests {

public:
    /**
     * load a dataset from a given path to a vector of points
     * @param filename std::string the path of the dataset
     * @param std::vector<Point> a vector of point to load the data to
     */
    static void loadData(const std::string &filename, std::vector<Point> &data);

    /**
     * Runs KNN evaluation using Euclidean distance method, reports the best accuracy.
     * @param all vector<Point> of all data set
     */
    static void KNNTestEuclidean(const std::vector<Point> &all);

    /**
     * Runs KNN evaluation using Manhattan distance method, reports the best accuracy.
     * @param all vector<Point> of all data set
     */
    static void KNNTestManhattan(const std::vector<Point> &all);

    /**
     * Runs Perceptron classification on a dataset.
     * splits into training and testing set, and trains the classifier.
     * then tests the accuracy using the testing set.
     * @param all vector<Point> of all data set
     * @param alpha double indicates the learning rate
     * @param epochs size_t he number of iterations through the entire training set
     */
    static void perceptronTest(const std::vector<Point> &all,
                               double alpha, size_t epochs);

    /**
     * Runs Perceptron on Logic functions (AND, XOR).
     * Trains on the entire dataset (4) and print the weights.
     * @param all vector<Point> of all data set
     * @param alpha alpha double indicates the learning rate
     * @param epochs epochs size_t he number of iterations through the entire training set
     */
    static void perceptronLogic(const std::vector<Point> &all,
                                double alpha, size_t epochs);

    /**
     * Tests the MetaClassifier.
     * Runs through several K values to find out the best accuracy obtained with MetaClassifier.
     * @param all vector<Point> entire Dataset
     */
    static void metaClassifierTest(const std::vector<Point> &all);

    enum eTests {
        testKNNEuclidean = 0, testKNNManhattan, testPerceptronLogic, testPerceptron, testMetaClassifier, numOfTests
    };
    static const std::string testNames[numOfTests];

private:
    /**
     * receives Test set and Classifier and predicts the entire test set.
     * Then checks the accuracy for the given test
     * @param subset vector<Point> of Testing set
     * @param classifier Classifier indicating which classifier to use.
     * @return double value representing the accuracy of the classifier.
     */
    static double testClassifier(std::vector<Point> &subset, const Classifier &classifier);

    /**
     * recieves Train and Test set, trains the classifier and then tests it.
     * @param trainingSet vector<Point> of training set
     * @param testingSet vector<Point> of Testing set
     * @param classifier Classifier indicating which classifier to use.
     * @return double value representing the accuracy of the classifier.
     */
    static double trainTestClassifier(const std::vector<Point> &trainingSet,
                                      std::vector<Point> &testingSet,
                                      Classifier &classifier);

    /**
     * Check several K values for a dataset to find best accuracy.
     * @param all vector<Point> of all data set
     * @param pdistance Distance indicates which distance method to use.
     * @return double value representing the best accuracy.
     */
    static double evaluateKNN(const std::vector<Point> &all, Distance *pdistance);

    /**
     * Splits the dataset into training(60%), Validation(10%) and testing(30%)
     * @param all vector<Point> entire Dataset
     * @param training vector<Point> to hold Training set
     * @param validation vector<Point> to hold Validation set
     * @param testing vector<Point> to hold testing set
     */
    static void fixedSplitThree(const std::vector<Point> &all,
                                std::vector<Point> &training,
                                std::vector<Point> &validation,
                                std::vector<Point> &testing);

    /**
     * Splits the dataset into training(70%) and testing(30%)
     * @param all vector<Point> entire Dataset
     * @param training vector<Point> to hold Training set
     * @param testing vector<Point> to hold testing set
     */
    static void fixedSplitTwo(const std::vector<Point> &all,
                              std::vector<Point> &training,
                              std::vector<Point> &testing);

};


#endif //CLASSIFICATION_TESTS_H
