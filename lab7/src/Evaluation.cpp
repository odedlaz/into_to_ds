#include "include/Evaluation.h"
#include <algorithm>
#include "include/EvaluationMeasures.h"


using std::vector;
using std::cout;
using std::endl;

void Evaluation::splitData(const std::vector<Point> &data,
                           size_t testFoldStart,
                           size_t testFoldEnd,
                           std::vector<Point> &trainingSet,
                           std::vector<Point> &testingSet) {
    size_t dimension = data[0].getDimension();
    testingSet.resize(testFoldEnd - testFoldStart, Point(dimension));
    trainingSet.resize(data.size() - testingSet.size(), Point(dimension));
    std::copy(data.begin() + testFoldStart, data.begin() + testFoldEnd, testingSet.begin());
    std::copy(data.begin(), data.begin() + testFoldStart, trainingSet.begin());
    std::copy(data.begin() + testFoldEnd, data.end(), trainingSet.begin() + testFoldStart);
}

void Evaluation::test(std::vector<Point> &testingSet) {
    for (std::vector<Point>::size_type sz = 0; sz < testingSet.size(); sz++) {
        _knn.predict(testingSet[sz]);
    }
}

double Evaluation::crossValidation(std::vector<Point> &data, size_t folds) {
    if (data.size() == 0)
        return 0;
    std::random_shuffle(data.begin(), data.end());
    size_t foldSize = data.size() / folds;
    double totalAccuracy(0.0);
    //we are handling all folds besides the last one
    for (size_t id = 0; id < folds; id++) {
        _knn.reset();
        std::vector<Point> training;
        std::vector<Point> testing;
        if (id != (folds - 1))
            splitData(data, id * foldSize, id * foldSize + foldSize, training, testing);
        else
            splitData(data, id * foldSize, data.size(), training, testing);

        if (!_knn.train(training))
            return 0;
        test(testing);
        totalAccuracy += EvaluationMeasures::accuracy(testing);
    }
    return totalAccuracy / (double) folds;
}