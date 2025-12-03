#include <fstream>      /* ifstream */
#include <string>       /* string */
#include <cstring>      /* strlen */
#include <cstdio>       /* printf */
#include <cstdlib>      /* atoi */
#include <cstdint>      /* uint64_t */

using namespace std;

void part1 (string filename) 
{
    printf("PART 1:\n");

    ifstream myfile (filename);
    string line;

    uint64_t sum = 0;

    while (getline(myfile, line)) {
        char first = '0';
        char second = '0';
        for (int i = line.size() - 1; i >= 0; --i) {
            if (second == '0') {
                second = line[i];
            }
            else if (line[i] >= first){
                if (first > second) {
                    second = first;
                }
                first = line[i];
            }
            
        }
        string tmp {first, second};
        sum += atoi(tmp.c_str());
    }
    printf("\tTotal: %lu\n\n", sum);
}

void part2 (string filename)
{
    printf("PART 2:\n");

    ifstream myfile (filename);
    string line;

    uint64_t sum = 0;

    while (getline(myfile, line)) {
        char joltage[12];
        for (int i = 12; i > 0; --i) {
            joltage[12 - i] = line[line.size()-i];
        }

        for (int i = line.size() - 13; i >= 0; --i) {
            char c = line[i];
            for (int j = 0; j < strlen(joltage); ++j) {

                if (joltage[j] <= c){
                    char tmp = joltage[j];
                    joltage[j] = c;
                    c = tmp;
                }
                else {
                    break;
                }
            }
        }
        string tmp {joltage};
        sum += atol(tmp.c_str());
    }
    printf("\tTotal: %lu\n", sum);
}

int main() {
    string filename = "Day_03/input.txt";

    part1(filename);
    part2(filename);
}