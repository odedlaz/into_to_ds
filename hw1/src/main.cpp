// Implementation of the KMeans Algorithm
// reference: http://mnemstudio.org/clustering-k-means-example-1.htm

#include "include/SeedsGenerator.h"
#include "tests/include/Tests.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::vector;
using std::string;

/** load features from dataset to a a vector of Point
 *  @param fileName Type string
 *  @param points Type vector<Point>&
 */
void readInput(const string &filename, vector<Point> &points) {
    std::ifstream file;
    file.open(filename.c_str(), std::ifstream::in);

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
}

int main(int argc, char *argv[]) {
    unsigned K(0), max_iterations(0);
    if (argc < 5) {
        return 1;
    }

    K = (unsigned) atoi(argv[1]);
    max_iterations = (unsigned) atoi(argv[2]);

    if ((!K) || (!max_iterations)) {
        return 1;
    }

    string fileName(argv[3]);
    string testName(argv[4]);

    // we initialize the random number generator to a seed
    SeedsGenerator::init();

    // load the dataset from given path into the points vector
    vector<Point> points;
    readInput(fileName, points);

    // run tests
    if (testName == Tests::testNames[Tests::eTestKMeans])
        Tests::testKMeans(K, max_iterations, points);
    else if (testName == Tests::testNames[Tests::eTestKMedoids])
        Tests::testKMedoids(K, max_iterations, points);
    else if (testName == Tests::testNames[Tests::eTestKMeansSSE])
        Tests::testKMeansSSE(K, max_iterations, points);
    else if (testName == Tests::testNames[Tests::eTestKMedoidsSSE])
        Tests::testKMedoidsSSE(K, max_iterations, points);

    return 0;
}
