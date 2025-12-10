#include <fstream>

#include "common.hpp"

void part1(std::string filename)
{
    printf("Part 1:\n");
    
    std::ifstream myfile (filename);
    std::string line;
    std::string prev_line;

    int count = 0;

    while (getline(myfile, line)) {
        for (int i = 0; prev_line.length() > 0 && i < line.length(); ++i) {
            if (prev_line[i] == '|' || prev_line[i] == 'S'){
                if (line[i] != '^') {
                    line[i] = '|';
                } else {
                    count++;
                    if (i > 0) {
                        line[i-1]='|';
                    }
                    if (i < line.length() - 1) {
                        line[i+1]='|';
                    }
                }
            } 
        }
        

        printf("%s\n", line.c_str());
        prev_line = line;
    }
    printf("\tTotal: %d\n", count);
}
