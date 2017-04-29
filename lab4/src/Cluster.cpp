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

/**
 * Single Link clustering method.
 * using Single link method between two clusters.
 * find the minimum distance between points of 2 clusters.
 * @param cluster1 Type Cluster
 * @param cluster2 Type Cluster
 * @return double result of minimum distance.
 */
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

/**
 * merge adjacent clusters.
 * merges the clusters that were chosen by the given method.
 * @param cluster2 Type Cluster
 */
void Cluster::merge(Cluster &cluster2) {
    _points.insert(_points.end(),
                   cluster2._points.begin(),
                   cluster2._points.end());

    cluster2._idCluster = Cluster::_invalid;
}
/**
 * calculate distance between two points of different clusters.
 * for every point in cluster A calculates distances to cluster B points.
 * @param cluster1 Type Cluster
 * @param cluster2 Type Cluster
 * @param distances Type vector<dobule>, holds all the distances.
 */
void Cluster::calcAllInterPointDistances(const Cluster &cluster1,
                                         const Cluster &cluster2,
                                         std::vector<double> &distances) {

    std::vector<Point> pointsA = cluster1._points;
    std::vector<Point> pointsB = cluster2._points;
    std::vector<Point>::iterator pItA, pItB;

    for (pItA = pointsA.begin(); pItA != pointsA.end(); ++pItA) {
        for (pItB = pointsB.begin(); pItB != pointsB.end(); ++pItB) {
            double dist = (*pItA).euclideanDistance(*pItB);
            distances.push_back(dist);
        }
    }
}
/**
 * Complete Link clustering method.
 * using Complete Link method between two clusters.
 * finds the maximum distance between points of 2 clusters.
 * then "chooses" the minimum value of all maximum distances, and merge these clusters.
 * @param cluster1 Type Cluster
 * @param cluster2 Type Cluster
 * @return double result of maximum distance.
 */
double Cluster::completeLink(const Cluster &cluster1, const Cluster &cluster2) {
    std::vector<double> distances;
    calcAllInterPointDistances(cluster1, cluster2, distances);
    double max = std::numeric_limits<double>::min();//initialize to minimum value.

    for (vector<double>::iterator iter = distances.begin(); iter != distances.end(); iter++) {
        if (*iter > max) max = *iter;
    }

    return max;
}
/**
 * Average Link method
 * using Average Link method between two clusters.
 * finds the average distance between two clusters.
 * then "chooses" the minimum value of all average distances, and merge these clusters.
 * @param cluster1 Type Cluster
 * @param cluster2 Type Cluster
 * @return double result of average distance.
 */
double Cluster::averageDistance(const Cluster &cluster1, const Cluster &cluster2) {
    double sum = 0;

    std::vector<double> distances;
    calcAllInterPointDistances(cluster1, cluster2, distances);

    for (vector<double>::iterator it = distances.begin(); it != distances.end(); it++) {
        sum += *it;
    }
    return sum / distances.size();
}