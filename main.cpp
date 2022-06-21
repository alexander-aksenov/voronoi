#include <iostream>
#include <vector>
#include <utility>
#include <random_points.h>
#include <bmp_writer.h>

static void
printPoints(std::vector<std::pair<unsigned int, unsigned int>>& points)
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
    unsigned int width = strtoul(argv[1], &end, 10);
    unsigned int height = strtoul(argv[2], &end, 10);
    unsigned int num = strtoul(argv[3], &end, 10);

    std::cout << "Num values are " << width << " " << height << " " << num << std::endl;

    std::vector<std::pair<unsigned int, unsigned int>> points;

    if (argc == 5) {
        unsigned int seed = strtoul(argv[4], &end, 10);
        std::cout << "With seed " << seed << std::endl;

        points = RandomPoints::generate(width, height, num, seed);
    } else {
        points = RandomPoints::generate(width, height, num);
    }

    if (argc == 6) {
        std::string filename(argv[5]);
        BmpWriter bw(filename, width, height);
        bw.addDots(points);
        bw.writeFile();
    } else {
        printPoints(points);
    }

    return 0;
}
