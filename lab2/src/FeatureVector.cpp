//
// Created by odedlaz on 4/17/17.
//

#include "FeatureVector.h"

FeatureVector::FeatureVector(std::string name) : _name(name) {
    _features = std::vector<double>();

}

FeatureVector::FeatureVector(std::string name, std::vector<double> &features) :
        _name(name), _features(features) {
}

void FeatureVector::Add(double feature) {
    _features.push_back(feature);
}

const std::string &FeatureVector::GetName() const {
    return _name;
}

