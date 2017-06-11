#include "include/CosineDistance.h"
#include <math.h>

double CosineDistance::calculate(const Point &p1, const Point &p2) const {
    return dotProduct(p1, p2) / (magnitude(p1) * magnitude(p2));
}

double CosineDistance::dotProduct(const Point &p1, const Point &p2) const {
    double sum(0.0);
    for (int i = 0; i < p1.getDimension(); i++) {
        sum += p1[i] * p2[i];
    }
    return sum;
}

double CosineDistance::magnitude(const Point &p) const {
    double sum(0.0);
    for (int i = 0; i < p.getDimension(); i++) {
        sum += pow(p[i], 2);
    }
    return sqrt(sum);
}
