#include "include/Point.h"
#include <cmath>

using std::vector;
using std::string;
using std::cout;
using std::endl;

/*
 * Constructor
 * constructs a Point
 * @param id_point an id that will represent this point
 * @param values a vector<double> that holds the point's coordinates
 * @param name a name to represent this point
 * @return a double representing the distance
 */
Point::Point(size_t id_point, const std::vector<double> &values, const std::string &name) : _idPoint(id_point),
                                                                                            _values(values),
                                                                                            _name(name) {}

/*
 * getID
 * Get the ID of this point
 * @return a double representing the distance
 */
size_t Point::getID() const {
    return _idPoint;
}

/*
 * euclideanDistance
 * calculates the euclidean distance between this point and another
 * @param other_point another Point& instance to claculate distance from
 * @return a double representing the distance
 */
double Point::euclideanDistance(const Point &other_point) const {
    double sum = 0.0;

    for (vector<double>::size_type i = 0; i < _values.size(); i++) {
        sum += pow(_values[i] - other_point._values[i], 2.0);
    }

    return sqrt(sum);
}

/*
 * Print
 * Print the point's name and coordinates
 */
void Point::print() const {

    for (vector<double>::size_type i = 0; i < _values.size(); i++)
        cout << _values[i] << " ";

    if (!_name.empty())
        cout << " - " << _name;

    cout << endl;

}
