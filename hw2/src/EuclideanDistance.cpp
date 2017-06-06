//
// Created by odedlaz on 6/6/17.
//

#include "include/EuclideanDistance.h"
#include <math.h>

double EuclideanDistance::calculate(const Point &p1, const Point &p2) const {
    if (p1.getDimension() != p2.getDimension()) {
        return 0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < p1.getDimension(); i++) {
        sum += pow(p1[i] - p2[i], 2.0);
    }
    return sqrt(sum);
}

