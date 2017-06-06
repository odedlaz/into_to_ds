//
// Created by annabel@staff.technion.ac.il on 5/5/17.
//

#ifndef CLASSIFICATION_PERCEPTRON_H
#define CLASSIFICATION_PERCEPTRON_H


#include "Classifier.h"

class Perceptron: public Classifier {

public:

    Perceptron(size_t dimension, double alpha, size_t epoch):_inputCount(dimension+1),
                                                              _ptrWeights(NULL),
                                                              _alpha(alpha),
                                                              _epoch(epoch){}
    void init();
    virtual ~Perceptron();
    virtual bool train(const std::vector<Point>& points);
    virtual void predict( Point& newPoint) const;
    void printWeights() const;

private:
    double calculateIn(const Point& point) const;
    void updateWeights(const Point& point);
    void release();
    void mapClasses(const std::vector<Point>& points);
    bool findClass(const std::string& classname) const;
    double squaredError(const std::vector<Point>& points) const;
    double getClassID(const Point& ptrPoint) const;
    void initWeights();
    static double specialInput;

private:
    size_t _inputCount;
    double* _ptrWeights;
    double  _alpha;
    size_t _epoch;
    std::vector<std::string> _classes;

};


#endif //CLASSIFICATION_PERCEPTRON_H
