#ifndef LAB6_DATAREADER_H
#define LAB6_DATAREADER_H


#include <vector>
#include "Point.h"
#include <string>

class DataReader {
public:
    void read(const std::string &fileName, std::vector<Point> &data);

    void write(const std::string &fileName, const std::vector<Point> &data);
};


#endif //LAB6_DATAREADER_H
