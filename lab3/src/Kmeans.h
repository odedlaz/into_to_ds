//
// Created by shraga89@st.technion.ac.il on 3/5/17.
//

#ifndef LAB3_KMEANS_KMEANS_H
#define LAB3_KMEANS_KMEANS_H

#include <vector>
#include "Cluster.h"
class Point;

class KMeans
{
private:
    unsigned _K; // number of clusters
    unsigned _maxIterations;
    std::vector<Cluster> _clusters;

    // return ID of nearest center (uses euclidean distance)
    size_t getIDNearestCenter(const Point& point);

public:
    KMeans(unsigned K, unsigned maxIterations): _K(K), _maxIterations(maxIterations)  {    }

    void run( std::vector<Point> &points);
private:
    void setRandomSeeds( std::vector<Point> &points );

    bool attributePoints( std::vector<Point> &points);
};


#endif //LAB2_KMEANS_H
