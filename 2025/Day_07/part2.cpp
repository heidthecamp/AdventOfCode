#include <fstream>
#include <cstdlib> 
#include <vector>
#include <cstdint>

#include "common.hpp"

void part2(std::string filename)
{
    printf("Part 2:\n");
    
    std::ifstream myfile (filename);
    std::string line;
    std::vector<uint64_t> beam_count;

    while(getline(myfile, line)){
        for (int i = 0; i < line.length(); ++i) {
            while (i >= beam_count.size()) {
                beam_count.push_back(0);
            }
            if (line[i] == 'S') {
                beam_count[i] = 1;
            } else if (line[i] == '^') {
                beam_count[i-1] += beam_count[i];
                beam_count[i+1] += beam_count[i];
                beam_count[i] = 0;
            }
        }
    }
    


    uint64_t total = 0;

    for(int i = 0; i < beam_count.size(); ++i){
        if (i == beam_count.size() - 1) {
            printf("%lu", beam_count[i]);
        } else {
            printf("%lu, ", beam_count[i]);
        }
        total += beam_count[i];
    }
    printf("\n");

    printf("\tTotal: %lu\n", total);
}
