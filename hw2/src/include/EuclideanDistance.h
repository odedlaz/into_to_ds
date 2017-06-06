//
// Created by odedlaz on 6/6/17.
//

#ifndef SRC_EUCLIDEANDISTANCE_H
#define SRC_EUCLIDEANDISTANCE_H


#include "Distance.h"

class EuclideanDistance : public Distance {
public:
    virtual double calculate(const Point &p1, const Point &p2) const;
};


#endif //SRC_EUCLIDEANDISTANCE_H
