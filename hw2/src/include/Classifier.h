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
    /**
     * Trains the given classifier using a Training set using the Classifier's method
     * @param points Vector<Points> of training set
     * @return boolean result that indicates if the train was successful.
     */
    virtual bool train(const std::vector<Point> &points)=0;

    /**
     * Predicts the class of given Point using the Classifier's method
     * @param newPoint Point that it's class will be predicted and assigned to.
     */
    virtual void predict(Point &newPoint) const =0;

    /**
     * Calculates the accuracy of a classifier using a classified set
     * compare the given Class to the predicted class
     * @param subset vector<Point> of points with assigned class
     * @return double value of correct predictions in ratio to subset.size()
     */
    double accuracy(const std::vector<Point> &subset) const;

    /**
     * prints the each point and it's given class against it's predicted class
     * @param subset vector<Point> of points with assigned class
     */
    void printResults(const std::vector<Point> &subset) const;

    virtual ~Classifier() {}

};


#endif //CLASSIFICATION_CLASSIFIER_H
