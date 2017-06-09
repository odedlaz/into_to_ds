//
// Created by odedlaz on 6/6/17.
//

#ifndef SRC_MANHATTENDISTANCE_H
#define SRC_MANHATTENDISTANCE_H


#include "Distance.h"

/**
 * calculates Manhattan Distance between two points
 * @param p1 cont Point
 * @param p2 cont Point
 * @return double value of the Manhattan ditance between p1 & p2.
 */
class ManhattanDistance : public Distance {
public:
    virtual double calculate(const Point &p1, const Point &p2) const;
};


#endif //SRC_MANHATTENDISTANCE_H
