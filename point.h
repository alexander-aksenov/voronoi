#ifndef POINT_H
#define POINT_H

struct Point {
    unsigned int x;
    unsigned int y;

    Point() : x(0), y(0) {}
    Point(unsigned int x, unsigned int y) : x(x), y(y) {}

    bool operator==(const Point& p) const
    {
        return (x == p.x) && (y == p.y);
    }
};

template <>
struct std::hash<Point> {
    size_t operator()(const Point& p) const
    {
        return (std::hash<unsigned int>()(p.x)
                ^ std::hash<unsigned int>()(p.y));
    }
};


#endif /* POINT_H */
