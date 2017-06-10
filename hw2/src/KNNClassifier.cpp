#include <cstddef>
#include "include/KNNClassifier.h"
#include "include/Distance.h"
#include "include/Point.h"
#include <math.h>
#include <algorithm>

using std::string;
using std::vector;

KNNClassifier::KNNClassifier(size_t &size, Distance *&distance) : _size(size), _distance(distance) {

}

void KNNClassifier::predict(Point &newPoint) const {
    std::vector<std::pair<string, double> > distances;
    //we keep the first k distances as starting neighbours
    for (std::vector<Point *>::size_type sz = 0; sz < _size; sz++) {
        distances.push_back(std::pair<string, double>(_data[sz].getClass(), _distance->calculate(_data[sz], newPoint)));
    }

    for (std::vector<Point *>::size_type sz = _size; sz < _data.size(); sz++) {
        double max = 0;
        size_t max_pos = maxDistIndex(distances, max);
        double currentDist = _distance->calculate(_data[sz], newPoint);
        if (currentDist < max) {
            distances[max_pos].first = _data[sz].getClass();
            distances[max_pos].second = currentDist;
        }
    }
    newPoint.setPrediction(getMajorityClass(distances));
}

bool KNNClassifier::train(const std::vector<Point> &points) {
    if (points.size() < _size) {
        return false;
    }

    _data = points;

    return true;
}


size_t KNNClassifier::maxDistIndex(const std::vector<std::pair<string, double> > &distances, double &max) const {
    size_t index = 0;
    max = distances[index].second;
    for (size_t sz = 0; sz < distances.size(); sz++) {
        if (max < distances[sz].second) {
            max = distances[sz].second;
            index = sz;
        }
    }
    return index;
}

const std::string KNNClassifier::getMajorityClass(const std::vector<std::pair<std::string, double> > &distances) const {
    vector<string> classes;
    vector<size_t> counts;
    for (size_t sz = 0; sz < distances.size(); sz++) {
        size_t found = 0;
        //we look for the class
        for (; found < classes.size(); found++) {
            if (classes[found] == distances[sz].first) {
                counts[found]++;
                break;
            }
        }
        //we didn't find the class
        if (found == classes.size()) {
            classes.push_back(distances[sz].first);
            counts.push_back(1);
        }
    }
    vector<size_t>::iterator it = std::max_element(counts.begin(), counts.end());
    size_t index = (size_t) (it - counts.begin());
    return classes[index];
}

