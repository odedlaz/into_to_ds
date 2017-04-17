// Implementation of the KMeans Algorithm
// reference: http://mnemstudio.org/clustering-k-means-example-1.htm

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "include/Kmeans.h"

using std::vector;
using std::string;

void readInput(const string &filename, bool has_name, vector<Point> &points) {
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
    if (argc < 5)
        return 1;

    K = (unsigned) atoi(argv[1]);
    max_iterations = (unsigned) atoi(argv[2]);

    if ((!K) || (!max_iterations)) return 1;

    bool has_name = (bool) atoi(argv[3]);
    string fileName(argv[4]);

    vector<Point> points;
    std::cout << fileName << std::endl;
    readInput(fileName, has_name, points);

    KMeans kmeans(K, max_iterations);
    kmeans.run(points);

    return 0;
}
