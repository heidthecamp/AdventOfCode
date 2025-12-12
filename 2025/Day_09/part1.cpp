#include <fstream>
#include <vector>

#include "common.hpp"


void part1(std::string filename)
{
    printf("Part 1:\n");

    std::ifstream myfile (filename);
    std::string line;

    std::vector<Point> points;

    while(std::getline(myfile, line)) {
        points.push_back( Point{
            .x = atol(line.substr(0, line.find(',')).c_str()),
            .y = atol(line.substr(line.find(',') + 1).c_str()),
        });
    }

    int64_t max_area = -1;
    for (int i = 0; i < points.size(); ++i) {
        for(int j = i + 1; j < points.size(); ++j) {
            int64_t a = area(points[i], points[j]);

            if (a > max_area) {
                max_area = a;
            }
        }
    }
    printf("\tMax area: %ld\n", max_area);
}