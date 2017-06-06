//
// Created by annabel@staff.technion.ac.il on 5/3/17.
//

#ifndef CLASSIFICATION_CLASSIFIER_H
#define CLASSIFICATION_CLASSIFIER_H

#include <vector>
#include <string>


class Point;

class Classifier {

public:
    virtual bool train(const std::vector<Point> &points)=0;

    //The predicted class will be filled inside the point
    virtual void predict(Point &newPoint) const =0;

    double accuracy(const std::vector<Point> &subset) const;

    void printResults(const std::vector<Point> &subset) const;

    virtual ~Classifier() {}

};


#endif //CLASSIFICATION_CLASSIFIER_H
