#include <cstddef>
#include "include/MetaClassifier.h"
#include <numeric>
#include <math.h>
#include <algorithm>


using std::string;
using std::vector;

const int REMOVE_LOWEST = 20;

size_t numOfLowest(size_t size) {

    return (size_t) ceil(REMOVE_LOWEST / 100.0 * size);
}

bool compareWeights(std::pair<int, double> x, std::pair<int, double> y) {
    return fabs(x.second) > fabs(y.second);
}

bool compareIndex(std::pair<int, double> x, std::pair<int, double> y) {
    return x.first < y.first;
}

bool MetaClassifier::train(const std::vector<Point> &points) {
    double result = _perceptron->train(points);

    if (!result) {
        return false;
    }

    // add all the weights
    for (int i = 0; i < _perceptron->_inputCount; i++) {
        _weights.push_back(std::pair<int, double>(i, _perceptron->_ptrWeights[i]));
    }

    // sort them by the weights (highest is the "heaviest", ignores w0)
    std::sort(_weights.begin()+1, _weights.end(), compareWeights);


    // remove the "lightest" weights
    for (int i = 0; i < numOfLowest(_weights.size()); i++) {
        _weights.erase(_weights.end() - 1);
    }

    // sort the weights according to their index
    std::sort(_weights.begin(), _weights.end(), compareIndex);


    // create a new training set with the new points
    for (int i = 0; i < points.size(); i++) {
        Point p(points[i].getDimension() - numOfLowest(_weights.size()));
        setPointAccordingToWeights(points[i], p);
        _training.push_back(p);
    }

    // train the knn
    return _knn->train(_training);
}


void MetaClassifier::setPointAccordingToWeights(const Point &point, Point &newPoint) const {
    vector<double> v = vector<double>();
    vector<std::pair<int, double> >::const_iterator it;

    for (it = _weights.begin(); it != _weights.end(); it++) {
        int idx = (*it).first;

        // the first weight has a "-1" point which is not real ;)
        if (idx == 0) {
            continue;
        }

        v.push_back(point[idx - 1]);
    }

    newPoint.setValues(v);
    newPoint.setPrediction(point.getPrediction());
    newPoint.setClass(point.getClass());
}

void MetaClassifier::predict(Point &newPoint) const {
    Point point(newPoint.getDimension() - numOfLowest(_weights.size()));
    setPointAccordingToWeights(newPoint, point);

    // predict on the new point according to perceptron weights
    _knn->predict(point);

    // update class and prediction of the "old" point
    newPoint.setClass(point.getClass());
    newPoint.setPrediction(point.getPrediction());
}

MetaClassifier::~MetaClassifier() {
    // cleanup
    delete _knn;
    delete _perceptron;
}

MetaClassifier::MetaClassifier(size_t k, size_t size, Distance *&distance) : _k(k),
                                                                             _size(size),
                                                                             _distance(distance) {
    _perceptron = new Perceptron(size, 0.0001, 5000);
    _perceptron->init();

    _knn = new KNNClassifier(k, _distance);
    _training = vector<Point>();
}
