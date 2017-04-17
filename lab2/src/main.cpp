#include "include/Statistics.h"
#include "include/FeatureVector.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <tr1/tuple>

using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;

bool loadDataset(const string &fileName, vector<FeatureVector> &data) {
    ifstream infile(fileName);
    if (!infile.is_open()) {
        return false;
    }
    string line;

    // First we read the first line of the file,
    // which specifies the names of the variables
    if (getline(infile, line)) {
        stringstream lineStream(line);
        string variableName;
        while (getline(lineStream, variableName, ',')) {
            variableName = variableName.substr(1, variableName.length() - 2);
            data.push_back(FeatureVector(variableName));
        }
    }

    while (getline(infile, line)) {
        stringstream lineStream(line);
        string featureText;
        vector<FeatureVector>::iterator it = data.begin();

        while (getline(lineStream, featureText, ',')) {
            (*it).append(std::stod(featureText));
            ++it;
        }

        if (it != data.end()) {
            return false;
        }
    }
    return true;
}


int main(int argc, char *argv[]) {
    string fileName = "/mnt/share/students/LAB2/winequality.csv";
    // if the filename was passed as an argument, use that instead.
    if (argc == 2) {
        fileName = argv[1];
    }

    vector<FeatureVector> data;

    if (!loadDataset(fileName, data)) {
        printf("Couldn't load the dataset from :%s\n", fileName.c_str());
        return 1;
    }

    double min, max;
    // create seed correlation for min and max values
    min = max = (*data.begin()).getCorrelation(*(data.begin() + 1));

    std::tr1::tuple<FeatureVector, FeatureVector> minTuple, maxTuple;

    for (vector<FeatureVector>::iterator iterA = data.begin(); iterA != data.end(); ++iterA) {
        FeatureVector fvA = (*iterA);

        printf("\n=== %s ===\n", fvA.getName().c_str());
        cout << "Number of Features:" << fvA.length() << endl;
        cout << "Feature Mean: " << fvA.getMean() << endl;
        cout << "Feature Variance: " << fvA.getVariance() << endl;
        cout << "Standard Deviation: " << fvA.getStandardDeviation() << endl;

        for (vector<FeatureVector>::iterator iterB = iterA + 1; iterB != data.end(); ++iterB) {
            FeatureVector fvB = (*iterB);
            double correlation = fvA.getCorrelation(fvB);

            if (correlation > max) {
                max = correlation;
                maxTuple = std::tr1::tuple<FeatureVector, FeatureVector>(fvA, fvB);
            }

            if (correlation < min) {
                min = correlation;
                minTuple = std::tr1::tuple<FeatureVector, FeatureVector>(fvA, fvB);
            }
        }
    }

    printf("\nStrongest Correlation between '%s' and '%s' is: %.3f\n",
           std::tr1::get<0>(maxTuple).getName().c_str(),
           std::tr1::get<1>(maxTuple).getName().c_str(),
           max);

    printf("Weakest Correlation between '%s' and '%s' is: %.3f\n",
           std::tr1::get<0>(minTuple).getName().c_str(),
           std::tr1::get<1>(minTuple).getName().c_str(),
           min);

    return 0;
}
