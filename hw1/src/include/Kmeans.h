#ifndef HW1_KMEANS_H
#define HW1_KMEANS_H

#include <vector>
#include "Cluster.h"
#include "Point.h"

class KMeans {
private:
    unsigned _K; // number of clusters
    unsigned _maxIterations;
    std::vector<Cluster> _clusters;
    std::vector<Point> _points;

    // return ID of nearest center (uses euclidean distance)
    size_t getIDNearestCenter(const Point &point);

public:
    KMeans(unsigned K, unsigned maxIterations) : _K(K), _maxIterations(maxIterations) {}

    void run(const std::vector<Point> &points);

    void print() const;

private:
    void setRandomSeeds();

    bool attributePoints();


};


#endif //LAB2_KMEANS_H
