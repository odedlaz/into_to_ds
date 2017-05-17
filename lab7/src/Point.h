//
// Created by annabel@staff.technion.ac.il on 5/9/17.
//

#ifndef LAB6_POINT_H
#define LAB6_POINT_H

#include <vector>
#include <string>
#include <algorithm>


class Point {
public:
    Point(size_t size):_values(size,0.0){}
    void setClass(const std::string& classValue){ _class=classValue; }
    const std::string& getClass() const { return _class;}
    void setPrediction(const std::string& prediction){ _prediction=prediction; }
    const std::string& getPrediction() const{ return _prediction; }
    const double& operator[]( size_t index) const { return _values[index]; }
    double& operator[](size_t index) { return _values[index];}
    Point operator-(const Point& otherPoint) const;
    Point operator/(const Point& otherPoint) const;
    size_t getDimension()const { return _values.size(); }
    void setValues(const std::vector<double>& values){ _values = values; }
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
private:
    std::string _class;
    std::string _prediction;
    std::vector<double> _values;
};


#endif //LAB7_POINT_H
