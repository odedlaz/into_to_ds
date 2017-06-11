#ifndef CLASSIFICATION_POINT_H
#define CLASSIFICATION_POINT_H

#include <string>
#include <vector>

class Point {

public:
    Point(size_t size) : _values(size, 0.0) {}

    /**
     * sets the class of a point
     * @param classValue string contains the class name
     */
    void setClass(const std::string &classValue) { _class = classValue; }

    /**
     * gets the class of a point
     * @return string contains the class name
     */
    const std::string &getClass() const { return _class; }

    /**
     * sets the prediction for a point
     * @param prediction string represent the predicted class
     */
    void setPrediction(const std::string &prediction) { _prediction = prediction; }

    /**
     * gets the prediction of a point
     * @return string represent the predicted class
     */
    const std::string &getPrediction() const { return _prediction; }

    const double &operator[](size_t index) const { return _values[index]; }

    double &operator[](size_t index) { return _values[index]; }

    /**
     * get the dimension of a point (aka amount of features)
     * @return size_t value of dimension
     */
    size_t getDimension() const { return _values.size(); }

    /**
     * set the values of a point.
     * @param values vector<double> contains the values to be assigned to the point.
     */
    void setValues(const std::vector<double> &values) { _values = values; }

private:
    std::string _class;
    std::string _prediction;
    std::vector<double> _values;

};


#endif //CLASSIFICATION_POINT_H
