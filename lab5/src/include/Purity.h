#ifndef LAB5_PURITY_H
#define LAB5_PURITY_H


#include "EvaluationMeasure.h"

class Purity : public EvaluationMeasure {
public:
    Purity(const std::vector<Cluster> &clusters, size_t pointsDimension) : EvaluationMeasure(clusters,
                                                                                             pointsDimension) {}

    double calculate() const;

};


#endif //LAB5_PURITY_H
