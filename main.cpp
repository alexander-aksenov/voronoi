#include <iostream>
#include <vector>
#include <utility>
#include <random_points.h>

static void
printPoints(std::vector<std::pair<unsigned long, unsigned long>>& points)
{
    for (auto point : points)
        std::cout << point.first << ", " << point.second << std::endl;
}

int
main(int argc, char** argv)
{
    if (argc < 4) {
        std::cerr << "Number of args less than 4" << std::endl;
        return -1;
    }

    char *end;
    unsigned long width = strtoul(argv[1], &end, 10);
    unsigned long height = strtoul(argv[2], &end, 10);
    unsigned long num = strtoul(argv[3], &end, 10);

    std::cout << "Num values are " << width << " " << height << " " << num << std::endl;

    std::vector<std::pair<unsigned long, unsigned long>> res;

    if (argc == 5) {
        unsigned long seed = strtoul(argv[4], &end, 10);
        std::cout << "With seed " << seed << std::endl;

        res = RandomPoints::generate(width, height, num, seed);
    } else {
        res = RandomPoints::generate(width, height, num);
    }

    printPoints(res);


    return 0;
}
