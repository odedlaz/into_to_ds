//
// Created by odedlaz on 6/6/17.
//

#ifndef SRC_EUCLIDEANDISTANCE_H
#define SRC_EUCLIDEANDISTANCE_H


#include "Distance.h"


class EuclideanDistance : public Distance {
public:
    /**
     * calculates Euclidean distance between two points
     * @param p1 const Point
     * @param p2 const Point
     * @return double value of the euclidean distance between p1 & p2.
     */
    virtual double calculate(const Point &p1, const Point &p2) const;
};


#endif //SRC_EUCLIDEANDISTANCE_H
