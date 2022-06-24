#ifndef BMP_WRITER_H
#define BMP_WRITER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>

using BmpDot = std::tuple<unsigned char, unsigned char, unsigned char>;

class BmpWriter {
        std::string filename;
        unsigned int width;
        unsigned int height;

        std::vector<std::vector<BmpDot>> img;

        unsigned int getWidthInBytes();
        unsigned int getPaddingSize();
        void writeFileHeader(std::ofstream &out);
        void writeInfoHeader(std::ofstream &out);
        void writeImage(std::ofstream &out);

    public:
        BmpWriter(std::string &filename, unsigned int width, unsigned int height) :
            filename(filename), width(width), height(height)
        {
            img = std::vector<std::vector<BmpDot>>(width, std::vector<BmpDot>(height, std::make_tuple(255, 255, 255)));
        }

        void addDots(const std::vector<std::pair<unsigned int, unsigned int>> &dots);
        void showVoronoi(const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &diagram);
        void showBinaryVoronoi(const std::vector<std::vector<bool>> &diagram);
        void writeFile();
};

#endif /* BMP_WRITER_H */
