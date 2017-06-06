//
// Created by annabel@staff.technion.ac.il on 5/3/17.
//

#ifndef CLASSIFICATION_KNNCLASSIFIER_H
#define CLASSIFICATION_KNNCLASSIFIER_H

#include "Classifier.h"
#include "Distance.h"

class KNNClassifier : public Classifier {
    Distance *_distance;
    size_t _size;


public:
    KNNClassifier(size_t &size, Distance *&distance);

    virtual bool train(const std::vector<Point> &points);

    virtual void predict(Point &newPoint) const;
};

#endif //CLASSIFICATION_KNNCLASSIFIER_H
