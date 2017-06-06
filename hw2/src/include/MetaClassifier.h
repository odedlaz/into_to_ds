//
// Created by odedlaz on 6/6/17.
//

#ifndef SRC_METACLASSIFER_H
#define SRC_METACLASSIFER_H


#include "Classifier.h"

class MetaClassifier : public Classifier {
public:
    virtual bool train(const std::vector<Point> &points);

    virtual void predict(Point &newPoint) const;
};


#endif //SRC_METACLASSIFER_H
