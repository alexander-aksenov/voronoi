#ifndef IMAGE_GENERATOR_H
#define IMAGE_GENERATOR_H

#include <vector>
#include <tuple>
#include <utility>
#include <point.h>

using ImgDot = std::tuple<unsigned char, unsigned char, unsigned char>;

class ImageGenerator {
        unsigned int width;
        unsigned int height;
        std::vector<std::vector<ImgDot>> img;

    public:
        ImageGenerator(unsigned int width, unsigned int height) : width(width), height(height)
        {
            img = std::vector<std::vector<ImgDot>>(width, std::vector<ImgDot>(height, std::make_tuple(255, 255, 255)));
        }
        void addDots(const std::vector<Point> &dots);
        void addVoronoi(const std::vector<std::vector<Point>> &diagram);
        void addBinaryVoronoi(const std::vector<std::vector<bool>> &diagram);
        void addHeightMap(const std::vector<std::vector<Point>> &map);
        unsigned int getWidth() const { return width; }
        unsigned int getHeight() const { return height; }
        unsigned char getR(unsigned int x, unsigned int y) const { return std::get<0>(img[x][y]); }
        unsigned char getG(unsigned int x, unsigned int y) const { return std::get<1>(img[x][y]); }
        unsigned char getB(unsigned int x, unsigned int y) const { return std::get<2>(img[x][y]); }
};

#endif /* IMAGE_GENERATOR_H */
