#include "include/Cluster.h"
#include <cmath>
#include <cstdio>
#include <set>

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


void Cluster::updatePrototype(const std::vector<Point> &allPoints) {
    double numOfDimensions = allPoints.front().getDimension();

    vector<size_t>::iterator iter;

    for (size_t dimension = 0; dimension < numOfDimensions; dimension++) {
        double sum = 0;

        for (iter = _points.begin(); iter != _points.end(); ++iter) {
            // get the point that belongs to this cluster
            const Point &point = allPoints[*iter];
            sum += point.getValue(dimension);
        }

        _prototype.setValue(sum / _points.size(), dimension);
    }
}

double Cluster::getDistanceToPrototype(const Point &point) const {
    return Point::euclideanDistance(_prototype, point);
}

std::vector<size_t>::iterator Cluster::find(size_t pointID) {
    std::vector<size_t>::iterator it;
    for (it = _points.begin(); it != _points.end(); it++) {
        if (*it == pointID) {
            return it;
        }
    }
    return _points.end();
}


void Cluster::updatePrototypeMedoid(const std::vector<Point> &allPoints) {
    vector<size_t >::iterator it, otherIterator;
    double min = -1;


    for (it = _points.begin(); it != _points.end(); ++it) {
        const Point &point = allPoints[*it];
        double sum = 0;

        for (otherIterator = _points.begin(); otherIterator != _points.end(); ++otherIterator) {

            // don't calculate distance from self
            if (it == otherIterator) {
                continue;
            }

            const Point &otherPoint = allPoints[*otherIterator];
            sum += Point::euclideanDistance(otherPoint, point);
        }

        if (min == -1 || min > sum) {
            _prototype = point;
            min = sum;
        }
    }
}
