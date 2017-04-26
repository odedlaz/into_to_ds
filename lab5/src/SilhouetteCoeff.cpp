#include <limits>
#include "include/SilhouetteCoeff.h"

using std::vector;


double SilhouetteCoeff::getMinimalDistance(std::vector<Cluster>::size_type ignoredClusterID, const Point &point) const {
    double min = std::numeric_limits<double>::max();
    for (std::vector<Cluster>::const_iterator cit = _clusters.begin(); cit != _clusters.end(); cit++) {
        if (cit->getID() != ignoredClusterID) {
            double sdist = cit->avgEuclideanPointToCluster(point);
            if (sdist < min) min = sdist;
        }
    }
    return min;
}

double SilhouetteCoeff::calculate(const Point &point) const {
    vector<Cluster>::size_type clusterID(0);
    if (!findClusterIDForPoint(point, clusterID)) return 0.0;
    double in = _clusters[clusterID].avgEuclideanPointToCluster(point);
    double out = getMinimalDistance(clusterID, point);
    double max = in < out ? out : in;
    return (out - in) / max;
}

double SilhouetteCoeff::calculate(const Cluster &cluster) const {
    double avg(0.0);
    for (size_t i = 0; i < cluster.getSize(); i++) {
        avg += calculate(cluster[i]);
    }
    return avg / cluster.getSize();

}

double SilhouetteCoeff::calculate() const {
    double avg(0.0);
    for (std::vector<Cluster>::const_iterator cit = _clusters.begin(); cit != _clusters.end(); cit++) {
        avg += calculate(*cit);
    }
    return avg / _clusters.size();
}