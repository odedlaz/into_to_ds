#ifndef HW1_TESTS_H
#define HW1_TESTS_H

#include <vector>
#include <string>
#include "../../include/Point.h"

class Tests {

public:
    enum eTests {
        eTestKMeans = 0, eTestKMedoids, eTestKMeansSSE, eTestKMedoidsSSE, numOfTests
    };
    static const std::string testNames[numOfTests];

public:
    static void testKMeans(unsigned K, unsigned max_iterations, const std::vector<Point> &points);

    static void testKMedoids(unsigned K, unsigned max_iterations, const std::vector<Point> &points);

    static void testKMeansSSE(unsigned K, unsigned max_iterations, const std::vector<Point> &points);

    static void testKMedoidsSSE(unsigned K, unsigned max_iterations, const std::vector<Point> &points);

private:
    Tests();

};

#endif //HW1_TESTS_H
