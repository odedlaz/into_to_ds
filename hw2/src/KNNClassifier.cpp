#include <cstddef>
#include "include/KNNClassifier.h"
#include "include/Distance.h"

//
// Created by annabel@staff.technion.ac.il on 5/3/17.
//
KNNClassifier::KNNClassifier(size_t &size, Distance *&distance) : _size(size), _distance(distance) {

}

bool KNNClassifier::train(const std::vector<Point> &points) {
    return false;
}

void KNNClassifier::predict(Point &newPoint) const {

}

