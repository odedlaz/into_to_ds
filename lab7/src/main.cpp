#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "KNN.h"
#include "DataReader.h"
#include "EvaluationMeasures.h"
#include "Evaluation.h"
#include "SumNormalizer.h"
#include "ZNormalizer.h"
#include "MinMaxNormalizer.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;


void normalizeData(Normalizer &normalizer, const vector<Point>& data, vector<Point>& normData )
{
    normalizer.init(data);
    for (std::vector<Point>::size_type pi=0; pi<data.size(); pi++) {
        Point normPoint(data[pi].getDimension());
        normalizer.normalize(data[pi],normData[pi]);
    }
}

void runKNN(KNN& knn, Normalizer &normalizer, const vector<Point> &data )
{
    vector<Point> normData(data.size(),Point(data[0].getDimension()));
    normalizeData(normalizer, data, normData);
    knn.reset();
    Evaluation eval(knn);
    cout << eval.crossValidation(normData,10) << endl;
}

int main(int argc, char *argv[])
{
    if (argc<2)
    {
        cerr << "You are missing the input file name" << endl;
        return 1;
    }
    string fileName(argv[1]);
    DataReader dr;
    vector<Point> allData;
    dr.read(fileName, allData);
    KNN knn(5);
    Evaluation eval(knn);
    cout << "No normalization: " << eval.crossValidation(allData,10) << endl;
    ZNormalizer zN(allData[0].getDimension());
    runKNN(knn, zN, allData);
    return 0;
}