#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <vector>
using std::vector;
#include <random>
#include <time.h>


/*
 * There are 12 possible moves (F, F', B, B', U, U', D, D', L, L', R, R') [0,11] is the range for valid turns
 *          - 20 moves are required to get a good scramble (God's Number)
 *          - I will use 100 because that is what Korf uses in his paper
 *          - getScramble will generate a vector of 25 ints [0,11] that represent the turns to scramble
 *          - doScramble will actually implement the generated scramble sequence starting at the back of the vector
 */

class RandomGenerator
{
public:
    RandomGenerator() {}
    vector<int> getRand(int numMoves) {
        vector<int> randNums;
        time_t timer;
        struct tm y2k = {0};
        double seconds;

        y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
        y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
        time(&timer);

        seconds = difftime(timer,mktime(&y2k));

        std::mt19937 rng;
        rng.seed(seconds);
        std::uniform_int_distribution<std::mt19937::result_type> uint_dist10(0,17);

        for(int i = 0; i < numMoves; i++) {
            randNums.push_back(uint_dist10(rng));
        }

        return randNums;
    }

};

#endif // RANDOMGENERATOR_H
