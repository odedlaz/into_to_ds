#include "include/TSS.h"

double TSS::calculate() const {

    Point overallCentroid(getOverallCenter());
    double tss(0.0);
    std::vector<Cluster>::const_iterator cIter;
    for (cIter = _clusters.begin(); cIter != _clusters.end(); ++cIter) {
        tss += (*cIter).sumSquaresPointToCluster(overallCentroid);
    }

    return tss;

}
