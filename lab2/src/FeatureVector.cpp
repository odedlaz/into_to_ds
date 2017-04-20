#include <iostream>
#include "include/FeatureVector.h"
#include "include/Statistics.h"

/**
 * Constructor
 * construct a FeatureVector using Feature Name only.
 * @param name string the name of the Feature Vector
 */
FeatureVector::FeatureVector(std::string name) : _name(name), _features() {
}

/**
 * Constructor
 * construct a FeatureVector using name and vector of data.
 * @param name string the name of the Feature Vector
 * @param features vector<double> the vector holding the data for the feature.
 */
FeatureVector::FeatureVector(std::string name, std::vector<double> &features) :
        _name(name), _features(features) {
}

void FeatureVector::append(double feature) {
    _features.push_back(feature);
}

const std::string &FeatureVector::getName() const {
    return _name;
}

double FeatureVector::getMedian() const {
    return statistics::median(_features);
}

double FeatureVector::getMean() const {
    return statistics::mean(_features);

}

double FeatureVector::getVariance() const {
    return statistics::variance(_features);
}

double FeatureVector::getStandardDeviation() const {
    return statistics::standardDeviation(_features);
}

double FeatureVector::getCovariance(const FeatureVector &otherV) const {
    return statistics::covariance(_features, otherV._features);
}

double FeatureVector::getCorrelation(const FeatureVector &otherV) const {
    return statistics::correlation(_features, otherV._features);
}

int FeatureVector::length() {
    return _features.size();
}