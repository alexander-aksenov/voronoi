#ifndef BMP_WRITER_H
#define BMP_WRITER_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>

class BmpWriter {
        std::string filename;
        unsigned int width;
        unsigned int height;

        std::vector<std::vector<bool>> binaryImg;

        unsigned int getWidthInBytes();
        unsigned int getPaddingSize();
        void writeFileHeader(std::ofstream &out);
        void writeInfoHeader(std::ofstream &out);
        void writeImage(std::ofstream &out);

    public:
        BmpWriter(std::string &filename, unsigned int width, unsigned int height) :
            filename(filename), width(width), height(height)
        {
            binaryImg = std::vector<std::vector<bool>>(width, std::vector<bool>(height));
        }

        void addDots(const std::vector<std::pair<unsigned int, unsigned int>> &dots);
        void writeFile();
};

#endif /* BMP_WRITER_H */
