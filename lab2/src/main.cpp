#include "Statistics.h"
#include "FeatureVector.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;

bool LoadDataset(const string &fileName, vector<FeatureVector> &data) {
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
            (*it).Add(std::stod(featureText));
            ++it;
        }

        if (it != data.end() ) {
            return false;
        }
    }
    return true;
}

int main() {

    vector<FeatureVector> data;
    string fileName = "/tmp/winequality.csv";
    if (!LoadDataset(fileName, data)) {
        printf("Couldn't load the dataset from :%s\n", fileName.c_str());
        return 1;
    }

    return 0;
}
