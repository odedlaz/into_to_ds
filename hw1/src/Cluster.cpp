#include "include/Cluster.h"
#include <cmath>
#include <cstdio>

using std::vector;
using std::string;
using std::cout;
using std::endl;


bool Cluster::removePoint(size_t pointID) {
    for (vector<Point>::size_type i = 0; i < _points.size(); i++) {
        if (_points[i] == pointID) {
            _points.erase(_points.begin() + i);
            return true;
        }
    }
    return false;
}

void Cluster::print(const vector<Point> &allPoints) const {
    cout << "Cluster " << _idCluster + 1 << endl;
    for (vector<Point>::size_type j = 0; j < _points.size(); j++) {
        cout << "Point " << allPoints[_points[j]].getID() + 1 << ": ";
        allPoints[_points[j]].print();
    }

    cout << "Cluster prototype: ";
    _prototype.print();
}

Cluster::Cluster(int idCluster, const Point &point) :
        _idCluster(idCluster),
        _prototype(point) {
    _points.push_back(point.getID());
}

void Cluster::addPoint(size_t pointID) {
    vector<unsigned long>::iterator it;
    for (it = _points.begin(); it != _points.end(); ++it) {
        if ((*it) == pointID) {
            return;
        }
    }
    _points.push_back(pointID);
}

void Cluster::updatePrototype(const std::vector<Point> &allPoints) {
    double dimension = allPoints.front().getDimension();
    vector<unsigned long>::iterator iter;
    for (size_t i = 0; i < dimension; i++) {
        double sum = 0;
        for (iter = _points.begin(); iter != _points.end(); ++iter) {
            sum += allPoints[*iter].getValue(i);
        }
        _prototype.setValue(sum / _points.size(), i);
    }
}

double Cluster::getDistanceToPrototype(const Point &point) const {
    return _prototype.euclideanDistance(point);
}

