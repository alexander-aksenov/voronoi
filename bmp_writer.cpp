#include <stdexcept>
#include <bmp_writer.h>

enum {
    BYTES_PER_PIXEL = 3,
    FILE_HEADER_SIZE = 14,
    INFO_HEADER_SIZE = 40,
};

unsigned int
BmpWriter::getWidthInBytes()
{
    return width * BYTES_PER_PIXEL;
}

unsigned int
BmpWriter::getPaddingSize()
{
    return (4 - (getWidthInBytes()) % 4) % 4;
}

void
BmpWriter::writeFileHeader(std::ofstream &out)
{
    unsigned int stride = getWidthInBytes() + getPaddingSize();
    unsigned int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);
    unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    out.write((const char*) &fileHeader, FILE_HEADER_SIZE);
}

void
BmpWriter::writeInfoHeader(std::ofstream &out)
{
    unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

    out.write((const char*) &infoHeader, INFO_HEADER_SIZE);
}

void
BmpWriter::writeImage(std::ofstream &out)
{
    static const unsigned char padding[] = {0, 0, 0};

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            const unsigned char dot[] = {
                std::get<0>(img[x][y]),
                std::get<1>(img[x][y]),
                std::get<2>(img[x][y]),
            };
            out.write((const char *) &dot, BYTES_PER_PIXEL);
        }
        out.write((const char *) &padding, getPaddingSize());
    }
}

void
BmpWriter::addDots(const std::vector<std::pair<unsigned int, unsigned int>> &dots)
{
    for (auto dot : dots)
        img[dot.first][dot.second] = std::make_tuple(255, 255, 255);
}

void
BmpWriter::showVoronoi(const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &diagram)
{
    for (unsigned int x = 0; x < diagram.size(); x++) {
        for (unsigned int y = 0; y < diagram[0].size(); y++) {
            img[x][y] = std::make_tuple((diagram[x][y].first % 12) * 20, (diagram[x][y].second % 12) * 20, 0);
        }
    }
}

void
BmpWriter::writeFile()
{
    std::ofstream out(filename.c_str(), std::ios::out | std::ios::binary);
    if (!out)
        throw std::invalid_argument("Could not open " + filename + " for write");

    writeFileHeader(out);
    writeInfoHeader(out);
    writeImage(out);

    out.close();
}
