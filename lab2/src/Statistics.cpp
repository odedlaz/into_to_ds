#include "include/Statistics.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using std::vector;

double statistics::median(const vector<double> &xv) {
    //we create temporal copy of the given constant vector
    vector<double> dv_cpy;
    copy(xv.begin(), xv.end(), back_inserter(dv_cpy));
    //we sort it to find the getMedian
    sort(dv_cpy.begin(), dv_cpy.end());
    double medX(0.0);
    size_t center = dv_cpy.size() / 2;
    if (dv_cpy.size() % 2 == 0) {
        medX = (dv_cpy[center] + dv_cpy[center + 1]) / 2.0;
    } else {
        medX = dv_cpy[center + 1];
    }
    return medX;
}

double statistics::mean(const std::vector<double> &xv) {
    double sum = 0;

    vector<double>::const_iterator iter = xv.begin();

    for (iter; iter != xv.end(); ++iter) {
        sum += *iter;
    }
    return sum / xv.size();
}

double statistics::variance(const std::vector<double> &xv) {
    double meanX = mean(xv);
    double sum = 0;

    vector<double>::const_iterator iter = xv.begin();
    for (iter; iter != xv.end(); ++iter) {
        sum += pow(*iter - meanX, 2);
    }

    return sum / xv.size();
}

double statistics::standardDeviation(const std::vector<double> &xv) {
    return sqrt(variance(xv));
}

double statistics::covariance(const std::vector<double> &xv, const std::vector<double> &yv) {
    double meanX = mean(xv);
    double meanY = mean(yv);
    double cov = 0;

    // splitting initialization for better readability
    vector<double>::const_iterator iterY = yv.begin();
    vector<double>::const_iterator iterX = xv.begin();

    for (iterX, iterY; iterX != xv.end(); ++iterX, ++iterY) {
        cov += (*iterX - meanX) * (*iterY - meanY);
    }

    return cov / xv.size();
}

double statistics::correlation(const std::vector<double> &xv, const std::vector<double> &yv) {
    return covariance(xv, yv) / (standardDeviation(xv) * standardDeviation(yv));
}

