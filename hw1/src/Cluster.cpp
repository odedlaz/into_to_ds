#include "include/Cluster.h"
#include <cmath>
#include <cstdio>

using std::vector;
using std::string;
using std::cout;
using std::endl;


bool Cluster::removePoint(size_t pointID) {
    std::vector<size_t>::iterator iter = find(pointID);
    if (iter != _points.end()) {
        _points.erase(iter);
    }

    return iter != _points.end();
}

void Cluster::print(const vector<Point> &allPoints) const {
    cout << "Cluster " << _idCluster + 1 << endl;
    for (vector<Point>::size_type j = 0; j < _points.size(); j++) {
        size_t pID = allPoints[_points[j]].getID() + 1;
        cout << "Point " << pID << ": ";
        cout << allPoints[_points[j]];
        cout << " - " << pID << endl;
    }

    cout << "Cluster prototype: " << _prototype << endl;
}

Cluster::Cluster(int idCluster, const Point &point) :
        _idCluster(idCluster),
        _prototype(point) {
    _points.push_back(point.getID());
}

void Cluster::addPoint(size_t pointID) {
    // if the point already exists -> don't add it
    if (find(pointID) != _points.end()) {
        return;
    }

    _points.push_back(pointID);
}

void Point::print() const {
    std::vector<double>::const_iterator it = _values.begin();
    for (it; it != _values.end(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
}

void Cluster::updatePrototype(const std::vector<Point> &allPoints) {
    double numOfDimensions = allPoints.front().getDimension();
    vector<size_t>::iterator iter;

    for (size_t dimension = 0; dimension < numOfDimensions; dimension++) {
        double sum = 0;

        for (iter = _points.begin(); iter != _points.end(); ++iter) {
            // get the point that belongs to this cluster
            sum += allPoints[*iter].getValue(dimension);
        }

        _prototype.setValue(sum / _points.size(), dimension);
    }
}

double Cluster::getDistanceToPrototype(const Point &point) const {
    return _prototype.euclideanDistance(_prototype, point);
}

std::vector<size_t>::iterator Cluster::find(size_t pointID) {
    std::vector<size_t>::iterator it = _points.begin();
    for (it; it != _points.end(); it++) {
        if (*it == pointID) {
            return it;
        }
    }
    return _points.end();
}

