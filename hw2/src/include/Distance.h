//
// Created by odedlaz on 6/6/17.
//

#ifndef SRC_DISTANCE_H
#define SRC_DISTANCE_H


#include "Point.h"

class Distance {
public:
    /**
     * Calculates distance between two points using a given method.
     * @param p1 Point
     * @param p2 Point
     * @return dobule value of the distance from given method.
     */
    virtual double calculate(const Point &p1, const Point &p2) const =0;
};


#endif //SRC_DISTANCE_H
