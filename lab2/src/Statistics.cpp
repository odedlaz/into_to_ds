//
// Created by shraga89@st.technion.ac.il on 3/16/17.
//

#include "Statistics.h"
#include <iostream>
#include <algorithm>

using std::vector;

double Median(  const vector<double>& xv )
{
    //we create temporal copy of the given constant vector
    vector<double> dv_cpy;
    copy(xv.begin(), xv.end(), back_inserter(dv_cpy) );
    //we sort it to find the median
    sort( dv_cpy.begin(), dv_cpy.end() );
    double median(0.0);
    size_t center = dv_cpy.size()/2;
    if ( dv_cpy.size()%2 == 0)
    {
        median = (dv_cpy[center]+dv_cpy[center+1])/2.0;
    }
    else
    {
        median = dv_cpy[center+1];
    }
    return median;
}



