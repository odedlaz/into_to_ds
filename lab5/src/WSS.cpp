#include "include/WSS.h"

double WSS::calculate(const Cluster &cluster) const {
    return cluster.sumSquaresPointToCluster(cluster.getCenterPoint());
}

double WSS::calculate() const {
    double wss(0.0);

    std::vector<Cluster>::const_iterator it;
    for (it = _clusters.begin(); it != _clusters.end(); ++it) {
        const Cluster &cluster = *it;
        wss += calculate(cluster);
    }
    return wss;
}
