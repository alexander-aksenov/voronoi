#include <random>
#include <cmath>
#include <unordered_map>
#include <height_map.h>

enum {
    MAIN_POINTS_PERCENT = 10,

    MIN_HEIGHT = -1000,
    MAX_HEIGHT = 1000,
};

void
HeightMap::generateMainPointsHeights(std::vector<MainPoint>& points, unsigned int seed)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned int> distrib(MIN_HEIGHT, MAX_HEIGHT);

    for (auto it = points.begin(); it != points.end(); it++)
        (*it).height = distrib(gen);
}

double
HeightMap::getPointsDistance(const Point& p1, const Point& p2)
{
    /* D = sqrt((p2.x - p1.x)^2 + (p2.y - p1.y)^2) */

    long x1 = p1.x;
    long y1 = p1.y;
    long x2 = p2.x;
    long y2 = p2.y;

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void
HeightMap::evalHeigthPointsHeights(std::vector<MainPoint>& main_points,
                                   std::vector<HeightPoint>& height_points)
{
    for (auto h_it = height_points.begin(); h_it != height_points.end(); h_it++) {
        for (auto m_it = main_points.begin(); m_it != main_points.end(); m_it++) {
            auto distance = getPointsDistance((*h_it).p, (*m_it).p);

            /* At first, add new points. If all are already added - replace the farthest with this if it is nearer */
            unsigned int replace_ind = HEIGHTS_COUNT;
            bool is_new = false;
            for (unsigned int i = 0; i < HEIGHTS_COUNT; i++) {
                /* Check point is just inited */
                if ((*h_it).heights[i].mp.p == (*h_it).p) {
                    (*h_it).heights[i].mp = *m_it;
                    (*h_it).heights[i].distance = distance;
                    is_new = true;
                    break;
                }

                if ((*h_it).heights[i].distance > distance) {
                    if (replace_ind >= HEIGHTS_COUNT)
                        replace_ind = i;
                    else if ((*h_it).heights[replace_ind].distance > distance)
                        replace_ind = i;
                }
            }

            /* If not new - add */
            if (!is_new) {
                (*h_it).heights[replace_ind].mp = *m_it;
                (*h_it).heights[replace_ind].distance = distance;
            }
        }
    }
}

int
HeightMap::evalPointHeigth(const HeightPoint& hp)
{
    double d_height = 0;

    for (unsigned int i = 0; i < HEIGHTS_COUNT; i++) {
        d_height += (hp.heights[i].mp.height / hp.heights[i].distance);
    }

    d_height /= HEIGHTS_COUNT;

    return static_cast<int>(d_height);
}

std::unordered_map<Point, int>
HeightMap::getHeigthsHashTable(const std::vector<MainPoint>& main_points,
                               const std::vector<HeightPoint>& height_points)
{
    std::unordered_map<Point, int> hash_table;

    for (auto it = main_points.begin(); it != main_points.end(); it++)
        hash_table.emplace((*it).p, (*it).height);

    for (auto it = height_points.begin(); it != height_points.end(); it++) {
        unsigned int height = evalPointHeigth(*it);
        hash_table.emplace((*it).p, height);
    }

    return hash_table;
}

std::vector<std::vector<int>>
HeightMap::doMakeHeigthMap(const std::vector<std::vector<Point>>& voronoi,
                           const std::unordered_map<Point, int> heights_by_point)
{
    std::vector<std::vector<int>> height_map(voronoi.size(), std::vector<int>(voronoi[0].size(), 0));

    for (unsigned int x = 0; x < voronoi.size(); x++) {
        for (unsigned int y = 0; y < voronoi[0].size(); y++) {
            height_map[x][y] = heights_by_point.at(voronoi[x][y]);
        }
    }

    return height_map;
}


std::vector<std::vector<int>>
HeightMap::makeHeightMap(const std::vector<std::vector<Point>>& voronoi,
                         const std::vector<Point>& points,
                         unsigned int seed)
{
    size_t main_points_cnt = points.size() * (MAIN_POINTS_PERCENT / 100);
    if (main_points_cnt == 0)
        main_points_cnt = 1;

    std::vector<MainPoint> main_points(points.begin(), points.begin() + main_points_cnt);
    std::vector<HeightPoint> height_points(points.begin() + main_points_cnt + 1, points.end());

    generateMainPointsHeights(main_points, seed);
    evalHeigthPointsHeights(main_points, height_points);
    auto heights_by_point = getHeigthsHashTable(main_points, height_points);

    return doMakeHeigthMap(voronoi, heights_by_point);
}

std::vector<std::vector<int>>
HeightMap::makeHeightMap(const std::vector<std::vector<Point>>& voronoi,
                         const std::vector<Point>& points)
{
    std::random_device rd;

    return makeHeightMap(voronoi, points, rd());
}
