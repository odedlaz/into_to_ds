//
// Created by anna on 4/22/2017.
//

#ifndef LAB5_POINT_H
#define LAB5_POINT_H

#include <iostream>
#include <vector>
#include <string>


class Point
{
private:
    size_t _idPoint;
    std::vector<double> _values;
    std::string _name;

public:
    static const std::string _no_name;
    static const size_t _no_id;

public:
    Point(const std::vector<double>& values, const std::string& name=_no_name, size_t id_point=_no_id);
    Point(size_t dimension);
    size_t getID() const { return _idPoint; }
    const std::string& getName() const { return _name; }
    double euclideanDistance( const Point &other_point ) const;
    double squaredDistance( const Point &other_point ) const;
    bool operator==(const Point &other_point ) const;
    void print() const;
    void operator/=(double denominator);
    friend Point operator+(const Point& point1, const Point& point2);

};





#endif //LAB5_POINT_H
