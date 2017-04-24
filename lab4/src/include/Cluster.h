#ifndef LAB3_KMEANS_CLUSTER_H
#define LAB3_KMEANS_CLUSTER_H

#include "Point.h"

class Cluster {
private:
    int _idCluster;
    std::vector<Point> _points;
public:
    static double singleLink(const Cluster &cluster1, const Cluster &cluster2);

    void merge(Cluster &cluster2);

    bool isValid() { return _idCluster != _invalid; }

public:
    Cluster(int id_cluster, const Point &point);

    void print() const;

private:
    static const int _invalid;

    static void calcAllInterPointDistances(const Cluster &cluster, const Cluster &cluster2, std::vector<double> vector);
    static void calcAllInterPointDistances(const Cluster &cluster,
                                           const Cluster &cluster2,
                                           std::vector<double> &distance);

};

#endif
