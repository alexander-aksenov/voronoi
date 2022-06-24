#include <iostream>
#include <vector>
#include <utility>
#include <random_points.h>
#include <bmp_writer.h>
#include <voronoi_diag.h>

static void
printPoints(std::vector<std::pair<unsigned int, unsigned int>>& points)
{
    for (auto point : points)
        std::cout << point.first << ", " << point.second << std::endl;
}

static void
printVoronoi(std::vector<std::vector<std::pair<unsigned int, unsigned int>>>& diag)
{
    for (unsigned int y = 0; y < diag[0].size(); y++) {
        for (unsigned int x = 0; x < diag.size(); x++) {
            std::cout << diag[x][y].first << "," << diag[x][y].second << " ";
        }
        std::cout << std::endl;
    }
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

    if (argc >= 5) {
        unsigned int seed = strtoul(argv[4], &end, 10);

        if (seed != 0) {
            std::cout << "With seed " << seed << std::endl;

            points = RandomPoints::generate(width, height, num, seed);
        } else {
            points = RandomPoints::generate(width, height, num);
        }
    } else {
        points = RandomPoints::generate(width, height, num);
    }

    auto voronoi = VoronoiDiagram::makeVoronoiDiagram(width, height, points);
    if (argc == 6) {
        std::string filename(argv[5]);
        BmpWriter bw(filename, width, height);
        bw.showVoronoi(voronoi);
        bw.addDots(points);
        bw.writeFile();
    } else {
        printPoints(points);
        printVoronoi(voronoi);
    }

    return 0;
}
