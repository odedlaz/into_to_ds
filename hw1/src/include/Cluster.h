#ifndef HW1_CLUSTER_H
#define HW1_CLUSTER_H

#include <vector>
#include "Point.h"

class Cluster {
private:
    int _idCluster;
    Point _prototype;
    //vector of point indexes in the vector of all points stored in KMeans class
    std::vector<size_t> _points;

    std::vector<size_t>::iterator find(size_t pointID);

public:
    Cluster(int idCluster, const Point &prototype);

    void addPoint(size_t pointID);

    bool removePoint(size_t pointID);

    void updatePrototype(const std::vector<Point> &allPoints);

    double getDistanceToPrototype(const Point &point) const;

    void print(const std::vector<Point> &allPoints) const;

};

#endif
