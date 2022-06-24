#include <cmath>
#include <voronoi_diag.h>


double
VoronoiDiagram::getDistance(std::pair<unsigned int, unsigned int> p1,
                            std::pair<unsigned int, unsigned int> p2)
{
    unsigned int x_diff = p1.first > p2.first ? p1.first - p2.first : p2.first - p1.first;
    unsigned int y_diff = p1.second > p2.second ? p1.second - p2.second : p2.second - p2.second;

    return std::hypot(p1.first - p2.first, p1.second - p2.second);
}

bool
VoronoiDiagram::isNewSeedNearer(std::pair<unsigned int, unsigned int> old_seed,
                                std::pair<unsigned int, unsigned int> new_seed,
                                std::pair<unsigned int, unsigned int> point)
{
    unsigned long new_d = std::pow((long)new_seed.first - (long)point.first, 2) + std::pow((long)new_seed.second - (long)point.second, 2);
    unsigned long old_d = std::pow((long)old_seed.first - (long)point.first, 2) + std::pow((long)old_seed.second - (long)point.second, 2);
    return new_d < old_d;
}

bool
VoronoiDiagram::changeNeighboursIfNeed(std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &img,
                                       std::pair<unsigned int, unsigned int> &point,
                                       unsigned int offset)
{
    bool has_changes = false;
    unsigned int from_x = point.first >= offset ? point.first - offset : 0;
    unsigned int till_x = img.size() - point.first - 1 >= offset ? point.first + offset : img.size() - 1;

    unsigned int from_y = point.second >= offset ? point.second - offset : 0;
    unsigned int till_y = img[0].size() - point.second - 1 >= offset ? point.second + offset : img[0].size() - 1;

    /* Top line */
    for (unsigned int x = from_x; x <= till_x; x++) {
        if (img[x][from_y].first == 0 && img[x][from_y].second == 0) {
            img[x][from_y] = point;
            has_changes = true;
        } else {
            if (isNewSeedNearer(img[x][from_y], point, std::make_pair(x, from_y))) {
                img[x][from_y] = point;
                has_changes = true;
            }
        }
    }

    /* Bottom line */
    for (unsigned int x = from_x; x <= till_x; x++) {
        if (img[x][till_y].first == 0 && img[x][till_y].second == 0) {
            img[x][till_y] = point;
            has_changes = true;
        } else {
            if (isNewSeedNearer(img[x][till_y], point, std::make_pair(x, till_y))) {
                img[x][till_y] = point;
                has_changes = true;
            }
        }
    }

    /* Left line */
    for (unsigned int y = from_y; y <= till_y; y++) {
        if (img[from_x][y].first == 0 && img[from_x][y].second == 0) {
            img[from_x][y] = point;
            has_changes = true;
        } else {
            if (isNewSeedNearer(img[from_x][y], point, std::make_pair(from_x, y))) {
                img[from_x][y] = point;
                has_changes = true;
            }
        }
    }

    /* Right line */
    for (unsigned int y = from_y; y <= till_y; y++) {
        if (img[till_x][y].first == 0 && img[till_x][y].second == 0) {
            img[till_x][y] = point;
            has_changes = true;
        } else {
            if (isNewSeedNearer(img[till_x][y], point, std::make_pair(till_x, y))) {
                img[till_x][y] = point;
                has_changes = true;
            }
        }
    }

    return has_changes;
}

void
VoronoiDiagram::buildDiagram(std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &img,
                             std::vector<std::pair<unsigned int, unsigned int>> &points)
{
    bool has_changes = false;
    unsigned int max = img.size() > img[0].size() ? img.size() : img[0].size();

    for (unsigned int i = 0; i < max; i++) {
        has_changes = false;
        for (unsigned int p = 0; p < points.size(); p++) {
            bool changes = changeNeighboursIfNeed(img, points[p], i);
            has_changes = has_changes || changes;
        }



        if (!has_changes)
            break;
    }
}

std::vector<std::vector<std::pair<unsigned int, unsigned int>>>
VoronoiDiagram::makeVoronoiDiagram(unsigned int width, unsigned int height,
                                   std::vector<std::pair<unsigned int, unsigned int>> &points)
{
    std::vector<std::vector<std::pair<unsigned int, unsigned int>>> img(width, std::vector<std::pair<unsigned int, unsigned int>>(height, std::make_pair(0, 0)));
    buildDiagram(img, points);

    return img;
}
