#ifndef BMP_WRITER_H
#define BMP_WRITER_H

#include <string>
#include <fstream>
#include <image_generator.h>


class BmpWriter {
        const std::string filename;

        const ImageGenerator &img;

        unsigned int getWidthInBytes();
        unsigned int getPaddingSize();
        void writeFileHeader(std::ofstream &out);
        void writeInfoHeader(std::ofstream &out);
        void writeImage(std::ofstream &out);

    public:
        BmpWriter(const std::string &filename, const ImageGenerator &img) :
            filename(filename), img(img) {}

        void writeFile();
};

#endif /* BMP_WRITER_H */
