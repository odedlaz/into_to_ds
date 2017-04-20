#include <iostream>
#include "include/TestRunner.h"
#include "include/FeatureVectorTests.h"

using std::cout;
using std::endl;

/**
 * Test Run
 * handles test running for this lab
 */
void runTests() {
    cout << "Running all tests..." << endl;
    printTestResult(testCorrelationSymmetry(),
                    "Correlation Symmetry Test");

}

/**
 * Print Tests Result
 * prints the result of specific test.
 * @param result Type Boolean
 * @param testName Type string
 */
void printTestResult(bool result, std::string testName) {
    std::string resultText = result ? "Success" : "Fail";
    printf("%s: %s!\n", testName.c_str(),
           resultText.c_str());
}