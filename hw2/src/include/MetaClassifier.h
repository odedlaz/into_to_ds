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
    MetaClassifier(size_t k, const std::vector<Point> &allData, Distance *&distance);

    virtual bool train(const std::vector<Point> &points);

    virtual void predict(Point &newPoint) const;

    virtual ~MetaClassifier();


private:
    Perceptron *_perceptron;
    KNNClassifier *_knn;
    size_t _k;
    std::vector<Point> _data;
    std::vector<Point>* _training;
    Distance *_distance;
    std::vector<std::pair<int, double> > _weights;

    void setPointAccordingToWeights(const Point &point, Point &newPoint) const;
};


#endif //SRC_METACLASSIFER_H
