//
// Created by shraga89@st.technion.ac.il on 3/16/17.
//

#include "include/Statistics.h"
#include <algorithm>
#include <iostream>
#include <math.h>

double Mean(const std::vector<double>& xv)
{

    double sum = 0;
    std::vector<double>::const_iterator it;
    for (it = xv.begin(); it != xv.end(); ++it) {
        sum += *it;
    }
    return sum / xv.size();
}

double Variance(const std::vector<double>& xv)
{
    double sum = 0;
    double mean = Mean(xv);

    for (auto it = xv.begin(); it != xv.end(); ++it) {
        sum += pow(*it - mean, 2);
    }

    return sum / (xv.size() - 1);
}

double Median(const std::vector<double>& xv)
{
    // we create temporal copy of the given constant std::vector
    std::vector<double> dv_cpy;
    copy(xv.begin(), xv.end(), back_inserter(dv_cpy));
    // we sort it to find the median
    sort(dv_cpy.begin(), dv_cpy.end());
    double median(0.0);
    size_t center = dv_cpy.size() / 2;
    if (dv_cpy.size() % 2 == 0) {
	median = (dv_cpy[center] + dv_cpy[center + 1]) / 2.0;
    } else {
	median = dv_cpy[center + 1];
    }
    return median;
}
