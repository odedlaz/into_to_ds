//
// Created by annabel@staff.technion.ac.il on 5/11/17.
//

#ifndef CLASSIFICATION_DATAREADER_H
#define CLASSIFICATION_DATAREADER_H


#include <vector>
#include "Point.h"
#include <string>

class DataReader {
public:
    void read(const std::string& fileName, std::vector<Point>& data);



};


#endif //CLASSIFICATION_DATAREADER_H
