#include <fstream>      /* file */
#include <string>       /* std::string */
#include <cstdio>       /* printf */
#include <cstdlib>      /* atoi */
#include <vector>       /* vector */
#include <cstdint>      /* uint64_t */


struct Range {
    uint64_t low;
    uint64_t high;
};

void part1 (std::string filename)
{
    // Part 1
    std::string line;
    std::ifstream myfile (filename);
    uint64_t count = 0;

    uint64_t running_sum = 0;

    std::vector<Range> ranges; 

    if (myfile.is_open()) {
        std::string rest;
        while (getline(myfile, line)) {
            std::string rest;
            rest = line;
            std::string first;
            while (true) {
                
                size_t index = rest.find(",");
                first = rest.substr(0, index);
                
                Range r = {
                    .low = (uint64_t)atol(first.substr(0,first.find("-")).c_str()),
                    .high = (uint64_t)atol(first.substr(first.find("-") + 1).c_str()),
                };

                ranges.push_back(r);
                
                if (index==std::string::npos) {
                    break;
                }
                rest = rest.substr(index + 1);
            }

            for (auto& range : ranges) {
                // printf("Range: %lu - %lu\n", range.low, range.high);
                for (uint64_t i = range.low; i <= range.high; i++) {
                    std::string str = std::to_string(i);

                    if (str.substr(0, (str.length()/2)) == str.substr((str.length()/2))) {
                        ++count;
                        running_sum += i;
                    }
                }
                
            }
        }
    }

    printf("FINAL Count: %lu\n", count);
    printf("FINAL Sum: %lu\n", running_sum);
}

void part2 (std::string filename)
{
    std::string line;
    std::ifstream myfile (filename);
    uint64_t count = 0;

    uint64_t running_sum = 0;

    std::vector<Range> ranges; 

    if (myfile.is_open()) {
        std::string rest;
        while (getline(myfile, line)) {
            std::string rest;
            rest = line;
            std::string first;
            while (true) {
                
                size_t index = rest.find(",");
                first = rest.substr(0, index);
                
                Range r = {
                    .low = (uint64_t)atol(first.substr(0,first.find("-")).c_str()),
                    .high = (uint64_t)atol(first.substr(first.find("-") + 1).c_str()),
                };
                    
                ranges.push_back(r);
                
                if (index==std::string::npos) {
                    break;
                }
                rest = rest.substr(index + 1);
            }

            for (auto &range : ranges) {
                for (uint64_t i = range.low; i <= range.high; i++) {
                    std::string str = std::to_string(i);

                    for (size_t j = 2; j <= str.length(); ++j) {
                        if (str.length() % j == 0) {

                            std::string tmp = str.substr(0, str.length()/j);
                            std::string test = "";

                            for ( size_t k = 0; k < j; ++k) {
                                test += tmp;
                            }

                            if (str == test) {
                                ++count;
                                running_sum += i;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("FINAL Count: %lu\n", count);
    printf("FINAL Sum: %lu\n", running_sum);
}

int main()
{
    std::string filename = "input.txt";
    printf("Part 1: \n");
    part1(filename);
    printf("Part 2: \n");
    part2(filename);

    return 0;
}