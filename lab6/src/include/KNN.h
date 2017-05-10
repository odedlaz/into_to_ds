#ifndef LAB6_KNN_H
#define LAB6_KNN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Point;

class KNN {
public:
    bool train(const std::vector <Point> &points);

    void predict(Point &newPoint) const;

    void reset() { _data.clear(); }

    KNN(size_t k) : _k(k) {}

private:
    size_t maxDistIndex(const std::vector <std::pair<std::string, double>> &distances, double &max) const;

    const std::string getMajorityClass(const std::vector <std::pair<std::string, double>> &distances) const;

    double euclidianDistance(const Point &p1, const Point &p2) const;

private:
    std::vector <Point> _data;
    size_t _k;

};


#endif //LAB5_KNN_H
