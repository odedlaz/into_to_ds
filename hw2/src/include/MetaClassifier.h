//
// Created by odedlaz on 6/6/17.
//

#ifndef SRC_METACLASSIFER_H
#define SRC_METACLASSIFER_H


#include "Classifier.h"
#include "Perceptron.h"
#include "KNNClassifier.h"

class MetaClassifier : public Classifier {
    friend class Perceptron;

public:
    MetaClassifier(size_t k, size_t size, Distance *&distance);

    virtual bool train(const std::vector<Point> &points);

    virtual void predict(Point &newPoint) const;

    virtual ~MetaClassifier();


private:
    Perceptron *_perceptron;
    KNNClassifier *_knn;
    size_t _k;
    size_t _size;
    std::vector<Point> _training;
    Distance *_distance;
    std::vector<std::pair<int, double> > _weights;

    void setPointAccordingToWeights(const Point &point, Point &newPoint) const;
};


#endif //SRC_METACLASSIFER_H
