//
// Created by annabel@staff.technion.ac.il on 5/3/17.
//

#include "Classifier.h"
#include "Point.h"
#include <iostream>

using std::cout;
using std::endl;

double Classifier::accuracy(const std::vector<Point>& subset) const
{
    double correct(0.0);
    for(size_t i=0; i<subset.size(); i++)
    {
        if (subset[i].getClass()==subset[i].getPrediction())
            correct++;
    }
    return correct/(double)subset.size();
}