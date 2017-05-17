#ifndef LAB7_NORMALIZER_H
#define LAB7_NORMALIZER_H

#include <vector>
#include "Point.h"




class Normalizer {
public:
    virtual bool init(const std::vector<Point> &allData) = 0;
    virtual void normalize(const Point &oldPoint, Point &newPoint) = 0;
};


#endif //LAB7_NORMALIZER_H