#ifndef LAB7_NORMALIZER_H
#define LAB7_NORMALIZER_H

#include <vector>
#include "Point.h"




class Normalizer {
public:
    /**
     * initializing the min, max & delta with the given dataset
     * @param points Vector<Points> that contains dataset
     * @return boolean result if init was successful.
     */
    virtual bool init(const std::vector<Point> &allData) = 0;

    /**
     * normalize oldPoint to newPoint after init is successful.
     * @param oldPoint Point to be normalized
     * @param newPoint Point to hold the normalized value
     */
    virtual void normalize(const Point &oldPoint, Point &newPoint) = 0;
};


#endif //LAB7_NORMALIZER_H