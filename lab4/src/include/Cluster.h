#ifndef LAB3_KMEANS_CLUSTER_H
#define LAB3_KMEANS_CLUSTER_H

#include "Point.h"

class Cluster {
private:
    int _idCluster;
    std::vector<Point> _points;
public:
    static double singleLink(const Cluster &cluster1, const Cluster &cluster2);

    static double completeLink(const Cluster &cluster1, const Cluster &cluster2);

    static double averageDistance(const Cluster &cluster1, const Cluster &cluster2);

    void merge(Cluster &cluster2);
    /**
   * Validating cluster's usage.
   * if cluster was merge, instead of deleting it from vector, mark as invalid because of efficiency reasons.
   * @return boolean result of cluster's validity.
   */
    bool isValid() { return _idCluster != _invalid; }

public:
    /**
    * Constructor
     * construct a Cluster
    * @param id_cluster Type int - the ID of Cluster
    * @param point Type vector<Point> - vector of points that belong to cluster
    */
    Cluster(int id_cluster, const Point &point);

    void print() const;


private:
    static const int _invalid;

    static void calcAllInterPointDistances(const Cluster &cluster,
                                           const Cluster &cluster2,
                                           std::vector<double> &distance);
};

#endif
