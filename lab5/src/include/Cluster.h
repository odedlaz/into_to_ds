//
// Created by anna on 4/22/2017.
//

#ifndef LAB5_CLUSTER_H
#define LAB5_CLUSTER_H

#include "Point.h"

class Cluster
{
private:
    size_t _idCluster;
    std::vector<Point> _points;
public:
    Cluster(size_t id_cluster);
    void addPoint(const Point& point){ _points.push_back(point); }
    bool isInCluster(const Point& point) const;
    double sumSquaresPointToCluster(const Point& point) const;
    double avgEuclideanPointToCluster(const Point& point) const;
    Point getCenterPoint() const;
    void getMajority(std::string& name, size_t& count) const;
    void print( ) const;
    size_t getID() const { return _idCluster; }
    const Point& operator[](size_t index)const{ return _points[index]; }
    size_t getSize() const{ return _points.size(); }

};


#endif //LAB5_CLUSTER_H
