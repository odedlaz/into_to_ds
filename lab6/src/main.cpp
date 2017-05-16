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
/** runCrossValidation
 *  Generic function to run Cross Validation with given arguments
 * @param allData vector<Point> of Dataset
 * @param k int specifics the amount of neighbours
 * @param folds int specifics the amount of folds from cross validation
 * @return the average accuracy for the amount of folds.
 */
double runCrossValidation(vector<Point> &allData, int k, int folds) {
    KNN knn(k);
    if (knn.train(allData)) {
        Evaluation evaluation(knn);
        return evaluation.crossValidation(allData, folds);
    }
    return -1;
}
/** Lab Question 1 (in Class)
 * train the dataset with K=5 and predicts the 1st element in dataset.
 * @param allData vector<Point> of Dataset
 */
void trainKnn5(vector<Point> &allData) {
    KNN knn(5);
    if (knn.train(allData)) {
        knn.predict(*allData.begin());
        cout << "First element Prediction class: " << (*allData.begin()).getPrediction() << endl;
    }

}
/** Lab Question 2 (in Class)
 * runs 10-fold-cross-validation and prints the output.
 * @param allData vector<Point> of Dataset
 */
void evaluationTenFold(vector<Point> &allData) {
    cout << "10-fold Cross Validation is: " << runCrossValidation(allData, 5, 10) << endl;
}
/** Question 1 (For submission)
 * trains classifier for K=1, and then predicts the entire dataset.
 * also calculates the Accuracy.
 * @param allData vector<Point> of Dataset
 */
void question1(vector<Point> &allData) {
    KNN knn(1);
    if (knn.train(allData)) {
        for (vector<Point>::iterator iter = allData.begin(); iter != allData.end(); iter++) {
            knn.predict(*iter);
        }
        cout << "Accuracy for KNN1 is: " << EvaluationMeasures::accuracy(allData) << endl;
    }
}
/** Question 2 (For submission)
 * trains classifier for K=1..30, for each K runs Leave-One-Out Cross Validation and reports it's Accuracy.
 * prints the best Accuracy and it's K.
 * @param allData vector<Point> of Dataset
 */
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

