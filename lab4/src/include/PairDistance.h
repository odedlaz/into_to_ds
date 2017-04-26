#ifndef LAB4_PAIRSIMILARITY_H
#define LAB4_PAIRSIMILARITY_H

#include <stdlib.h>

class PairDistance {
private:
    size_t _clusterID1;
    size_t _clusterID2;
    double _distance;
public:
    PairDistance(size_t clusterID1, size_t clusterID2, double distance) : _clusterID1(clusterID1),
                                                                          _clusterID2(clusterID2),
                                                                          _distance(distance) {}

    void setDistance(double distance) { _distance = distance; }

    size_t getClusterID1() const { return _clusterID1; }

    size_t getClusterID2() const { return _clusterID2; }

    bool operator>(const PairDistance &ps) const {
        return _distance > ps._distance;
    }
};


#endif //LAB4_PAIRSIMILARITY_H
