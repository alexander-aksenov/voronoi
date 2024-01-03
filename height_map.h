#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include <vector>
#include <unordered_map>
#include <point.h>

/* Make height map from Voronoi diag:
 * 1. Get several 'main' points
 * 2. Generate random height for these points
 * 3. Eval height for other points:
 *   1. For each non-'main' point eval length from 'main' points
 *   2. Take top-10 (?) nearest
 *   3. Eval height ((Height1 / Distance1) + (Height2 / Distance2) + ... (Height10 / Distance10)) / 10
 */

class HeightMap {
        enum {
            HEIGHTS_COUNT = 10,
        };

        struct MainPoint {
            Point p;
            int height;

            MainPoint() : p(Point(0, 0)), height(0) {}
            MainPoint(Point p) : p(p), height(0) {}
        };

        struct HeightElement
        {
            MainPoint mp;
            double distance;
        };

        struct HeightPoint {
            Point p;
            HeightElement heights[HEIGHTS_COUNT];

            HeightPoint(Point p) : p(p) {
                for (int i = 0; i < HEIGHTS_COUNT; i++) {
                    heights[i].mp.p = p;
                    heights[i].mp.height = 0;
                    heights[i].distance = 0;
                }
            }
        };

        static void generateMainPointsHeights(std::vector<MainPoint>& main_points, unsigned int seed);
        static void evalHeigthPointsHeights(std::vector<MainPoint>& main_points,
                                            std::vector<HeightPoint>& height_points);
        static std::unordered_map<Point, int> getHeightsHashTable(const std::vector<MainPoint>& main_points,
                                                                  const std::vector<HeightPoint>& height_points);
        static void doMakeHeigthMap(std::vector<std::vector<Point>>& voronoi,
                                    const std::unordered_map<Point, int> heights_by_point,
                                    int min);
        static double getPointsDistance(const Point& p1, const Point& p2);
        static int evalPointHeigth(const HeightPoint& hp);


    public:
        static void makeHeightMap(std::vector<std::vector<Point>>& voronoi,
                                  const std::vector<Point>& points,
                                  unsigned int seed);
        static void makeHeightMap(std::vector<std::vector<Point>>& voronoi, const std::vector<Point> &points);
};

#endif /* HEIGHT_MAP_H */





