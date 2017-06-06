//
// Created by odedlaz on 6/6/17.
//

#ifndef SRC_DISTANCE_H
#define SRC_DISTANCE_H


#include "Point.h"

class Distance {
public:
    virtual double calculate(const Point &p1, const Point &p2) const =0;
};


#endif //SRC_DISTANCE_H
