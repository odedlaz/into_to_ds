//
// Created by annabel@staff.technion.ac.il on 5/3/17.
//

#ifndef CLASSIFICATION_KNNCLASSIFIER_H
#define CLASSIFICATION_KNNCLASSIFIER_H

#include "Classifier.h"
#include "Distance.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class KNNClassifier : public Classifier {
    Distance *_distance;
    size_t _size;
    std::vector<Point> _data;


public:
    KNNClassifier(size_t &size, Distance *&distance);

    virtual bool train(const std::vector<Point> &points);

    virtual void predict(Point &newPoint) const;

    size_t maxDistIndex(const std::vector<std::pair<std::string, double> > &distances, double &max) const;

    const std::string getMajorityClass(const std::vector<std::pair<std::string, double> > &distances) const;
};

#endif //CLASSIFICATION_KNNCLASSIFIER_H

