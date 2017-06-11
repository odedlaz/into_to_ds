#ifndef SRC_COSINEDISTANCE_H
#define SRC_COSINEDISTANCE_H


#include "Distance.h"

class CosineDistance : public Distance {
public:

    /**
     * calculates cosine similarity between two points
     * @param p1 const Point
     * @param p2 const Point
     * @return the cosine difference
     */
    virtual double calculate(const Point &p1, const Point &p2) const;

private:

    /**
     * calculates dot product between two points
     * @param p1 const Point
     * @param p2 const Point
     * @return double the dot product between the point vectors
     */
    double dotProduct(const Point &p1, const Point &p2) const;

    /*
     * calculates the magnitude of a point vector
     * @param p const Point
     * @return double the calculated magnitude of the point
     */
    double magnitude(const Point &p) const;
};


#endif //SRC_COSINEDISTANCE_H
