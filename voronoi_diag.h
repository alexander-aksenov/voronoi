#ifndef VORONOI_DIAG_H
#define VORONOI_DIAG_H

#include <vector>
#include <utility>

/* Dumb Voronoi based on flooding algorithm */
/* TODO get not (only) colorful picture, but line coordinates */

class VoronoiDiagram {
        static double getDistance(std::pair<unsigned int, unsigned int> p1, std::pair<unsigned int, unsigned int> p2);
        static bool isNewSeedNearer(std::pair<unsigned int, unsigned int> old_seed,
                                    std::pair<unsigned int, unsigned int> new_seed,
                                    std::pair<unsigned int, unsigned int> point);
        static bool changeNeighboursIfNeed(std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &img,
                                           std::pair<unsigned int, unsigned int> &point,
                                           unsigned int offset);
        static void buildDiagram(std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &img,
                                 std::vector<std::pair<unsigned int, unsigned int>> &points);
        static bool pointIsEdge(std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &img,
                                unsigned int x, unsigned int y);

    public:
        static std::vector<std::vector<std::pair<unsigned int, unsigned int>>>
            makeVoronoiDiagram(unsigned int width, unsigned int height,
                               std::vector<std::pair<unsigned int, unsigned int>> &points);
        static std::vector<std::vector<bool>>
            binarizeDiagram(std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &img);
};

#endif /* VORONOI_DIAG_H */
