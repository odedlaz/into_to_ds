#include "include/Point.h"
#include "include/Cluster.h"
#include <cmath>
#include <cstdio>

using std::vector;
using std::string;
using std::cout;
using std::endl;


const int Point::_notAssignedToCluster = -1;


double Point::euclideanDistance(const Point &other_point) const {
    double sum = 0;
    std::vector<double>::const_iterator it = _values.begin();
    std::vector<double>::const_iterator other_it = other_point._values.begin();


    for (it, other_it; it != _values.end(); ++it, ++other_it) {
        sum += pow(*it - *other_it, 2);
    }
    return sqrt(sum);
}

Point::Point(size_t id_point, const std::vector<double> &values, const string &name) :
        _idPoint(id_point),
        _values(values),
        _idCluster(_notAssignedToCluster),
        _name(name) {

}

/*
void Point::print() const {
    std::vector<double>::const_iterator it = _values.begin();
    for (it; it != _values.end(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
}
*/

std::ostream &operator<<(std::ostream &os, const Point &point) {
    for (size_t i = 0; i < point.getDimension(); i++) {
        os << point.getValue(i) << " ";
    }
    return os;
}

