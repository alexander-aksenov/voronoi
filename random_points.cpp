#include <random_points.h>

std::pair<unsigned long, unsigned long>
RandomPoints::getPoint(std::mt19937 &gen, std::uniform_int_distribution<unsigned long> &w_dist,
                       std::uniform_int_distribution<unsigned long> &h_dist)
{
    return std::make_pair(w_dist(gen), h_dist(gen));

}

std::vector<std::pair<unsigned long, unsigned long>>
RandomPoints::generate(unsigned long width, unsigned long height, unsigned long num, unsigned long seed)
{
    std::vector<std::pair<unsigned long, unsigned long>> res(num);

    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned long> w_distrib(0, width);
    std::uniform_int_distribution<unsigned long> h_distrib(0, height);

    for (auto it = res.begin(); it != res.end(); it++)
        *it = getPoint(gen, w_distrib, h_distrib);

    return res;
}

std::vector<std::pair<unsigned long, unsigned long>>
RandomPoints::generate(unsigned long width, unsigned long height, unsigned long num)
{
    std::random_device rd;

    return generate(height, width, num, rd());
}
