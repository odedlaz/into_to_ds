
#include "KNN.h"
#include "Point.h"
#include <math.h>
#include <algorithm>

using std::string;
using std::vector;

bool KNN::train(const std::vector<Point>& points)
{
    if (points.size()<_k)
        return false;
    _data=points;
    return true;
}


size_t KNN::maxDistIndex(const std::vector< std::pair<string, double> >& distances, double& max) const
{
    size_t index=0;
    max = distances[index].second;
    for (size_t sz=0; sz< distances.size();sz++)
    {
        if (max<distances[sz].second)
        {
            max=distances[sz].second;
            index=sz;
        }
    }
    return index;
}

const std::string KNN::getMajorityClass( const std::vector< std::pair<std::string, double> >& distances) const
{
    vector<string> classes;
    vector<size_t> counts;
    for (size_t sz=0; sz< distances.size();sz++)
    {
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
    vector<size_t>::iterator it= std::max_element(counts.begin(),counts.end());
    size_t index= (size_t)(it-counts.begin());
    return classes[index];
}

double KNN::euclidianDistance(const Point& p1, const Point& p2) const
{
    if (p1.getDimension()!=p2.getDimension())
        return 0;
    double sum = 0.0;
    for( size_t i = 0; i < p1.getDimension(); i++)
    {
        sum += pow( p1[i] - p2[i], 2.0);
    }
    return sqrt(sum);

}

void KNN::predict( Point& newPoint) const
{
    std::vector< std::pair<string, double> > distances;
    //we keep the first k distances as starting neighbours
    for (std::vector<Point*>::size_type sz=0; sz< _k; sz++)
    {
        distances.push_back( std::pair<string, double>(_data[sz].getClass(), euclidianDistance(_data[sz],newPoint)) );
    }

    for (std::vector<Point*>::size_type sz=_k; sz< _data.size(); sz++)
    {
        double max=0;
        size_t max_pos=maxDistIndex(distances,max);
        double currentDist = euclidianDistance(_data[sz],newPoint);
        if ( currentDist < max)
        {
            distances[max_pos].first = _data[sz].getClass();
            distances[max_pos].second = currentDist;
        }
    }
    newPoint.setPrediction(getMajorityClass(distances));
}
