#ifndef LAB5_EVALUATIONMEASURE_H
#define LAB5_EVALUATIONMEASURE_H

#include <vector>
#include "Cluster.h"

class EvaluationMeasure {

protected:
    const std::vector<Cluster> &_clusters;
    size_t _pointsDimension;

    bool findClusterIDForPoint(const Point &point, std::vector<Cluster>::size_type &index) const;

    Point getOverallCenter() const;

public:
    EvaluationMeasure(const std::vector<Cluster> &clusters, size_t pointsDimension) : _clusters(clusters),
                                                                                      _pointsDimension(
                                                                                              pointsDimension) {}

};


#endif //LAB5_EVALUATIONMEASURE_H
