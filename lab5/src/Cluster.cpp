//
// Created by anna on 4/22/2017.
//

#include "include/Cluster.h"
#include <cstdlib>
#include <limits>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::string;


Cluster::Cluster(size_t idCluster) : _idCluster(idCluster)
{
}

bool Cluster::isInCluster(const Point& point) const
{
    for (size_t i=0; i<_points.size(); i++)
    {
        if (_points[i]==point) return true;
    }
    return false;
}


void Cluster::print() const
{
    cout << "Cluster " << _idCluster + 1 << endl;
    for(vector<Point>::size_type j = 0; j < _points.size(); j++)
    {
        cout << "Point " << _points[j].getID() + 1 << ": ";
        _points[j].print();
    }
}

double Cluster::sumSquaresPointToCluster(const Point& point) const
{
    double sum(0.0);
    for(vector<Point>::size_type j = 0; j < _points.size(); j++)
    {
        sum += _points[j].squaredDistance(point);
    }
    return sum;
}

double Cluster::avgEuclideanPointToCluster(const Point& point) const
{
    double sum(0.0);
    for(vector<Point>::size_type j = 0; j < _points.size(); j++)
    {
        sum += _points[j].euclideanDistance(point);
    }
    return sum/_points.size();
}

Point Cluster::getCenterPoint() const
{
    if (_points.size()==0) return Point(vector<double>());
    Point avg(_points[0]);

    for(vector<Point>::size_type j = 1; j < _points.size(); j++)
    {
        avg=avg+_points[j];
    }
    avg/=(double)_points.size();
    return avg;
}

void Cluster::getMajority(std::string& name, size_t& count) const
{
    std::vector<string> names;
    std::vector<size_t> counts;
    for(vector<Point>::size_type j = 0; j < _points.size(); j++)
    {
        std::vector<string>::iterator it = std::find(names.begin(),names.end(),_points[j].getName());
        if (it==names.end()) //no name yet
        {
            names.push_back(_points[j].getName());
            counts.push_back(1);
        }
        else
        {
            size_t pos=(size_t)(it - names.begin());
            counts[pos]++;
        }
    }
    size_t max=std::numeric_limits<size_t>::min();
    size_t index=0;
    for (size_t sz=0; sz<counts.size();sz++) {
        if (max < counts[sz]) {
            max = counts[sz];
            index = sz;
        }
    }
    name= names[index];
    count =max;
}