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

void part1(std::string filename) {
    printf("Part 1:\n");

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

    int max_i = 0;
    if (points.size() >= 1000) {
        max_i = 1000;
    } else {
        max_i = 10;
    }

    for (int i = 0; i < max_i; ++ i) {
        // auto lowest_key = std::make_tuple(-1, -1);
        auto lowest_key = distances.begin()->first;
    
        for (auto it : distances) {
            auto& [key, value] = it;

            if (value < distances[lowest_key]) {
                lowest_key = key;
            }
        }

        auto& [to, from] = lowest_key;

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

    int64_t top[3] = {-1, -1, -1};

    for (int i = 0; i < connections.size(); ++i) {
        int size = connections[i].size();
        if (size > top[2]) {
            if (size > top[1]) {
                if (size > top[0]){
                    top[2] = top[1];
                    top[1] = top[0];
                    top[0] = size;
                }
                else {
                    top[2] = top[1];
                    top[1] = size;
                }
            }
            else {
                top[2] = size;
            }
        }
    }
    printf("\t%ld * %ld * %ld = %ld\n", top[0], top[1], top[2], top[0] * top[1] * top[2]);
};