#include <cmath>
#include <voronoi_diag.h>


bool
VoronoiDiagram::isNewSeedNearer(const Point &old_seed, const Point &new_seed, const Point &point)
{
    unsigned long new_d = std::pow((long)new_seed.x - (long)point.x, 2) + std::pow((long)new_seed.y - (long)point.y, 2);
    unsigned long old_d = std::pow((long)old_seed.x - (long)point.x, 2) + std::pow((long)old_seed.y - (long)point.y, 2);
    return new_d < old_d;
}

bool
VoronoiDiagram::changeNeighboursIfNeed(std::vector<std::vector<Point>> &img,
                                       Point &point, unsigned int offset)
{
    bool has_changes = false;
    unsigned int from_x = point.x >= offset ? point.x - offset : 0;
    unsigned int till_x = img.size() - point.x - 1 >= offset ? point.x + offset : img.size() - 1;

    unsigned int from_y = point.y >= offset ? point.y - offset : 0;
    unsigned int till_y = img[0].size() - point.y - 1 >= offset ? point.y + offset : img[0].size() - 1;

    /* Top line */
    for (unsigned int x = from_x; x <= till_x; x++) {
        if (img[x][from_y].x == 0 && img[x][from_y].y == 0) {
            img[x][from_y] = point;
            has_changes = true;
        } else if (img[x][from_y].x != point.x || img[x][from_y].y != point.y) {
            if (isNewSeedNearer(img[x][from_y], point, Point(x, from_y))) {
                img[x][from_y] = point;
                has_changes = true;
            }
        }
    }

    /* Bottom line */
    for (unsigned int x = from_x; x <= till_x; x++) {
        if (img[x][till_y].x == 0 && img[x][till_y].y == 0) {
            img[x][till_y] = point;
            has_changes = true;
        } else if (img[x][till_y].x != point.x || img[x][till_y].y != point.y) {
            if (isNewSeedNearer(img[x][till_y], point, Point(x, till_y))) {
                img[x][till_y] = point;
                has_changes = true;
            }
        }
    }

    /* Left line */
    for (unsigned int y = from_y; y <= till_y; y++) {
        if (img[from_x][y].x == 0 && img[from_x][y].y == 0) {
            img[from_x][y] = point;
            has_changes = true;
        } else if (img[from_x][y].x != point.x || img[from_x][y].y != point.y) {
            if (isNewSeedNearer(img[from_x][y], point, Point(from_x, y))) {
                img[from_x][y] = point;
                has_changes = true;
            }
        }
    }

    /* Right line */
    for (unsigned int y = from_y; y <= till_y; y++) {
        if (img[till_x][y].x == 0 && img[till_x][y].y == 0) {
            img[till_x][y] = point;
            has_changes = true;
        } else if (img[till_x][y].x != point.x || img[till_x][y].y != point.y) {
            if (isNewSeedNearer(img[till_x][y], point, Point(till_x, y))) {
                img[till_x][y] = point;
                has_changes = true;
            }
        }
    }

    return has_changes;
}

void
VoronoiDiagram::buildDiagram(std::vector<std::vector<Point>> &img, std::vector<Point> &points)
{
    bool has_changes = false;
    std::vector<bool> point_changes(points.size(), true);
    unsigned int max = img.size() > img[0].size() ? img.size() : img[0].size();

    for (unsigned int i = 0; i < max; i++) {
        has_changes = false;
        for (unsigned int p = 0; p < points.size(); p++) {
            if (point_changes[p]) {
                point_changes[p] = changeNeighboursIfNeed(img, points[p], i);
                has_changes = has_changes || point_changes[p];
            }
        }

        if (!has_changes)
            break;
    }
}

bool
VoronoiDiagram::pointIsEdge(std::vector<std::vector<Point>> &img, unsigned int x, unsigned int y)
{
    unsigned int color1 = img[x][y].x;
    unsigned int color2 = img[x][y].y;

    /* Top left */
    if (x > 0 && y > 0 && (img[x-1][y-1].x != color1  || img[x-1][y-1].y != color2))
        return true;

    /* Top */
    if (y > 0 && (img[x][y-1].x != color1  || img[x][y-1].y != color2))
        return true;

    /* Top right */
    if (x < img.size() - 1 && y > 0 && (img[x+1][y-1].x != color1  || img[x+1][y-1].y != color2))
        return true;

    /* Left */
    if (x > 0 && (img[x-1][y].x != color1  || img[x-1][y].y != color2))
        return true;

    /* Right */
    if (x < img.size() - 1 && y > 0 && (img[x+1][y].x != color1  || img[x+1][y].y != color2))
        return true;

    /* Bottom left */
    if (x > 0 && y < img[0].size() - 1 && (img[x-1][y+1].x != color1  || img[x-1][y+1].y != color2))
        return true;

    /* Bottom */
    if (y < img[0].size() - 1 && (img[x][y+1].x != color1  || img[x][y+1].y != color2))
        return true;

    /* Bottom right */
    if (x < img.size() - 1 && y < img[0].size() - 1 && (img[x+1][y+1].x != color1  || img[x+1][y+1].y != color2))
        return true;

    return false;
}

std::vector<std::vector<Point>>
VoronoiDiagram::makeVoronoiDiagram(unsigned int width, unsigned int height,
                                   std::vector<Point> &points)
{
    std::vector<std::vector<Point>> img(width, std::vector<Point>(height, Point(0, 0)));
    buildDiagram(img, points);

    return img;
}

std::vector<std::vector<bool>>
VoronoiDiagram::binarizeDiagram(std::vector<std::vector<Point>> &img)
{
    std::vector<std::vector<bool>> res(img.size(), std::vector<bool>(img[0].size(), false));

    for (unsigned int x = 0; x < img.size(); x++) {
        for (unsigned int y = 0; y < img[0].size(); y++) {
            if (pointIsEdge(img, x, y))
                res[x][y] = true;
        }
    }

    return res;
}
