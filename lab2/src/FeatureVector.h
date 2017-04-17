//
// Created by odedlaz on 4/17/17.
//

#ifndef LAB2_FEATUREVECTOR_H
#define LAB2_FEATUREVECTOR_H


#include <vector>
#include <string>

class FeatureVector {
private:
    std::string _name;
    std::vector<double> _features;
public:
    FeatureVector(std::string name);
    FeatureVector(std::string name, std::vector<double> &features);

    void Add(double feature);
    const std::string &GetName() const;
};


#endif //LAB2_FEATUREVECTOR_H
