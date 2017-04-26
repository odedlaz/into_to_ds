#ifndef LAB5_SILHOUETTECOEFF_H
#define LAB5_SILHOUETTECOEFF_H

#include "EvaluationMeasure.h"

class SilhouetteCoeff : public EvaluationMeasure {

public:
    SilhouetteCoeff(const std::vector<Cluster> &clusters, size_t pointsDimension) : EvaluationMeasure(clusters,
                                                                                                      pointsDimension) {}

    double calculate(const Point &point) const;

    double calculate(const Cluster &cluster) const;

    double calculate() const;

private:

    double getMinimalDistance(std::vector<Cluster>::size_type ignoredClusterID, const Point &point) const;
};


#endif //LAB5_SILHOUETTECOEFF_H
