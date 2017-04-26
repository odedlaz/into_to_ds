#ifndef LAB5_BSS_H
#define LAB5_BSS_H


#include "EvaluationMeasure.h"

class BSS : public EvaluationMeasure {
public:
    BSS(const std::vector<Cluster> &clusters, size_t pointsDimension) : EvaluationMeasure(clusters, pointsDimension) {}

    double calculate() const;
};


#endif //LAB5_BSS_H
