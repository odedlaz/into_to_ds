#include <iostream>
#include "include/Tests.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using std::string;
using std::vector;


int main(int argc, char *argv[]) {
    if (argc < 3)
        return -1;

    string dataFile(argv[1]);
    vector<Point> allData;
    Tests::loadData(dataFile, allData);
    string testName(argv[2]);

    if (testName == Tests::testNames[Tests::testKNNEuclidean])
        Tests::KNNTestEuclidean(allData);
    else if (testName == Tests::testNames[Tests::testKNNManhattan])
        Tests::KNNTestManhattan(allData);
    else if (testName == Tests::testNames[Tests::testPerceptronLogic])
        Tests::perceptronLogic(allData, 0.001, 5000);
    else if (testName == Tests::testNames[Tests::testPerceptron])
        Tests::perceptronTest(allData, 0.0001, 5000);
    else if (testName == Tests::testNames[Tests::testMetaClassifier])
        Tests::metaClassifierTest(allData);

    return 0;
}