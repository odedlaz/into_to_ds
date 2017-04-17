//
// Created by shraga89@st.technion.ac.il on 3/5/17.
//
#include "Cluster.h"

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

Cluster::Cluster(int idCluster, const Point &point):
        _idCluster(idCluster),
        _prototype(point) {

}

void Cluster::addPoint(size_t pointID) {
   _points.push_back(pointID);
}

void Cluster::updatePrototype(const std::vector<Point> &allPoints) {
    double sum = 0;
    std::vector<Point>::const_iterator it = allPoints.begin();

    for (it; it != allPoints.end(); ++it) {
        double candidateSum = 0;
        std::vector<Point>::const_iterator inner_it = allPoints.begin();

        for (inner_it; inner_it != allPoints.end(); ++inner_it) {
            // don't calculate distance from self
            if ((*it).getName() == (*inner_it).getName()) {
                continue;
            }

            // add the distance from self to other point
            candidateSum += (*it).euclideanDistance(*inner_it);
        }

        // if we don't have a sum yet, use the first calculation
        // otherwise, use the minimal one.
        if (it == allPoints.begin() || candidateSum < sum) {
            sum = candidateSum;
            _prototype = (*it);
        }
    }
}

double Cluster::getDistanceToPrototype(const Point &point) const {
    return _prototype.euclideanDistance(point);
}

