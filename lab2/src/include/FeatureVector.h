#ifndef LAB2_FEATUREVECTOR_H
#define LAB2_FEATUREVECTOR_H


#include <vector>
#include <string>


/**
 * FeatureVector
 * Handles the data from a given dataset.
 * keeps the feature name, and vector of data(double).
 */
class FeatureVector {
private:
    std::string _name;
    std::vector<double> _features;
public:
    FeatureVector() : _name("n/a") {};

    FeatureVector(std::string name);

    FeatureVector(std::string name, std::vector<double> &features);

    void append(double feature);

    const std::string &getName() const;

    int length();

    double getMedian() const;

    double getMean() const;

    double getVariance() const;

    double getStandardDeviation() const;

    double getCovariance(const FeatureVector &otherV) const;

    double getCorrelation(const FeatureVector &otherV) const;


};


#endif //LAB2_FEATUREVECTOR_H
