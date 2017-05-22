#ifndef LAB7_MINMAXNORMALIZER_H
#define LAB7_MINMAXNORMALIZER_H

#include "Normalizer.h"

class MinMaxNormalizer : public Normalizer {
private:
    Point min;
    Point max;
public:
    /**
     * Receives the point's amount of dimensions initializing min, max and delta to same size.
     * @param dimension size_t amount of dimensions
     */
    MinMaxNormalizer(size_t dimension) : min(dimension), max(dimension) {}
    /**
     * initializing the min, max & delta with the given dataset
     * @param points Vector<Points> that contains dataset
     * @return boolean result if init was successful.
     */
    bool init(const std::vector<Point> &points);

    /**
     * normalize oldPoint to newPoint after init is successful.
     * @param oldPoint Point to be normalized
     * @param newPoint Point to hold the normalized value
     */
    void normalize(const Point &oldPoint, Point &newPoint);
};

#endif //LAB7_MINMAXNORMALIZER_H
