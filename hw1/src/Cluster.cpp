//
// Created by shraga89@st.technion.ac.il on 3/5/17.
//
#include "include/Cluster.h"
#include <cmath>

using std::vector;
using std::string;
using std::cout;
using std::endl;


bool Cluster::removePoint(size_t pointID)
{
   for(vector<Point>::size_type i = 0; i < _points.size(); i++)
    {
        if(_points[i] == pointID)
        {
            _points.erase(_points.begin() + i);
            return true;
        }
    }
    return false;
}

void Cluster::print(const vector<Point>& allPoints) const
{
    cout << "Cluster " << _idCluster + 1 << endl;
    for(vector<Point>::size_type j = 0; j < _points.size(); j++)
    {
        cout << "Point " << allPoints[_points[j]].getID() + 1 << ": ";
        allPoints[_points[j]].print();
    }

    cout << "Cluster prototype: ";
    _prototype.print();
}
