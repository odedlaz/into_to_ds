#include <cstdlib>
#include "include/AgglomerativeClustering.h"
#include <limits>

using std::vector;
using std::string;

const string AgglomerativeClustering::_types[countTypes] = {"SingleLink", "CompleteLink", "AverageLink"};

/*
 * assignClusters
 * add each point to a cluster
 * @param points a vector<Point> that holds the points
 */
void AgglomerativeClustering::assignClusters(vector<Point> &points) {
    for (vector<Point>::size_type i = 0; i < points.size(); i++) {
        Cluster cluster((int) i, points[i]);
        _clusters.push_back(cluster);
    }
}

/*
 * initDistances
 * initialize the distance vector with point pairs
 * @param points a vector<Point> that holds all the points
 */
void AgglomerativeClustering::initDistances(const std::vector<Point> &points) {
    for (vector<Point>::size_type i = 0; i < (points.size() - 1); i++) {
        for (vector<Point>::size_type j = i + 1; j < points.size(); j++) {
            _distances.push_back(PairDistance(i, j, points[i].euclideanDistance(points[j])));
        }
    }
}

/*
 * findClosestClusters
 * find the closest cluster relative to a PairDistance
 * @param psMinimum an instance of PairDistance to calculate against
 * @return true if distances aren't empty, otherwise -> false
 */
bool AgglomerativeClustering::findClosestClusters(PairDistance &psMinimum) {
    if (_distances.empty()) return false;
    for (vector<PairDistance>::const_iterator cit = _distances.begin();
         cit != _distances.end(); cit++) {
        if (psMinimum > *cit) {
            psMinimum = *cit;
        }
    }
    return true;
}

/*
 * removeDistances
 * remove a distance from the distance vector
 * @param pdClosest an instance of PairDistance to remove
 */
void AgglomerativeClustering::removeDistances(const PairDistance &pdClosest) {
    //cluster 2 is no longer present - needs to be removed from distances
    for (vector<PairDistance>::size_type i = 0; i != _distances.size();) {
        if ((_distances[i].getClusterID1() == pdClosest.getClusterID2()) ||
            (_distances[i].getClusterID2() == pdClosest.getClusterID2())) {
            _distances.erase(_distances.begin() + i);
        } else {
            i++;
        }
    }
}

/*
 * updateDistances
 * update the distance relative to a given PairDistance.
 * the update algorithm is picked at initialization time:
 * - Single Link
 * - Complete Link
 * - Average Link
 * @param pdClosest an instance of PairDistance to use
 */
void AgglomerativeClustering::updateDistances(const PairDistance &pdClosest) {
    removeDistances(pdClosest);

    //distances to cluster 1 need to be updated
    for (vector<PairDistance>::iterator it = _distances.begin();
         it != _distances.end(); it++) {
        if ((it->getClusterID1() == pdClosest.getClusterID1()) ||
            (it->getClusterID2() == pdClosest.getClusterID1())) {
            if (_type == AgglomerativeClustering::SingleLink)
                it->setDistance(Cluster::singleLink(_clusters[it->getClusterID1()],
                                                    _clusters[it->getClusterID2()]));

            else if (_type == AgglomerativeClustering::CompleteLink)
                it->setDistance(Cluster::completeLink(_clusters[it->getClusterID1()],
                                                      _clusters[it->getClusterID2()]));

            else if (_type == AgglomerativeClustering::AverageLink)
                it->setDistance(Cluster::averageDistance(_clusters[it->getClusterID1()],
                                                 _clusters[it->getClusterID2()]));
        }
    }
}

/*
 * countValidClusters
 * count the number of valid clusters
 * @return the number of valid clusters
 */
size_t AgglomerativeClustering::countValidClusters() {
    size_t count(0);
    for (vector<Cluster>::size_type i = 0; i < _clusters.size(); i++) {
        if (_clusters[i].isValid()) count++;
    }
    return count;
}

/*
 * run
 * run the clustering algorithm up to the given point
 * @param points a Point vector to use
 * @param clustersToStop a number that indicates on how many clusters to stop the algorithm
 * @param type the algorithm to use: Single Link, Complete Link, Average Link
 */
void AgglomerativeClustering::run(vector<Point> &points, unsigned clustersToStop, AgglomerativeClustering::eType type) {
    _type = type;
    // at the beginning each point is a cluster
    assignClusters(points);
    initDistances(points);
    while (countValidClusters() > clustersToStop) {
        PairDistance pdClosest = _distances[0];
        if (!findClosestClusters(pdClosest)) break;
        size_t clusterID1 = pdClosest.getClusterID1();
        size_t clusterID2 = pdClosest.getClusterID2();
        _clusters[clusterID1].merge(_clusters[clusterID2]);
        updateDistances(pdClosest);
    }
}

/*
 * print
 * print all valid clusters
 */
void AgglomerativeClustering::print() {
    for (vector<Cluster>::size_type i = 0; i < _clusters.size(); i++) {
        if (_clusters[i].isValid()) _clusters[i].print();
    }
}
