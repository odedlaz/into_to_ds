//
// Created by annabel@staff.technion.ac.il on 5/5/17.
//

#ifndef CLASSIFICATION_PERCEPTRON_H
#define CLASSIFICATION_PERCEPTRON_H


#include "Classifier.h"

class Perceptron : public Classifier {
    friend class MetaClassifier;
public:

    Perceptron(size_t dimension, double alpha, size_t epoch) : _inputCount(dimension + 1),
                                                               _ptrWeights(NULL),
                                                               _alpha(alpha),
                                                               _epoch(epoch) {}

    void init();

    virtual ~Perceptron();

    /**
     * Trains the Perceptron using a Training set
     * @param points Vector<Points> of training set
     * @return boolean result that indicates if the train was successful.
     */
    virtual bool train(const std::vector<Point> &points);

    /**
     * Predicts the class of given Point.
     * finds a linear function(set of weights) that the SE will converge at.
     * @param newPoint Point that it's class will be predicted and assigned to.
     */
    virtual void predict(Point &newPoint) const;

    /**
     * Prints the Weights of perceptron instance.
     */
    void printWeights() const;

private:
    /**
     * calculates the In value(sum of features affected by their weights)
     * to be used in activation function
     * @param point Point to calculates its In value.
     * @return double of In value.
     */
    double calculateIn(const Point &point) const;

    /**
     * updates the Weight vector using the perceptron update rule.
     * @param point Point to update the weights correspondingly.
     */
    void updateWeights(const Point &point);

    /**
     * Releases the Weight vector from memory
     */
    void release();

    /**
     * Initializes the _classes vector with the given set
     * @param points vector<Point> that contains the set.
     */
    void mapClasses(const std::vector<Point> &points);

    /**
     * Checks if a class is already assigned to _classes
     * @param classname string represent the class name
     * @return boolean result, true if found the class in _classes
     */
    bool findClass(const std::string &classname) const;

    /**
     * Calculates the SE for a set of points.
     * @param points vector<Point> contains the set
     * @return double value represents the SE.
     */
    double squaredError(const std::vector<Point> &points) const;

    /**
     * Gets the coded value of class (-1 or 1) of a point.
     * @param ptrPoint Point reference (saves space)
     * @return double coded value of class.
     */
    double getClassID(const Point &ptrPoint) const;

    /**
     * Initializing Weights vector with random values.
     */
    void initWeights();

    static double specialInput;

private:
    size_t _inputCount;
    double *_ptrWeights;
    double _alpha;
    size_t _epoch;
    std::vector<std::string> _classes;

};


#endif //CLASSIFICATION_PERCEPTRON_H
