#include "include/FeatureVectorTests.h"
#include "../include/FeatureVector.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

void initializeRandomVector(int numOfValues, std::vector<double> &vec) {
    for (int i = 0; i < numOfValues; ++i) {
        vec.push_back(std::rand() % 10 + 1);
    }
}

bool testCorrelationSymmetry() {
    std::vector<double> vecA, vecB;

    initializeRandomVector(3, vecA);
    initializeRandomVector(3, vecB);

    FeatureVector a = FeatureVector("a", vecA);
    FeatureVector b = FeatureVector("b", vecB);
    return trunc(1000. * a.getCorrelation(b)) == trunc(1000. * b.getCorrelation(a));
}
