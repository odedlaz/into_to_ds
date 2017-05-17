//
// Created by shraga89@st.technion.ac.il on 5/11/17.
//

#ifndef LAB7_ZNORMALIZER_H
#define LAB7_ZNORMALIZER_H

#include "Normalizer.h"

class ZNormalizer:public Normalizer{
private:
    Point mean;
    Point sd;
public:
    ZNormalizer(size_t dimension):mean(dimension),sd(dimension){}
    bool init(const std::vector<Point>& points);
    void normalize(const Point &oldPoint, Point &newPoint);
};


#endif //LAB7_ZNORMALIZER_H
