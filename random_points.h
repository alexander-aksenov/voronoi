#ifndef RANDOM_POINTS_H
#define RANDOM_POINTS_H

#include <vector>
#include <utility>
#include <random>

class RandomPoints {
        static std::pair<unsigned long, unsigned long>
            getPoint(std::mt19937 &gen, std::uniform_int_distribution<unsigned long> &w_dist,
                     std::uniform_int_distribution<unsigned long> &h_dist);

    public:
        static std::vector<std::pair<unsigned long, unsigned long>>
            generate(unsigned long width, unsigned long height, unsigned long num);
        static std::vector<std::pair<unsigned long, unsigned long>>
            generate(unsigned long width, unsigned long height, unsigned long num, unsigned long seed);
};

#endif /* RANDOM_POINTS_H */
