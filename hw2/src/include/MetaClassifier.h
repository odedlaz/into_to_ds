#ifndef SRC_METACLASSIFER_H
#define SRC_METACLASSIFER_H


#include "Classifier.h"
#include "Perceptron.h"
#include "KNNClassifier.h"


// a pair of weight index and value
typedef std::pair<int,double> WeightPair;

class MetaClassifier : public Classifier {
    friend class Perceptron;

public:
    /**
     * MetaClassifier constructor.
     * Creates Perceptron(alpha as 0.0001, and epoch as 5000) and KNN(with k and distance) Instances.
     * @param k size_t Number of neighbours to run with KNN's prediction
     * @param size size_t Dimension of point in the dataset
     * @param distance Distance method to calculate distance with
     */
    MetaClassifier(size_t k, size_t size, Distance *&distance);

    /**
     * Trains the MetaClassifier.
     * Uses Perceptron weights to determinate which feature is the least significant, and removes lowest X features.
     * sends the trimmed dataset to KNN classifier.
     * @param points vector<Point> contains the original dataset
     * @return boolean result indicates if the train was successful
     */
    virtual bool train(const std::vector<Point> &points);

    /**
     * Predicts the given point class.
     * trims the point to be predicted using the least significant weights, and uses KNN predict.
     * @param newPoint Point to be predicted
     */
    virtual void predict(Point &newPoint) const;

    virtual ~MetaClassifier();


private:
    Perceptron *_perceptron;
    KNNClassifier *_knn;
    size_t _k;
    size_t _size;
    std::vector<Point> _training;
    Distance *_distance;
    std::vector<WeightPair> _weights;

    /**
     * Trims the point's features using the calculated weights, to remove least significant features.
     * @param point Point that holds all the features
     * @param newPoint Point to hold the trimmed features.
     */
    void setPointAccordingToWeights(const Point &point, Point &newPoint) const;
};


#endif //SRC_METACLASSIFER_H
