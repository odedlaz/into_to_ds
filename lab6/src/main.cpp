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

void question1(vector<Point> &allData) {
    KNN knn(5);
    knn.train(allData);
    knn.predict(*allData.begin());
    cout << "first element Prediction class: " << (*allData.begin()).getPrediction() << endl;


}

void question2(vector<Point> &allData) {
    KNN knn(5);
    knn.train(allData);
    Evaluation evaluation(knn);
    cout << "Accuracy is: " << evaluation.crossValidation(allData, 10) << endl;
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
    cout << allData.size() << endl;
//    size_t folds = 10;
//    Evaluation evaluation = new Evaluation()
//    double accuracy = Evaluation::crossValidation(allData, folds);
//    cout << accuracy << endl;
    question1(allData);
    question2(allData);

    return 0;
}

