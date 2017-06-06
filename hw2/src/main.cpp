#include <iostream>
#include "include/Tests.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using std::string;
using std::vector;


int main(int argc, char *argv[]) {
    if (argc < 3)
        return -1;

    string dataFile(argv[1]);
    vector<Point> allData;
    Tests::loadData(dataFile, allData);
    string testName(argv[2]);

    Tests::KNNTestEuclidean(allData);

    return 0;
}