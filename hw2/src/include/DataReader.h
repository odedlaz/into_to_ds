#ifndef CLASSIFICATION_DATAREADER_H
#define CLASSIFICATION_DATAREADER_H


#include <vector>
#include "Point.h"
#include <string>

class DataReader {
public:
    /*
     * loads a set of points from a given filename
     * @param fileName std::string the filename to load the points from
     * @param data std::vector<Point> a vector to load the points to
     */
    void read(const std::string &fileName, std::vector<Point> &data);
};


#endif //CLASSIFICATION_DATAREADER_H
