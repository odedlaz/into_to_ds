//
// Created by odedlaz on 6/6/17.
//

#include "include/ManhattanDistance.h"
#include <math.h>

double ManhattanDistance::calculate(const Point &p1, const Point &p2) const {
    if (p1.getDimension() != p2.getDimension()) {
        return 0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < p1.getDimension(); i++) {
        sum += abs(p1[i] - p2[i]);
    }
    return sqrt(sum);
}

