#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <cstdlib> 


struct Range {
    uint64_t low;
    uint64_t high;
};

bool sortLows (Range x, Range y) {
    if (x.low == y.low) {
        return (x.high < y.high);
    }
    return (x.low < y.low);
}



void part1 (std::string filename)
{
    printf("Part 1:\n");
    
    std::ifstream myfile (filename);
    std::string line;

    std::vector<Range> ranges;

    int count = 0;

    // Get the ranges
    while(getline(myfile, line) && line != ""){

        Range r = {
            .low = (uint64_t)atol(line.substr(0, line.find("-")).c_str()),
            .high = (uint64_t)atol(line.substr(line.find("-")).c_str() + 1),
        };

        ranges.push_back(r);
    }

    // sort ranges
    sort(ranges.begin(), ranges.end(), sortLows);


    // get item ids and check agains the ranges.
    while(getline(myfile,line)){
        uint64_t id = (uint64_t)atol(line.c_str());

        for (auto it: ranges) {
            if (id < it.low) {
                break;
            }
            if ( it.low <= id && id <= it.high) {
                ++count;
                break;
            }
        }
    }
    printf("\tItems: %d\n",count);
}

void part2(std::string filename) {
    printf("Part 2:\n");
    
    std::ifstream myfile (filename);
    std::string line;

    std::vector<Range> ranges;

    // Get the ranges
    while(getline(myfile, line) && line != ""){

        Range r = {
            .low = (uint64_t)atol(line.substr(0, line.find("-")).c_str()),
            .high = (uint64_t)atol(line.substr(line.find("-")).c_str() + 1),
        };

        ranges.push_back(r);
    }

    // sort ranges
    sort(ranges.begin(), ranges.end(), sortLows);

    uint64_t pos = 0;
    uint64_t count = 0;

    for ( auto it:ranges){
        // Low minus One to account for including the bottom number.
        if (pos < it.low - 1) {
            pos = it.low - 1;
        }
        
        if (pos < it.high) {
            count += (it.high - pos);
            pos = it.high;
        }
    }
    printf("\tItems: %lu\n", count);
}

int main ()
{
    std::string filename = "input.txt";
    // std::string filename = "Day_05/input_example.txt";

    part1(filename);
    part2(filename);

    return 0;
}