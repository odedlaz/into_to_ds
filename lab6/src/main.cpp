#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "include/KNN.h"
#include "include/DataReader.h"
#include "include/EvaluationMeasures.h"
#include "include/Evaluation.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

double runCrossValidation(vector<Point> &allData, int k, int folds) {
    KNN knn(k);
    if (knn.train(allData)) {
        Evaluation evaluation(knn);
        return evaluation.crossValidation(allData, folds);
    }
    return -1;
}

void trainKnn5(vector<Point> &allData) {
    KNN knn(5);
    if (knn.train(allData)) {
        knn.predict(*allData.begin());
        cout << "First element Prediction class: " << (*allData.begin()).getPrediction() << endl;
    }

}

void evaluationTenFold(vector<Point> &allData) {
    cout << "10-fold Cross Validation is: " << runCrossValidation(allData, 5, 10) << endl;
    /*KNN knn(5);
    if (knn.train(allData)) {
        Evaluation evaluation(knn);
        cout << "10-fold Cross Validation is: " << evaluation.crossValidation(allData, 10) << endl;
    }*/
}

void question1(vector<Point> &allData) {
    KNN knn(1);
    if (knn.train(allData)) {
        for (vector<Point>::iterator iter = allData.begin(); iter != allData.end(); iter++) {
            knn.predict(*iter);
        }
        cout << "Accuracy for KNN1 is: " << EvaluationMeasures::accuracy(allData) << endl;
    }
}

void question2(vector<Point> &allData) {
    double bestAccuracy = 0.0;
    int bestK = 0;
    for (int k = 1; k <= 30; k++) {
        double currentAccuracy = runCrossValidation(allData, k, allData.size());
        if (currentAccuracy > bestAccuracy) {
            bestAccuracy = currentAccuracy;
            bestK = k;
        }
        cout << "leave-one-out Cross Validation for: " << k << "-Neighbours is: " << currentAccuracy << endl;
    }
    cout << bestK << " is the best Classifier. Best Accuracy is: " << bestAccuracy << endl;
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
    cout << "Data size: " << allData.size() << endl;
    trainKnn5(allData);
    evaluationTenFold(allData);
    cout << "   Question 1:" << endl;
    question1(allData);
    cout << "   Question 2:" << endl;
    question2(allData);
    cout << "   Question 3:" << endl;
    cout << "2-fold-cross-validation:" << runCrossValidation(allData, 8, 2) << endl;
    cout << "10-fold-cross-validation:" << runCrossValidation(allData, 8, 10) << endl;
    cout << "leave-one-out-cross-validation:" << runCrossValidation(allData, 8, allData.size()) << endl;


    return 0;
}

