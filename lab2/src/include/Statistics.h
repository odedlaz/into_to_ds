#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <cstdlib>
#include <vector>

namespace statistics {

    double median(const std::vector<double> &xv);

    double mean(const std::vector<double> &xv);

    double variance(const std::vector<double> &xv);

    double standardDeviation(const std::vector<double> &xv);

    double covariance(const std::vector<double> &xv, const std::vector<double> &yv);

    double correlation(const std::vector<double> &xv, const std::vector<double> &yv);

}
#endif//