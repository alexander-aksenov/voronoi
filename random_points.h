#ifndef RANDOM_POINTS_H
#define RANDOM_POINTS_H

#include <vector>
#include <utility>
#include <random>

class RandomPoints {
        static std::pair<unsigned int, unsigned int>
            getPoint(std::mt19937 &gen, std::uniform_int_distribution<unsigned int> &w_dist,
                     std::uniform_int_distribution<unsigned int> &h_dist);

    public:
        static std::vector<std::pair<unsigned int, unsigned int>>
            generate(unsigned int width, unsigned int height, unsigned int num);
        static std::vector<std::pair<unsigned int, unsigned int>>
            generate(unsigned int width, unsigned int height, unsigned int num, unsigned int seed);
};

#endif /* RANDOM_POINTS_H */
