#include "include/BSS.h"

double BSS::calculate() const {

    Point overallCentroid(getOverallCenter());
    std::vector<Cluster>::const_iterator iter;
    double bss(0.0);
    for (iter = _clusters.begin(); iter != _clusters.end(); ++iter) {
        Point clusterCentroid = (*iter).getCenterPoint();
        double dist = clusterCentroid.squaredDistance(overallCentroid);
        bss += dist * (*iter).getSize();
    }

    return bss;
}
