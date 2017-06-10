//
// Created by odedlaz on 6/10/17.
//

#ifndef SRC_COSINEDISTANCE_H
#define SRC_COSINEDISTANCE_H


#include "Distance.h"

class CosineDistance : public Distance {
public:
    virtual double calculate(const Point &p1, const Point &p2) const;
private:
    double dotProduct(const Point &p1, const Point &p2) const;

    double magnitude(const Point &p) const;
};


#endif //SRC_COSINEDISTANCE_H
