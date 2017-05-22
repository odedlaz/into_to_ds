#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "include/KNN.h"
#include "include/DataReader.h"
#include "include/EvaluationMeasures.h"
#include "include/Evaluation.h"
#include "include/SumNormalizer.h"
#include "include/ZNormalizer.h"
#include "include/MinMaxNormalizer.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;


void normalizeData(Normalizer &normalizer, const vector<Point> &data, vector<Point> &normData) {
    normalizer.init(data);
    for (std::vector<Point>::size_type pi = 0; pi < data.size(); pi++) {
        Point normPoint(data[pi].getDimension());
        normalizer.normalize(data[pi], normData[pi]);
    }
}

void runKNN(KNN &knn, Normalizer &normalizer, const vector<Point> &data) {
    vector<Point> normData(data.size(), Point(data[0].getDimension()));
    normalizeData(normalizer, data, normData);
    knn.reset();
    Evaluation eval(knn);
    cout << eval.crossValidation(normData, 10) << endl;
}

void runNormalizers(vector<Point> &allData, KNN &knn) {
    Evaluation eval(knn);
    size_t dimension = allData[0].getDimension();
    cout << "No normalization: " << eval.crossValidation(allData, 10) << endl;

    cout << "ZNormalization: ";
    ZNormalizer zN(dimension);
    vector<Point> zNallData(allData);
    runKNN(knn, zN, zNallData);

    cout << "SumNormalization: ";
    SumNormalizer sN(dimension);
    vector<Point> sNallData(allData);
    runKNN(knn, sN, sNallData);

    cout << "MinMaxNormalization: ";
    MinMaxNormalizer minMaxN(dimension);
    vector<Point> minMaxNallData(allData);
    runKNN(knn, minMaxN, minMaxNallData);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "You are missing the input file name" << endl;
        return 1;
    }
    string fileName(argv[1]);
    DataReader dr;
    vector<Point> allData;
    dr.read(fileName, allData);
    cout << "=== KNN set to 5 ===" << endl;
    KNN knn5(5);
    runNormalizers(allData, knn5);
    cout << "=== KNN set to 7 ===" << endl;
    KNN knn7(7);
    runNormalizers(allData, knn7);
    return 0;
}