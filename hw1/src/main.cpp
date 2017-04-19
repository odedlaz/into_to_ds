// Implementation of the KMeans Algorithm
// reference: http://mnemstudio.org/clustering-k-means-example-1.htm

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "tests/include/Tests.h"
#include "include/SeedsGenerator.h"

using std::vector;
using std::string;

bool testExists(string testName) {
    for (int i = 0; i < Tests::testNames->length(); ++i) {
        if (testName == Tests::testNames[i]) {
            return true;
        }
    }
    return false;
}

const string getAvailableTests() {
    string text = string(Tests::testNames[0].c_str());

    for (int i = 1; i < Tests::testNames->length() - 1; ++i) {
        string test = Tests::testNames[i];

        // ignore empty test cases
        if (test == "\0") {
            continue;
        }
        text.append(" ");
        text.append(test.c_str());
    }
    text.append("\n");
    return text;
}

bool readInput(const string &filename, vector<Point> &points) {
    std::ifstream file;
    file.open(filename.c_str(), std::ifstream::in);
    if (!file.is_open()) {
        return false;
    }

    string line;
    // read data from file
    size_t pointID = 0;
    while (getline(file, line)) {
        vector<double> values;
        std::istringstream iss(line);
        string point_name;
        iss >> point_name;
        while (iss.good()) {
            double dval(0.0);
            iss >> dval;
            values.push_back(dval);
        }
        Point p(pointID, values, point_name);
        points.push_back(p);
        pointID++;
    }

    file.close();
    return true;
}

int main(int argc, char *argv[]) {
    unsigned K(0), max_iterations(0);

    if (argc < 5) {
        printf("Usage: %s <K> <max_iterations> <input_file> <test_name>\n",
               argv[0]);
        return 1;
    }

    K = (unsigned) atoi(argv[1]);
    max_iterations = (unsigned) atoi(argv[2]);
    string fileName(argv[3]);
    string testName(argv[4]);

    if (K <= 0 || max_iterations <= 0) {
        printf("K & Max Iterations have to be positive\n");
        return 1;
    }

    if (!testExists(testName)) {
        std::string text = getAvailableTests();
        printf("test '%s' doesn't exist. Available tests: %s\n",
               testName.c_str(),
               text.c_str());
        return 1;
    }

    //we initialize the random number generator to a seed
    SeedsGenerator::init();

    vector<Point> points;
    if (!readInput(fileName, points)) {
        printf("couldn't open file '%s' for reading\n", fileName.c_str());
        return 1;
    }

    printf("test '%s' | k: %d | max iterations: %d | num of points: %ld\n",
           testName.c_str(),
           K,
           max_iterations,
           points.size());

    readInput(fileName, points);

    if (testName == Tests::testNames[Tests::eTestKMeans])
        Tests::testKMeans(K, max_iterations, points); /*
    else if (testName == Tests::testNames[Tests::eTestKMedoids])
        Tests::testKMedoids(K, max_iterations, points);
    else if (testName == Tests::testNames[Tests::eTestKMeansSSE])
        Tests::testKMeansSSE(K, max_iterations, points);
    else if (testName == Tests::testNames[Tests::eTestKMedoidsSSE])
        Tests::testKMedoidsSSE(K, max_iterations, points); */

    return 0;
}



