#include "include/MinMaxNormalizer.h"
#include <limits>

bool MinMaxNormalizer::init(const std::vector<Point> &points) {
    if (points.empty()) {
        return false;
    }
    // initializing min and max to corresponding limit values.
    size_t dimension = min.getDimension();
    for (size_t dim = 0; dim < dimension; dim++) {
        min[dim] = std::numeric_limits<double>::max();
        max[dim] = std::numeric_limits<double>::min();
    }

    std::vector<Point>::const_iterator iter;
    for (iter = points.begin(); iter != points.end(); iter++) {
        for (size_t dim = 0; dim < dimension; dim++) {
            double coordinate = (*iter)[dim];
            min[dim] = coordinate > min[dim] ? min[dim] : coordinate;
            max[dim] = coordinate < max[dim] ? max[dim] : coordinate;
        }
    }

    delta = max - min; // to avoid calculation of this value each normalization.
    return true;
}

void MinMaxNormalizer::normalize(const Point &oldPoint, Point &newPoint) {
    newPoint = (oldPoint - min) / delta;
}
