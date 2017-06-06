//
// Created by annabel@staff.technion.ac.il on 5/5/17.
//

#include "Perceptron.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include "Point.h"
#include <numeric>
#include <limits>

using std::vector;
using std::string;
using std::cout;
using std::endl;

double Perceptron::specialInput=-1.0;

void Perceptron::init()
{
    release();
    _ptrWeights=new double[_inputCount];
    initWeights();
}

void Perceptron::release()
{
    //implementation is missing
}

Perceptron::~Perceptron()
{
   //implementation is missing
}

double Perceptron::calculateIn(const Point &point) const
{
   //implementation is missing
}

double Perceptron::getClassID(const Point &point) const
{
    double classID=0;
    if (point.getClass()==_classes[0])
        classID=1.0;
    else if (point.getClass()==_classes[1])
        classID=-1.0;
    return classID;
}

void  Perceptron::updateWeights(const Point &point)
{
   //implementation is missing
}

bool Perceptron::findClass(const std::string& classname) const
{
    for (vector<std::string>::const_iterator it=_classes.begin(); it!=_classes.end();it++)
        if (classname==*it) return true;
    return false;
}


void Perceptron::mapClasses(const std::vector<Point>& points)
{
    for (vector<Point>::const_iterator cit=points.begin(); cit!= points.end(); cit++)
    {
        if (!findClass(cit->getClass()))
            _classes.push_back(cit->getClass());
    }
}

double Perceptron::squaredError(const std::vector<Point>& points) const
{
    //implementation is missing
}

void Perceptron::initWeights()
{
    srand(1);
   for (size_t i=0; i<_inputCount; i++)
   {
        _ptrWeights[i] = (double)rand()/(double)RAND_MAX;
   }
}

void Perceptron::printWeights() const
{
    for (size_t i=0; i<(_inputCount-1); i++)
    {
        cout << _ptrWeights[i] << "," ;
    }

    cout << _ptrWeights[_inputCount-1]<< endl;
}

bool Perceptron::train(const std::vector<Point>& points)
{
    mapClasses(points);
    if (_classes.size()!=2)
        return false;//this is a binary classifier
    double epsilon= pow(10,-10); // small number
    double previousSquaredError=squaredError(points);
    for (size_t iter=0; iter<_epoch; iter++)
    {
        for (vector<Point>::const_iterator cit=points.begin(); cit!= points.end(); cit++)
        {
            updateWeights(*cit);
        }
        double currentSquaredError=squaredError(points);

        if (currentSquaredError>previousSquaredError)
            std::cout << "Alpha is too large" << endl;
        else if (previousSquaredError-currentSquaredError<epsilon)
        {
            std::cout << "Converged at iter: " << iter << endl;
            break;
        }

        previousSquaredError=currentSquaredError;

    }
    return true;
}

void Perceptron::predict( Point& newPoint) const
{
    double in= calculateIn(newPoint);
    if (in > 0)
        newPoint.setPrediction(_classes[0]);
    else
        newPoint.setPrediction(_classes[1]);
}