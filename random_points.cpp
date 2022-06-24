#include <random_points.h>

std::pair<unsigned int, unsigned int>
RandomPoints::getPoint(std::mt19937 &gen, std::uniform_int_distribution<unsigned int> &w_dist,
                       std::uniform_int_distribution<unsigned int> &h_dist)
{
    return std::make_pair(w_dist(gen), h_dist(gen));

}

std::vector<std::pair<unsigned int, unsigned int>>
RandomPoints::generate(unsigned int width, unsigned int height, unsigned int num, unsigned int seed)
{
    std::vector<std::pair<unsigned int, unsigned int>> res(num);

    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned int> w_distrib(1, width - 1);
    std::uniform_int_distribution<unsigned int> h_distrib(1, height - 1);

    for (auto it = res.begin(); it != res.end(); it++)
        *it = getPoint(gen, w_distrib, h_distrib);

    return res;
}

std::vector<std::pair<unsigned int, unsigned int>>
RandomPoints::generate(unsigned int width, unsigned int height, unsigned int num)
{
    std::random_device rd;

    return generate(height, width, num, rd());
}
