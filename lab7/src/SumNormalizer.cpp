#include "include/SumNormalizer.h"

bool SumNormalizer::init(const std::vector<Point> &points) {
    if (points.empty()) {
        return false;
    }

    std::vector<Point>::const_iterator iter;
    size_t dimension = points[0].getDimension();
    for (iter = points.begin(); iter != points.end(); iter++) {
        for (size_t dim = 0; dim < dimension; dim++) {
            totalSum[dim] += (*iter)[dim];
        }
    }

    return true;
}

void SumNormalizer::normalize(const Point &oldPoint, Point &newPoint) {
    newPoint = oldPoint / totalSum;
}
