//
// Created by annabel@staff.technion.ac.il on 4/24/17.
//

#ifndef LAB5_TSS_H
#define LAB5_TSS_H

#include "EvaluationMeasure.h"

class TSS : public EvaluationMeasure {
public:
    TSS(const std::vector<Cluster>& clusters, size_t pointsDimension):EvaluationMeasure(clusters,pointsDimension){}
    double calculate() const;
};


#endif //LAB5_TSS_H
