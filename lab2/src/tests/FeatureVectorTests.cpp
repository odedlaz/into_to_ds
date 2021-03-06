#include "include/FeatureVectorTests.h"
#include "../include/FeatureVector.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

/**
 * Initialize Random Vector
 * initializing a random vector<double> with specific given number of values.
 * @param numOfValues Type int
 * @param vec Type vector<double>
 */
void initializeRandomVector(int numOfValues, std::vector<double> &vec) {
    for (int i = 0; i < numOfValues; ++i) {
        vec.push_back(std::rand() % 10 + 1);
    }
}

/**
 * Test Correlation Symmetry
 * checks if correlation symmetry exist
 * @return boolean result
 */
bool testCorrelationSymmetry() {
    std::vector<double> vecA, vecB;

    initializeRandomVector(3, vecA);
    initializeRandomVector(3, vecB);

    FeatureVector a = FeatureVector("a", vecA);
    FeatureVector b = FeatureVector("b", vecB);
    // Compare doubles in a deterministic manner
    // http://stackoverflow.com/a/18686946
    return trunc(1000. * a.getCorrelation(b)) == trunc(1000. * b.getCorrelation(a));
}
