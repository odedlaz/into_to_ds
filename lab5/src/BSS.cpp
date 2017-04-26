#include "include/BSS.h"

double BSS::calculate() const {

    Point overallCentroid(getOverallCenter());
    double bss(0.0);

    std::vector<Cluster>::const_iterator iter;
    for (iter = _clusters.begin(); iter != _clusters.end(); ++iter) {
        const Cluster &cluster = (*iter);
        Point clusterCentroid = cluster.getCenterPoint();
        double distance = clusterCentroid.squaredDistance(overallCentroid);
        bss += distance * cluster.getSize();
    }

    return bss;
}
