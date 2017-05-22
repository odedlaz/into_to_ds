#ifndef LAB7_SUMNORMALIZER_H
#define LAB7_SUMNORMALIZER_H

#include "Normalizer.h"

class SumNormalizer : public Normalizer {
private:
    Point totalSum;
public:
    /**
     * Receives the point's amount of dimensions initializing totalSum to same size.
     * @param dimension size_t amount of dimensions
     */
    SumNormalizer(size_t dimension) : totalSum(dimension) {}
    /**
     * initializing the totalSum with the given dataset
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


#endif //LAB7_SUMNORMALIZER_H
