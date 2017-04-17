#include <iostream>
#include "include/TestRunner.h"
#include "include/FeatureVectorTests.h"

using std::cout;
using std::endl;


void runTests() {
    cout << "Running all tests..." << endl;
    printTestResult(testCorrelationSymmetry(),
                    "Correlation Symmetry Test");

}

void printTestResult(bool result, std::string testName) {
    std::string resultText = result ? "Success" : "Fail";
    printf("%s: %s!\n", testName.c_str(),
           resultText.c_str());
}