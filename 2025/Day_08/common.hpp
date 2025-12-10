#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>
#include <string>
#include <cstdint>

struct Point {
    uint64_t x;
    uint64_t y;
    uint64_t z;

    inline uint64_t length2()
    {
        return (x * x) + (y * y) + (z * z);
    }

    inline double length() {
        return sqrt(length2());
    }
};

inline Point operator-(const Point& lhs, const Point& rhs) {
    return Point{
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
    };
}

inline uint64_t distance(const Point& first, const Point& second)
{
    Point diff = first - second;
    return diff.length2();
}

void part1(std::string filename);
void part2(std::string filename);

#endif // COMMON_HPP