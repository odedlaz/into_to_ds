#include "include/Cluster.h"
#include <cstdlib>
#include <limits>

using std::vector;
using std::cout;
using std::endl;

const int Cluster::_invalid = -1;

Cluster::Cluster(int idCluster, const Point &point) : _idCluster(idCluster) {
    _points.push_back(point);
}


void Cluster::print() const {
    cout << "Cluster " << _idCluster + 1 << endl;
    for (vector<Point>::size_type j = 0; j < _points.size(); j++) {
        cout << "Point " << _points[j].getID() + 1 << ": ";
        _points[j].print();
    }
}


double Cluster::singleLink(const Cluster &cluster1, const Cluster &cluster2) {
    std::vector<double> distances;
    calcAllInterPointDistances(cluster1, cluster2, distances);
    double min = std::numeric_limits<double>::max();
    for (vector<double>::const_iterator cit = distances.begin();
         cit != distances.end(); cit++) {
        if (min > *cit) min = *cit;
    }
    return min;
}


void Cluster::merge(Cluster &cluster2) {
    _points.insert(_points.end(), cluster2._points.begin(), cluster2._points.end());
    cluster2._idCluster = Cluster::_invalid;
}

void Cluster::calcAllInterPointDistances(const Cluster &cluster1,
                                         const Cluster &cluster2,
                                         std::vector<double> &distances) {

    std::vector<Point> pointsA = cluster1._points;
    std::vector<Point> pointsB = cluster2._points;

    for (std::vector<Point>::iterator pItA = pointsA.begin(); pItA != pointsA.end(); ++pItA) {
        for (std::vector<Point>::iterator pItB = pointsB.begin(); pItB != pointsB.end(); ++pItB) {
            double dist = (*pItA).euclideanDistance(*pItB);
            distances.push_back(dist);
        }
    }
}

double Cluster::completeLink(const Cluster &cluster1, const Cluster &cluster2) {
    std::vector<double> distances;
    calcAllInterPointDistances(cluster1, cluster2, distances);
    double max = std::numeric_limits<double>::min();//initialize to minimum value.
    for (vector<double>::iterator iter = distances.begin(); iter != distances.end(); iter++) {
        if (*iter > max) max = *iter;
    }
    return max;
}


double Cluster::averageDistance(const Cluster &cluster1, const Cluster &cluster2) {
    std::vector<double> distances;
    calcAllInterPointDistances(cluster1, cluster2, distances);
    double sum = 0;
    for (vector<double>::iterator cit = distances.begin(); cit != distances.end(); cit++) {
        sum += *cit;
    }
    return sum / distances.size();
}