#ifndef HW1_KMEDOIDS_H
#define HW1_KMEDOIDS_H

#include <vector>
#include "Cluster.h"
#include "Point.h"

class KMedoids {
private:
    unsigned _K; // number of clusters
    unsigned _maxIterations;
    std::vector<Cluster> _clusters;
    std::vector<Point> _points;

    // return ID of nearest center (uses euclidean distance)
    size_t getIDNearestCenter(const Point &point);

public:
    /**
     * Constructor
     *
     * Initializes a new instance of a KMedoids
     * @param K uint The number of clusters to create
     * @param maxIterations uint The maximum iterations
     */
    KMedoids(unsigned K, unsigned maxIterations) : _K(K), _maxIterations(maxIterations) {}

    /**
     * run
     *
     * run the KMeans algorithm on a given set of points
     *
     * @param points std::vector<Point>& A vector of points to run on
     */
    void run(const std::vector<Point> &points);

    /**
     * print
     *
     * dump the state of all the clusters
     */
    void print() const;

    /**
     *
     * calculateSSE
     *
     * Calculate the global SSE, for all the clusters
     */
    double calculateSSE() const;

private:
    /**
     * setRandomSeeds
     *
     * Add random seed points
     */
    void setRandomSeeds();

    /**
     * attributePoints
     *
     * Iterate the points in the dataset and attribute them to the right cluster
     *
     * @return A flag indicating if the points have been attributed
     */
    bool attributePoints();

};


#endif //HW1_KMEDOIDS_H
