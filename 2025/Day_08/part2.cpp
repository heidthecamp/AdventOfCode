#include <fstream>
#include <set>
#include <unordered_map>
#include <vector>
#include <cstdint>

#include "common.hpp"

namespace std {
    template <>
    struct hash<std::tuple<int, int>> {
        size_t operator()(const std::tuple<int, int>& key)const {
            return get<0>(key) * 10000 + get<1>(key);
        }
    };
}

void part2(std::string filename) {
    printf("Part 2:\n");

    std::ifstream myfile (filename);
    std::string line;

    std::vector<Point> points;

    while(getline(myfile, line)) {

        uint64_t x = atol(line.substr(0,line.find(",")).c_str());
        std::string rest = line.substr(line.find(",") + 1);
        uint64_t y = atol(rest.substr(0,rest.find(",")).c_str());
        uint64_t z = atol(rest.substr(rest.find(",") + 1).c_str());

        Point p = {
            .x = x,
            .y = y,
            .z = z,
        };
        points.push_back(p);
    }

    std::unordered_map<std::tuple<int, int>, uint64_t> distances;

    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            auto d = distance(points[i], points[j]);
            distances.emplace(std::make_pair(std::make_tuple(i,j), d));
            // distances.emplace(std::make_pair(std::make_tuple(j,i), d));
        }
    }

    std::vector<std::set<int>> connections;

    for (int i = 0; i < points.size(); ++i){
        connections.push_back({});
        connections[i].insert(i);
    }

    uint64_t last_from_x = 0;
    uint64_t last_to_x = 0;    
    while (connections.size() > 1) {
        auto lowest_key = distances.begin()->first;
    
        for (auto it : distances) {
            auto& [key, value] = it;

            if (value < distances[lowest_key]) {
                lowest_key = key;
            }
        }

        auto& [to, from] = lowest_key;

        last_from_x = points[from].x;
        last_to_x = points[to].x;

        int64_t low = -1;
        int64_t from_index = -1;
        int64_t to_index = -1;

        for (uint64_t j = 0; j < connections.size(); ++j) {
            auto& set = connections[j];
            if (from_index < 0 && set.contains(from)) {
                from_index = j;
            }
            if (to_index < 0 && set.contains(to)) {
                to_index =j;
            }
            if (from_index >= 0 && to_index >= 0) {
                break;
            }
        }

        if (from_index != to_index) {
            connections[to_index].merge(connections[from_index]);
            connections.erase(connections.begin() + from_index);
        }

        distances[lowest_key];
        distances.erase(distances.find(lowest_key));
    }

    printf("\t%lu * %lu = %lu\n", last_from_x, last_to_x, last_from_x * last_to_x);
};