﻿#include "include/Statistics.h"
#include <iostream>
#include <algorithm>
#include <cmath>

using std::vector;

/**
 * Median
 * calculates the median of given vector.
 * @param xv Type vector<double>
 * @return double result of median
 */
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

/**
 * Mean
 * calculates the mean of given vector
 * @param xv Type vector<double>
 * @return double result of mean
 */
double statistics::mean(const std::vector<double> &xv) {
    double sum = 0;

    vector<double>::const_iterator iter = xv.begin();

    for (iter; iter != xv.end(); ++iter) {
        sum += *iter;
    }
    return sum / xv.size();
}

/**
 * Variance
 * calculates the variance of given vector
 * @param xv vector<double>
 * @return double result of variance
 */
double statistics::variance(const std::vector<double> &xv) {
    double meanX = mean(xv);
    double sum = 0;

    vector<double>::const_iterator iter = xv.begin();
    for (iter; iter != xv.end(); ++iter) {
        sum += pow(*iter - meanX, 2);
    }

    return sum / xv.size();
}

/**
 * Standard Deviation
 * calculates the standard deviation of given vector
 * @param xv vector<double>
 * @return double result of Standard Deviation
 */
double statistics::standardDeviation(const std::vector<double> &xv) {
    return sqrt(variance(xv));
}

/**
 * Covariance
 * calculates the covariance between two vectors
 * @param xv vector<double>
 * @param yv vector<double>
 * @return double result of covariance
 */
double statistics::covariance(const std::vector<double> &xv, const std::vector<double> &yv) {
    double meanX = mean(xv);
    double meanY = mean(yv);
    double sum = 0;

    // splitting initialization for better readability
    vector<double>::const_iterator iterY = yv.begin();
    vector<double>::const_iterator iterX = xv.begin();

    for (iterX, iterY; iterX != xv.end(); ++iterX, ++iterY) {
        sum += (*iterX - meanX) * (*iterY - meanY);
    }

    return sum / xv.size();
}
/**
 * Correlation
 * calculates the correlation between two vectors
 * @param xv vector<double>
 * @param yv vector<double>
 * @return double result of correlation
 */
double statistics::correlation(const std::vector<double> &xv, const std::vector<double> &yv) {
    return covariance(xv, yv) / (standardDeviation(xv) * standardDeviation(yv));
}

