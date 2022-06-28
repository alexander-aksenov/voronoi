#ifndef POINT_H
#define POINT_H

struct Point {
    unsigned int x;
    unsigned int y;

    Point() : x(0), y(0) {}
    Point(unsigned int x, unsigned int y) : x(x), y(y) {}
};

#endif /* POINT_H */
