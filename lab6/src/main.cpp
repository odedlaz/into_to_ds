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


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "You are missing the input file name" << endl;
        return 1;
    }
    string fileName(argv[1]);
    DataReader dr;
    vector <Point> allData;
    dr.read(fileName, allData);
    cout << allData.size() << endl;

    return 0;
}