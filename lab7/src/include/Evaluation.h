#ifndef LAB6_EVALUATION_H
#define LAB6_EVALUATION_H


#include "KNN.h"
#include "Point.h"

class Evaluation {

public:
    Evaluation(KNN &knn) : _knn(knn) {}

    //returns accuracy
    double crossValidation(std::vector<Point> &data, size_t folds);

private:

    void splitData(const std::vector<Point> &data,
                   size_t testFoldStart,
                   size_t testFoldEnd,
                   std::vector<Point> &trainingSet,
                   std::vector<Point> &testingSet);

    void test(std::vector<Point> &testingSet);


private:
    KNN &_knn;

};


#endif //LAB6_EVALUATION_H
