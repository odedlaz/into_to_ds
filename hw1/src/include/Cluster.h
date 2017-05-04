#ifndef HW1_CLUSTER_H
#define HW1_CLUSTER_H

#include <vector>
#include <ostream>
#include "Point.h"

/**
 * Cluster
 * Keeps track of the cluster, allows manipulation
 */
class Cluster {
private:
    int _idCluster;
    Point _prototype;
    //vector of point indexes in the vector of all points stored in KMeans class
    std::vector<size_t> _points;

    /**
     * find
     *
     * Find the index of a given point in the Cluster's inner point-id vector
     *
     * @param pointID int The point id
     * @return std::vector<size_t>::iterator An iterator to the location of the point-id in the cluster's vector
     */
    std::vector<size_t>::iterator find(size_t pointID);

public:
    /**
     * Constructor
     *
     * Initializes a new instance of a Cluster
     *
     * @param idCluster int The cluster id
     * @param prototype Point& a point to use as the initial prototype
     */
    Cluster(int idCluster, const Point &prototype);

    /**
     * addPoint
     *
     * Adds a point to the cluster
     *
     * @param pointID size_t The id of the point to add
     */
    void addPoint(size_t pointID);

    /**
     * remotePoint
     *
     * Remove a point from the cluster
     *
     * @param pointID size_t  The id of the point to remove
     */
    bool removePoint(size_t pointID);

    /**
     * updatePrototype
     *
     * Update the cluster's prototype
     *
     * @param allPoints std::vector<Point>& a vector of all the points in the dataset
     */
    void updatePrototype(const std::vector<Point> &allPoints);

    /**
     * updatePrototypeMedoid
     *
     * Update the cluster's prototype medoid
     *
     * @param allPoints std::vector<Point>& a vector of all the points in the dataset
     */
    void updatePrototypeMedoid(const std::vector<Point> &allPoints);

    /**
     * getDistanceToPrototype
     *
     * Get the euclidiean distance from a given point to the prototype
     *
     * @param point Point& a point to calculate distance from
     * @return The euclidiean distance between the prototype and the given point
     */
    double getDistanceToPrototype(const Point &point) const;

    /**
     * print
     *
     * spit to stdout the state of the cluster
     *
     * @param allPoints std::vector<Point>& a vector of all the points in the dataset
     */
    void print(const std::vector<Point> &allPoints) const;

    /**
     * calculateSSE
     *
     * Calculate the clusters overall SSE
     *
     * @param allPoints std::vector<Point>& a vector of all the points in the dataset
     * @return The calculated SSE
     */
    double calculateSSE(const std::vector<Point> &allPoints) const;
};

#endif
