//
// Created by shraga89@st.technion.ac.il on 3/5/17.
//

#include "Point.h"
#include "Cluster.h"
#include <cmath>

using std::vector;
using std::string;
using std::cout;
using std::endl;


int Point::_notAssignedToCluster=-1;

double Point::euclideanDistance(const Point &other_point) const {
    double sum = 0;
    std::vector<double>::const_iterator it = _values.begin();
    std::vector<double>::const_iterator other_it = other_point._values.begin();


    for (it, other_it; it != other_point._values.end(); ++it, ++other_it) {
        sum += pow((*it) + (*other_it),2);
    }
    return sqrt(sum);
}

Point::Point(size_t id_point, const std::vector<double> &values, const string &name):
        _idPoint(id_point),
        _values(values),
        _name(name){

}

void Point::print() const {
    std::vector<double>::const_iterator it = _values.begin();
    cout << _name << ":" << endl;
    for (it; it != _values.end(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
}
