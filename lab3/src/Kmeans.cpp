//
// Created by shraga89@st.technion.ac.il on 3/5/17.
//

#include <cstdlib>
#include "Kmeans.h"
#include <algorithm>


using std::cout;
using std::vector;


size_t KMeans::getIDNearestCenter(const Point& point)
{
    size_t idClusterCenter = 0;
    double min_dist = _clusters[idClusterCenter].getDistanceToPrototype(point);

    for(unsigned i = 1; i < _K; i++)
    {
        double dist = _clusters[i].getDistanceToPrototype(point);
        if(dist < min_dist)
        {
            min_dist = dist;
            idClusterCenter = i;
        }
    }
    return idClusterCenter;
}

void KMeans::run( vector <Point> &points ) {

    if( _K > points.size() )
        return;

    // choose K distinct values for the centers of the clusters
    setRandomSeeds( points );

    unsigned iter = 1;
    bool done(false);

    while( (!done) && (iter<=_maxIterations) )
    {
        // associates each point to the nearest center
        done = attributePoints( points );

        // recalculating the center of each cluster
        for( std::vector<Cluster>::size_type i = 0; i < _K; i++)
        {
            _clusters[i].updatePrototype(points);
        }
        iter++;
    }

    // prints elements of clusters
    for( std::vector<Cluster>::size_type i = 0; i < _K; i++ )
    {
        _clusters[i].print(points);
    }
}

bool KMeans::attributePoints( vector<Point> &points )
{
    bool done = true;
    for(vector<Point>::size_type i = 0; i < points.size(); i++)
    {
        int id_old_cluster = points[i].getCluster();
        size_t id_nearest_center = getIDNearestCenter( points[i] );

        if(id_old_cluster != id_nearest_center)
        {
            if (id_old_cluster != Point::_notAssignedToCluster)
                _clusters[id_old_cluster].removePoint(points[i].getID());

            //a valid cluster ID is a positive number, there is an implicit assumption here that the number of clusters does not exceed the positive value of integer
            points[i].setCluster( (int)id_nearest_center );
            _clusters[id_nearest_center].addPoint( points[i].getID() );
            done = false;
        }
    }
    return done;
}

void KMeans::setRandomSeeds( vector<Point> &points ) {

    vector<vector<Point>::size_type> seedIndexes;
    //we initialize the random number generator to a different seed, to get each time different outputs
    srand( (unsigned int)time(NULL) );

    while (seedIndexes.size() < _K )
    {
        vector<Point>::size_type index_point = rand() % points.size();
        //This is a standard library function that looks for a value inside a vector, if the values is not found - an iterator to the end of vector is returned
        if ( std::find( seedIndexes.begin(), seedIndexes.end(), index_point) == seedIndexes.end())
            seedIndexes.push_back(index_point);
    }
    for (vector<vector<Point>::size_type>::size_type i=0; i< seedIndexes.size(); i++ )
    {
        points[ seedIndexes[i] ].setCluster((int)i);
        Cluster cluster((int)i, points[ seedIndexes[i] ]);
        _clusters.push_back( cluster );
    }
}

