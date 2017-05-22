#include "include/Point.h"
#include <iostream>

Point Point::operator-(const Point &otherPoint) const {
    size_t dimension = getDimension();

    Point outcome(dimension);
    for (size_t i = 0; i < dimension; i++) {
        outcome[i] = _values[i] - otherPoint[i];
    }

    outcome._class = _class;
    return outcome;
}

Point Point::operator/(const Point &otherPoint) const {
    size_t dimension = getDimension();

    Point outcome(dimension);
    for (size_t i = 0; i < dimension; i++) {
        outcome[i] = _values[i] / otherPoint[i];
    }

    outcome._class = _class;
    return outcome;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    size_t dimension = point.getDimension();
    for (size_t i = 0; i < dimension; i++) {
        os << point[i] << ',';
    }
    os << point.getClass();
    return os;
}

Point::Point(const Point &otherPoint) : _values(otherPoint._values),
                                        _class(otherPoint._class),
                                        _prediction(otherPoint._prediction) {
}
