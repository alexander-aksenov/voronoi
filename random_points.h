#ifndef RANDOM_POINTS_H
#define RANDOM_POINTS_H

#include <vector>
#include <random>
#include <point.h>

class RandomPoints {
        static Point
            getPoint(std::mt19937 &gen, std::uniform_int_distribution<unsigned int> &w_dist,
                     std::uniform_int_distribution<unsigned int> &h_dist);

    public:
        static std::vector<Point>
            generate(unsigned int width, unsigned int height, unsigned int num);
        static std::vector<Point>
            generate(unsigned int width, unsigned int height, unsigned int num, unsigned int seed);
};

#endif /* RANDOM_POINTS_H */
