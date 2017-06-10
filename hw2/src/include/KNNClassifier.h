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

    /**
     * Trains the KNN using a Training set. (sets the training set as _data)
     * @param points Vector<Points> of training set
     * @return boolean result that indicates if the train was successful.
     */
    virtual bool train(const std::vector<Point> &points);

    /**
     * Predicts the class of given Point.
     * find the K nearest points, and assign the majority class of these as the predicted class.
     * @param newPoint Point that it's class will be predicted and assigned to.
     */
    virtual void predict(Point &newPoint) const;

    /**
     * Find the Max distance of vector of class and distances, and return it's index & update max value
     * @param distances vector<pair<class, distance>> to find the max distance within
     * @param max double reference to be updated with the max value
     * @return size_t index of the max value inside the vector.
     */
    size_t maxDistIndex(const std::vector<std::pair<std::string, double> > &distances, double &max) const;

    /**
     * get the majority class from a set
     * creates a Unique set of classes, count the amount of appereance. return the highest count
     * @param distances vector<pair<string, double>> pairs of (class (string) and distance (double))
     * @return string of most common class.
     */
    const std::string getMajorityClass(const std::vector<std::pair<std::string, double> > &distances) const;
};

#endif //CLASSIFICATION_KNNCLASSIFIER_H

