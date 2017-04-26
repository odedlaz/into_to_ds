#include "include/ClusterReader.h"
#include <fstream>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
using std::istringstream;

bool ClusterReader::loadPoints(std::ifstream &in, std::string &line) {
    string first, second;
    if (!getline(in, line))
        return false;
    std::istringstream iss(line);
    iss >> first >> second;
    while (first == "Point") {
        vector<double> values;
        string vals = line.substr(line.find(":") + 1, line.find(" - ") - line.find(":") - 1);
        std::istringstream iss2(vals);
        while (!iss2.eof()) {
            double dval(0.0);
            iss2 >> dval;
            values.push_back(dval);
        }
        if (_pointsDimension == 0) _pointsDimension = values.size();
        else if (_pointsDimension != values.size())
            return false;
        string name = line.substr(line.find(" - ") + 3, line.size() - line.find(" - ") - 3);
        std::istringstream iss4(second.substr(0, second.size() - 1));
        size_t point_id(0);
        iss4 >> point_id;
        Point p(values, name, point_id);
        _clusters.back().addPoint(p);
        if (!getline(in, line)) break;
        std::istringstream iss3(line);
        iss3 >> first >> second;
    }
    return true;
}


bool ClusterReader::loadClusters() {
    std::ifstream in;
    in.open(_fileName.c_str(), std::ifstream::in);
    std::string line;
    //looking for a cluster
    while (getline(in, line) && (line.find("Cluster") == string::npos)) {}
    //reached here if nothing found or "Cluster" found
    while (line.find("Cluster") != string::npos) {
        if (line.find("prototype") == string::npos) {
            _clusters.push_back(Cluster(_clusters.size()));
        }
        if (!loadPoints(in, line)) return false;
        if ((line.find("Cluster") != string::npos) && (line.find("prototype") != string::npos)) {
            getline(in, line);
        }
    }
    in.close();
    return !_clusters.empty();
}