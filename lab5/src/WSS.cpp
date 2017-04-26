#include "include/WSS.h"

double WSS::calculate(const Cluster &cluster) const {
    return cluster.sumSquaresPointToCluster(cluster.getCenterPoint());
}

double WSS::calculate() const {
    std::vector<Cluster>::const_iterator it;

    double sumAll(0.0);
    for (it = _clusters.begin(); it != _clusters.end(); ++it) {
        sumAll += calculate(*it);
    }
    return sumAll;
}
