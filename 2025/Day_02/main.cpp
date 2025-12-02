#include <fstream>      /* file */
#include <string>       /* string */
#include <cstdio>       /* printf */
#include <cstdlib>      /* atoi */
#include <vector>       /* vector */
#include <cstdint>      /* uint64_t */

using namespace std;

struct Range {
    uint64_t low;
    uint64_t high;
};

void part1 (string filename)
{
    // Part 1
    string line;
    ifstream myfile (filename);
    uint64_t count = 0;

    uint64_t running_sum = 0;

    vector<Range> ranges; 

    if (myfile.is_open()) {
        string rest;
        while (getline(myfile, line)) {
            string rest;
            rest = line;
            string first;
            while (true) {
                
                size_t index = rest.find(",");
                first = rest.substr(0, index);
                
                Range r = {
                    .low = (uint64_t)atol(first.substr(0,first.find("-")).c_str()),
                    .high = (uint64_t)atol(first.substr(first.find("-") + 1).c_str()),
                };

                ranges.push_back(r);
                
                if (index==string::npos) {
                    break;
                }
                rest = rest.substr(index + 1);
            }

            for (auto &range : ranges) {
                // printf("Range: %lu - %lu\n", range.low, range.high);
                for (uint64_t i = range.low; i <= range.high; i++) {
                    string str = to_string(i);

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

void part2 (string filename)
{
    string line;
    ifstream myfile (filename);
    uint64_t count = 0;

    uint64_t running_sum = 0;

    vector<Range> ranges; 

    if (myfile.is_open()) {
        string rest;
        while (getline(myfile, line)) {
            string rest;
            rest = line;
            string first;
            while (true) {
                
                size_t index = rest.find(",");
                first = rest.substr(0, index);
                
                Range r = {
                    .low = (uint64_t)atol(first.substr(0,first.find("-")).c_str()),
                    .high = (uint64_t)atol(first.substr(first.find("-") + 1).c_str()),
                };
                    
                ranges.push_back(r);
                
                if (index==string::npos) {
                    break;
                }
                rest = rest.substr(index + 1);
            }

            for (auto &range : ranges) {
                for (uint64_t i = range.low; i <= range.high; i++) {
                    string str = to_string(i);

                    for (size_t j = 2; j <= str.length(); ++j) {
                        if (str.length() % j == 0) {

                            string tmp = str.substr(0, str.length()/j);
                            string test = "";

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
    string filename = "Day_02/input.txt";
    // string filename = "Day_02/input_example.txt";
    printf("Part 1: \n");
    part1(filename);
    printf("Part 2: \n");
    part2(filename);

    return 0;
}