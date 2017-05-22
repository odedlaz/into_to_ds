#include "include/MinMaxNormalizer.h"
#include <limits>

bool MinMaxNormalizer::init(const std::vector<Point> &points) {
    if (points.empty()) {
        return false;
    }

    for (size_t i = 0; i < points[0].getDimension(); i++) {
        double pointMax(std::numeric_limits<double>::min());
        double pointMin(std::numeric_limits<double>::max());

        for (std::vector<Point>::size_type dim = 0; dim < points.size(); dim++) {
            double coordinate = points[dim][i];
            pointMax = coordinate > pointMax ? coordinate : pointMax;
            pointMin = coordinate < pointMin ? coordinate : pointMin;
        }

        min[i] = pointMin;
        max[i] = pointMax;
    }

    return true;
}

void MinMaxNormalizer::normalize(const Point &oldPoint, Point &newPoint) {
    newPoint = (oldPoint - min) / (max - min);
}
