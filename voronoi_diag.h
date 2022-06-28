#ifndef VORONOI_DIAG_H
#define VORONOI_DIAG_H

#include <vector>
#include <utility>
#include <point.h>

/* Dumb Voronoi based on flooding algorithm */
/* TODO get not (only) colorful picture, but line coordinates */

class VoronoiDiagram {
        static bool isNewSeedNearer(const Point &old_seed, const Point &new_seed, const Point &point);
        static bool changeNeighboursIfNeed(std::vector<std::vector<Point>> &img, Point &point, unsigned int offset);
        static void buildDiagram(std::vector<std::vector<Point>> &img, std::vector<Point> &points);
        static bool pointIsEdge(std::vector<std::vector<Point>> &img, unsigned int x, unsigned int y);

    public:
        static std::vector<std::vector<Point>>
            makeVoronoiDiagram(unsigned int width, unsigned int height, std::vector<Point> &points);
        static std::vector<std::vector<bool>>
            binarizeDiagram(std::vector<std::vector<Point>> &img);
};

#endif /* VORONOI_DIAG_H */
