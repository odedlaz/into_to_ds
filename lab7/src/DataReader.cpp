#include "include/DataReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using std::string;
using std::vector;


void DataReader::read(const std::string &fileName, std::vector<Point> &data) {

    std::ifstream file;
    file.open(fileName.c_str(), std::ifstream::in);
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line)) {
        size_t variables = (size_t) std::count(line.begin(), line.end(), ',');
        Point p(variables);
        std::istringstream all(line);
        size_t count(0);
        while (count < variables) {
            string val;
            getline(all, val, ',');
            std::istringstream iss(val);
            double dval;
            iss >> dval;
            p[count] = dval;
            count++;
        }
        //the last value is the class
        string _cls;
        getline(all, _cls);
        p.setClass(_cls);
        data.push_back(p);
    }
}

void DataReader::write(const std::string &fileName, const std::vector<Point> &data) {
    std::ofstream file;
    file.open(fileName.c_str(), std::ofstream::out);
    if (!file.is_open())
        return;
    for (std::vector<Point>::size_type pi = 0; pi < data.size(); pi++) {
        file << data[pi] << std::endl;
    }

    file.close();
}