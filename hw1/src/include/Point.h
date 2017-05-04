#ifndef HW1_POINT_H
#define HW1_POINT_H

#include <iostream>
#include <vector>
#include <string>


class Point {
private:
    size_t _idPoint;
    int _idCluster;
    std::vector<double> _values;
    std::string _name;
public:
    static const int _notAssignedToCluster;

public:
    /**
     * Constructor
     *
     * constructs a Point
     *
     * @param id_point an id that will represent this point
     * @param values a vector<double> that holds the point's coordinates
     * @param name a name to represent this point
    **/
    Point(size_t id_point, const std::vector<double> &values, const std::string &name = "");

    /**
     * getID
     *
     * @return size_t The id of this point
     */
    size_t getID() const { return _idPoint; }

    /**
     * setCluster
     *
     * Sets the cluster for this point
     *
     * @param id_cluster int The cluster ID
     */
    void setCluster(int id_cluster) { _idCluster = id_cluster; }

    /**
     * getCluster
     *
     * @return size_t The cluster id for this point
     */
    int getCluster() const { return _idCluster; }

    /**
     * getName
     *
     * @return std::string The name of this point
     */
    const std::string &getName() const { return _name; }

    /**
     * attributePoints
     *
     * Iterate the points in the dataset and attribute them to the right cluster
     *
     * @return A flag indicating if the points have been attributed
     */
    void setName(const std::string &name) { _name = name; }

    /**
     * getDimension
     *
     * @return size_t this points dimension
     */
    size_t getDimension() const { return _values.size(); }

    /**
     * getValue
     *
     * get the point value at a given dimension
     *
     * @param dim size_t the points dimension to extract the value from
     * @return double the value at the given dimension
     */
    double getValue(size_t dim) const { return _values[dim]; }

    /**
     * setValue
     *
     * sets a point value at a given dimension
     *
     * @param value double the new value
     * @param dim size_t the points dimension to change the value to
     */
    void setValue(double value, size_t dim) { _values[dim] = value; }

    /**
     * euclideanDistance
     *
     * Calculate the euclidean distance between two points
     *
     * @param pointA Point& A point
     * @param pointB Point& Another point
     * @return The euclidean distance between point A and point B
     */
    static double euclideanDistance(const Point &pointA, const Point &pointB);

    /**
     * operator<<
     *
     * An implementation of the << operator
     * That dumps the dimension values of this point into a given stream
     *
     * @param os std::ostream& A stream to write the output to
     * @param point Point& A point to dump it's data
     * @return std::ostream& The stream that was sent
     */
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

#endif //LAB2_POINT_H
