#include <limits>
#include "include/MinMaxNormalizer.h"

bool MinMaxNormalizer::init(const std::vector<Point> &points) {
    if (points.empty())
        return false;
    // initializing min and max to corresponding limit values.
    for (size_t dim = 0; dim < min.getDimension(); dim++) {
        min[dim] = std::numeric_limits<double>::max();
        max[dim] = std::numeric_limits<double>::min();
    }
    for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); iter++) {
        for (size_t dim = 0; dim < points[0].getDimension(); dim++) {
            min[dim] = (*iter)[dim] > min[dim] ? min[dim] : (*iter)[dim];
            max[dim] = (*iter)[dim] < max[dim] ? max[dim] : (*iter)[dim];
        }
    }
    delta = max - min; // to avoid calculation of this value each normalization.
    return true;
}

void MinMaxNormalizer::normalize(const Point &oldPoint, Point &newPoint) {
    newPoint = (oldPoint - min) / delta;
}
