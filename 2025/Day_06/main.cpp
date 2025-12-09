#include <fstream>  /* std::ifstream */
#include <string>   /* std::string */
#include <cstdio>   /* printf */
#include <cstdint>  /* uint64_t */
#include <vector>   /* vector */
#include <algorithm>


void part1 (std::string filename)
{
    printf("Part 1\n");

    std::ifstream myfile (filename);
    std::string line;

    std::vector<std::vector<std::string>> problems;

    uint64_t total = 0;

    while (getline(myfile, line)) {
        std::vector<std::string> current_line;
        std::string rest = line;
        rest = rest.substr(0,rest.find_last_not_of(" \t\n\r") + 1);
        size_t pos;
        while (true) {
            
            size_t start = rest.find_first_not_of(" \t\n\r");
            if (start != std::string::npos) {
                rest = rest.substr(start);
            }

            pos = rest.find(" ");
            if (pos == std::string::npos) {
                current_line.push_back(rest);
                break;
            }

            std::string cur = rest.substr(0, pos);
            rest = rest.substr(pos + 1);
            
            if (cur != " ") {
                current_line.push_back(cur);
            }

        }
        problems.push_back(current_line);
    }

    for (int i = 0; i < problems[0].size(); ++i) {
        uint64_t res = 0;
        if (problems[problems.size() -1][i] == "*") {
            res = 1;
        }
        for (int j = 0; j < problems.size() - 1; ++j) {
            if (problems[problems.size() -1][i] == "+") {
                res += (uint64_t)atol(problems[j][i].c_str());
            }
            else if (problems[problems.size() -1][i] == "*") {
                res *= atol(problems[j][i].c_str());
            }
        }
        total += res;
    }

    printf("\tEnd total: %lu\n", total);
}

void part2(std::string filename)
{
    printf("Part 2:\n");

    std::ifstream myfile (filename);
    std::string line;

    std::vector<std::string> raw;

    uint64_t total = 0;

    while (getline(myfile, line)) {
        raw.push_back(line);
    }
    
    // Separate opperations from digits
    std::string opp_str = raw[raw.size()-1];
    raw.pop_back();

    // get all opperations in reverse order
    std::vector<char> opps;
    for (int i = opp_str.length() - 1; i >= 0; --i){
        if (opp_str[i] != ' ') {
            opps.push_back(opp_str[i]);
        }
    }

    // total for final result
    uint64_t running_total = 0;
    // calculation for current sum/product.
    uint64_t calculation = 0;

    int opp_index = 0;

    for(int i = raw[0].length() - 1; i >= 0; --i) {
        std::string tmp = "";
        for(auto it: raw) {
            if (it[i] != ' '){
                tmp += it[i];
            }
        }
        if (tmp != "" || i == 0) {
            if (opps[opp_index] == '+') {
                calculation += (uint64_t)atol(tmp.c_str());
            } else if (opps[opp_index] == '*') {
                if (calculation == 0) {
                    calculation = (uint64_t)atol(tmp.c_str());
                } else {
                    calculation *= (uint64_t)atol(tmp.c_str());
                }
            }
        }
        if (tmp == "" || i == 0) {
            running_total += calculation;
            calculation = 0;
            ++opp_index;
        }
    }
    printf("\tTotal: %lu\n", running_total);
}

int main()
{
    std::string filename = "input.txt";

    part1(filename);
    part2(filename);

    return 0;
}