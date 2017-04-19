#ifndef HW1_SEEDSGENERATOR_H
#define HW1_SEEDSGENERATOR_H

#include <cstdlib>

class SeedsGenerator {
private:
    static const unsigned _seed;
public:
    static void init() { srand(_seed); }

    static size_t getRandom(size_t min, size_t max) { return min + rand() % (max - min); }

};


#endif //HW1_SEEDSGENERATOR_H
