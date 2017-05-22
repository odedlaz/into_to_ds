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

void runNormalizers(vector<Point> &allData, KNN& knn, char normalizationType) {
    cout << "No Normalization: " << Evaluation(knn).crossValidation(allData, 10) << endl;
    size_t dimension = allData[0].getDimension();

    // default normalizer

    switch (normalizationType) {
        case 'z': {
            cout << "Z Normalization: ";
            ZNormalizer normalizer = ZNormalizer(dimension);
            runKNN(knn, normalizer,  allData);
            break;
        }

        case 'x': {
            cout << "Min-Max Normalization: ";
            MinMaxNormalizer normalizer = MinMaxNormalizer(dimension);
            runKNN(knn, normalizer, allData);
            break;
        }
        case 's': {
            cout << "Sum Normalization: ";
            SumNormalizer normalizer = SumNormalizer(dimension);
            runKNN(knn, normalizer, allData);
            break;
        }
        default: {
            cout << "Normalization method invalid" << endl;
            return;
        }
    }

}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Usage: <filename> <knn> <normalization type>" << endl;
        cerr << "z: Z Normalization" << endl;
        cerr << "s: Sum Normalization" << endl;
        cerr << "x: Min-Max Normalization" << endl;

        return 1;
    }
    string fileName(argv[1]);
    DataReader dr;
    vector<Point> allData;
    dr.read(fileName, allData);
    size_t iterations = (size_t) atoi(argv[2]);
    cout << "=== KNN set to " << iterations << " ===" << endl;

    KNN knn(iterations);
    runNormalizers(allData, knn, argv[3][0]);
    return 0;
}