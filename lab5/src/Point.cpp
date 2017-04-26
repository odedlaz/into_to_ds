//
// Created by anna on 4/22/2017.
//

#include "include/Point.h"
#include <cmath>
#include <limits>

using std::vector;
using std::string;
using std::cout;
using std::endl;


const std::string Point::_no_name="";
const size_t Point::_no_id=std::numeric_limits<size_t>::max();

Point::Point(const std::vector<double> &values, const std::string &name, size_t id_point):_values(values),
                                                                                          _name(name),
                                                                                          _idPoint(id_point)
{     }

Point::Point(size_t dimension):_values(dimension,0.0), _name(_no_name),_idPoint(_no_id)
{

}
double Point::euclideanDistance(const Point &other_point) const
{
    return sqrt(squaredDistance(other_point));
}

bool Point::operator==(const Point &other_point ) const
{
    for(  vector<double>::size_type i = 0; i < _values.size(); i++)
    {
        if ( _values[i]!=other_point._values[i]) return false;
    }
    return true;

}
double Point::squaredDistance( const Point &other_point ) const
{
    double sum = 0.0;
    for(  vector<double>::size_type i = 0; i < _values.size(); i++)
    {
        sum += pow( _values[i] - other_point._values[i], 2.0);
    }
    return sum;
}

void Point::print() const
{
    for(vector<double>::size_type i = 0; i < _values.size(); i++)
        cout << _values[i] << " ";

    if ( !_name.empty())
        cout << " - " << _name;

    cout << endl;

}

void Point::operator/=(double denominator)
{
    for(  vector<double>::size_type i = 0; i < _values.size(); i++)
    {
        _values[i]=_values[i]/denominator;
    }
}

Point operator+(const Point& point1, const Point& point2)
{

    //if the points have different dimensions, we have not much to do here, returning an empty point
    if ( point1._values.size()!=point2._values.size() )
        return Point(vector<double>());

    vector<double> values(point1._values);
    for(  vector<double>::size_type i = 0; i < point2._values.size(); i++)
    {
        values[i]+=point2._values[i];
    }
    return Point(values);
}

