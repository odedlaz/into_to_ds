//
// Created by shraga89@st.technion.ac.il on 5/11/17.
//

#include "ZNormalizer.h"
#include "math.h"

bool ZNormalizer::init(const std::vector<Point> &points) {
    if (points.empty())
        return false;
    for( size_t i = 0; i < points[0].getDimension(); i++)
    {
        double sumFeature(0.0);
        for (std::vector<Point>::size_type pi=0; pi<points.size(); pi++){
            sumFeature += points[pi][i];
        }
        mean[i]=sumFeature/(double)points.size();
        double varFeature(0.0);
        for (std::vector<Point>::size_type pi=0; pi<points.size(); pi++){
            varFeature += pow((points[pi][i] - mean[i]),2.0);
        }
        sd[i]=sqrt(varFeature);
    }
    return true;
}

void ZNormalizer::normalize(const Point &oldPoint, Point &newPoint) {
    newPoint=(oldPoint-mean)/sd;
}