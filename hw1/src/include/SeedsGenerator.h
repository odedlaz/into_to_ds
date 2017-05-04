#ifndef HW1_SEEDSGENERATOR_H
#define HW1_SEEDSGENERATOR_H

#include <cstdlib>

class SeedsGenerator {
private:
    static const unsigned _seed;
public:
    /**
     * init
     *
     *  Initializes the seed generator with a given seed
     *
     */
    static void init() { srand(_seed); }

    /**
     * getRandom
     *
     * get a random number from a given range
     *
     * @param min size_t the minimum number to be returned
     * @param max size_t the maximum number to be returned
     * @return A random number between min and max
     */
    static size_t getRandom(size_t min, size_t max) { return min + rand() % (max - min); }
};


#endif //HW1_SEEDSGENERATOR_H
