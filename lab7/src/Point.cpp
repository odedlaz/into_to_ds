#include "include/Point.h"
#include <iostream>

Point Point::operator-(const Point &otherPoint) const {
    Point outcome(getDimension());
    for (size_t i = 0; i < getDimension(); i++) {
        outcome[i] = _values[i] - otherPoint[i];
    }
    outcome._class = _class;
    return outcome;
}

Point Point::operator/(const Point &otherPoint) const {
    Point outcome(getDimension());
    for (size_t i = 0; i < getDimension(); i++) {
        outcome[i] = _values[i] / otherPoint[i];
    }
    outcome._class = _class;
    return outcome;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    for (size_t i = 0; i < point.getDimension(); i++) {
        os << point[i] << ',';
    }
    os << point.getClass();
    return os;
}
