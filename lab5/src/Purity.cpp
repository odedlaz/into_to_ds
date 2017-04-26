//
// Created by annabel@staff.technion.ac.il on 4/24/17.
//

#include "include/Purity.h"
using std::vector;
using std::string;

double Purity::calculate() const
{
    double totalMatches(0.0);
    double all(0.0);
    for (vector<Cluster>::size_type sz=0; sz<_clusters.size(); sz++)
    {
        string name;
        size_t max(0);
        _clusters[sz].getMajority(name, max);
        totalMatches+=max;
        all+=_clusters[sz].getSize();

    }
    return totalMatches/all;
}