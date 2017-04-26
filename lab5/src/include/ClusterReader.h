//
// Created by anna on 4/22/2017.
//

#ifndef LAB5_CLUSTERREADER_H
#define LAB5_CLUSTERREADER_H

#include <string>
#include "Cluster.h"

class ClusterReader {
public:
    ClusterReader(const std::string& fileName):_fileName(fileName),_pointsDimension(0){}
    bool loadClusters();
    const std::vector<Cluster>& getClusters() const { return _clusters; }
    size_t getPointsDimension() const { return _pointsDimension; }

private:
    bool loadPoints(std::ifstream& in, std::string& line);

private:
    std::string _fileName;
    std::vector<Cluster> _clusters;
    size_t _pointsDimension;
};


#endif //LAB5_CLUSTERREADER_H
