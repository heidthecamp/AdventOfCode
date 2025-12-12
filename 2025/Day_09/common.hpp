#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <cmath>
#include <cstdint>

struct Point {
    int64_t x;
    int64_t y;
};

inline bool in_area(
    const Point& lhs,
    const Point& rhs,
    const Point& point)
{
    if (lhs.x < rhs.x && lhs.x < point.x && point.x < rhs.x) {
        if (lhs.y < rhs.y && lhs.y < point.y && point.y < rhs.y){
            return true;
        } else if (lhs.y < rhs.y && lhs.y < point.y && point.y < rhs.y){
            return true;
        }
    }   else if (lhs.x > rhs.x && lhs.x > point.x && point.x > rhs.x) {
        if (lhs.y < rhs.y && lhs.y < point.y && point.y < rhs.y){
            return true;
        } else if (lhs.y < rhs.y && lhs.y < point.y && point.y < rhs.y){
            return true;
        }       
    }
    return false;
}

inline bool bisects(
    const Point& area_lhs,
    const Point& area_rhs,
    const Point& line_lhs,
    const Point& line_rhs)
{
    if (line_lhs.x == line_rhs.x) {
        if (area_lhs.x < area_rhs.x &&
            area_lhs.x < line_lhs.x &&
            line_lhs.x < area_rhs.x) {
            if (line_lhs.y < line_rhs.y) {
                if (area_lhs.y < area_rhs.y){
                    if (line_rhs.y < area_lhs.y){
                        return false;
                    } else if (line_lhs.y > area_rhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.y > area_rhs.y){
                    if (line_rhs.y < area_rhs.y){
                        return false;
                    } else if (line_lhs.y > area_lhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
            if (line_lhs.y > line_rhs.y) {
                if (area_lhs.y < area_rhs.y){
                    if (line_lhs.y < area_lhs.y){
                        return false;
                    } else if (line_rhs.y > area_rhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.y > area_rhs.y){
                    if (line_lhs.y < area_rhs.y){
                        return false;
                    } else if (line_rhs.y > area_lhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
        }
        
        if (area_lhs.x > area_rhs.x &&
            area_lhs.x > line_lhs.x &&
            line_lhs.x > area_rhs.x) {
            if (line_lhs.y < line_rhs.y) {
                if (area_lhs.y < area_rhs.y){
                    if (line_rhs.y < area_lhs.y){
                        return false;
                    } else if (line_lhs.y > area_rhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.y > area_rhs.y){
                    if (line_rhs.y < area_rhs.y){
                        return false;
                    } else if (line_lhs.y > area_lhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
            if (line_lhs.y > line_rhs.y) {
                if (area_lhs.y < area_rhs.y){
                    if (line_lhs.y < area_lhs.y){
                        return false;
                    } else if (line_rhs.y > area_rhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.y > area_rhs.y){
                    if (line_lhs.y < area_rhs.y){
                        return false;
                    } else if (line_rhs.y > area_lhs.y) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
        }
    }


    if (line_lhs.y == line_rhs.y) {
        if (area_lhs.y < area_rhs.y &&
            area_lhs.y < line_lhs.y &&
            line_lhs.y < area_rhs.y) {
            if (line_lhs.x < line_rhs.x) {
                if (area_lhs.x < area_rhs.x){
                    if (line_rhs.x < area_lhs.x){
                        return false;
                    } else if (line_lhs.x > area_rhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.x > area_rhs.x){
                    if (line_rhs.x < area_rhs.x){
                        return false;
                    } else if (line_lhs.x > area_lhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
            if (line_lhs.x > line_rhs.x) {
                if (area_lhs.x < area_rhs.x){
                    if (line_lhs.x < area_lhs.x){
                        return false;
                    } else if (line_rhs.x > area_rhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.x > area_rhs.x){
                    if (line_lhs.x < area_rhs.x){
                        return false;
                    } else if (line_rhs.x > area_lhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
        }
        
        if (area_lhs.y > area_rhs.y &&
            area_lhs.y > line_lhs.y &&
            line_lhs.y > area_rhs.y) {
            if (line_lhs.x < line_rhs.x) {
                if (area_lhs.x < area_rhs.x){
                    if (line_rhs.x < area_lhs.x){
                        return false;
                    } else if (line_lhs.x > area_rhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.x > area_rhs.x){
                    if (line_rhs.x < area_rhs.x){
                        return false;
                    } else if (line_lhs.x > area_lhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
            if (line_lhs.x > line_rhs.x) {
                if (area_lhs.x < area_rhs.x){
                    if (line_lhs.x < area_lhs.x){
                        return false;
                    } else if (line_rhs.x > area_rhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
                else if (area_lhs.x > area_rhs.x){
                    if (line_lhs.x < area_rhs.x){
                        return false;
                    } else if (line_rhs.x > area_lhs.x) {
                        return false;
                    } else {
                        return true;        
                    }
                }
            }
        }
    }


    return false;
}

inline Point operator-(const Point& lhs, const Point& rhs) {
    return Point {
        // long absolute value
        .x = labs(lhs.x - rhs.x) + 1,
        .y = labs(lhs.y - rhs.y) + 1,
    };
}

inline int64_t area(Point first, Point second) {
    Point a = first - second;
    return a.x * a.y;
}

void part1(std::string filename);
void part2(std::string filename);

#endif // COMMON_HPP