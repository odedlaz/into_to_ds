#include "include/EvaluationMeasures.h"


double EvaluationMeasures::accuracy(const std::vector <Point> &data) {
    double correct(0.0);
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].getClass() == data[i].getPrediction())
            correct++;
    }
    return correct / (double) data.size();

}