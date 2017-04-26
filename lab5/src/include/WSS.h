#ifndef LAB5_WSS_H
#define LAB5_WSS_H


#include "EvaluationMeasure.h"

class WSS : public EvaluationMeasure {
public:
    WSS(const std::vector<Cluster> &clusters, size_t pointsDimension) : EvaluationMeasure(clusters, pointsDimension) {}

    double calculate(const Cluster &cluster) const;

    double calculate() const;
};


#endif //LAB5_WSS_H
