#include <image_generator.h>

void
ImageGenerator::addDots(const std::vector<Point> &dots)
{
    for (auto dot : dots)
        img[dot.x][dot.y] = std::make_tuple(0, 0, 0);
}

void
ImageGenerator::addVoronoi(const std::vector<std::vector<Point>> &diagram)
{
    for (unsigned int x = 0; x < diagram.size(); x++) {
        for (unsigned int y = 0; y < diagram[0].size(); y++) {
            img[x][y] = std::make_tuple(
                                        (diagram[x][y].x % 12) * 20,
                                        (diagram[x][y].y % 12) * 20,
                                        (diagram[x][y].x % 6 + diagram[x][y].y % 6) * 20);
        }
    }
}

void
ImageGenerator::addBinaryVoronoi(const std::vector<std::vector<bool>> &diagram)
{
    for (unsigned int x = 0; x < diagram.size(); x++) {
        for (unsigned int y = 0; y < diagram[0].size(); y++) {
            if (diagram[x][y])
                img[x][y] = std::make_tuple(0, 0, 0);
        }
    }
}

