//
// Created by annabel@staff.technion.ac.il on 5/3/17.
//

#include "include/Classifier.h"
#include "include/Point.h"
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

double Classifier::accuracy(const std::vector<Point> &subset) const {
    double correct(0.0);
    for (size_t i = 0; i < subset.size(); i++) {
        const Point &point = subset[i];
        if (point.getClass() == point.getPrediction())
            correct++;
    }
    return correct / (double) subset.size();
}

void Classifier::printResults(const std::vector<Point> &subset) const {
    for (int i = 0; i < subset.size(); i++) {
        const Point & point = subset[i];
        printf("%d,%s,%s\n", i, point.getPrediction().c_str(), point.getClass().c_str());
    }
}
