#include "include/TSS.h"

double TSS::calculate() const {

    Point overallCentroid(getOverallCenter());
    double tss(0.0);

    std::vector<Cluster>::const_iterator iter;
    for (iter = _clusters.begin(); iter != _clusters.end(); ++iter) {
        const Cluster & cluster = *iter;
        tss += cluster.sumSquaresPointToCluster(overallCentroid);
    }

    return tss;

}
