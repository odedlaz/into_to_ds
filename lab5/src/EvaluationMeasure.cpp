#include "include/EvaluationMeasure.h"

using std::vector;

bool EvaluationMeasure::findClusterIDForPoint(const Point &point, vector<Cluster>::size_type &index) const {
    for (vector<Cluster>::size_type sz = 0; sz != _clusters.size(); sz++) {
        if (_clusters[sz].isInCluster(point)) {
            index = sz;
            return true;
        }
    }
    return false;
}

Point EvaluationMeasure::getOverallCenter() const {
    Point avg(_pointsDimension);
    double count(0.0);
    for (vector<Cluster>::size_type sz = 0; sz != _clusters.size(); sz++) {
        for (size_t i = 0; i < _clusters[sz].getSize(); i++) {
            avg = avg + _clusters[sz][i];
            count++;
        }
    }
    avg /= count;
    return avg;
}