#include <fstream>  /* ifstream */
#include <string>   /* string */
#include <cstdio>   /* printf */
#include <cstdint>  /* uint64_t */
#include <vector>   /* vector */
#include <algorithm>

using namespace std;

void part1 (string filename)
{
    printf("Part 1\n");

    ifstream myfile (filename);
    string line;

    vector<vector<string>> problems;

    uint64_t total = 0;

    while (getline(myfile, line)) {
        vector<string> current_line;
        string rest = line;
        rest = rest.substr(0,rest.find_last_not_of(" \t\n\r") + 1);
        size_t pos;
        while (true) {
            
            size_t start = rest.find_first_not_of(" \t\n\r");
            if (start != string::npos) {
                rest = rest.substr(start);
            }

            pos = rest.find(" ");
            if (pos == string::npos) {
                current_line.push_back(rest);
                break;
            }

            string cur = rest.substr(0, pos);
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

void part2(string filename)
{
    printf("Part 2:\n");

    ifstream myfile (filename);
    string line;

    vector<string> raw;

    uint64_t total = 0;

    while (getline(myfile, line)) {
        raw.push_back(line);
    }
    
    // Separate opperations from digits
    string opp_str = raw[raw.size()-1];
    raw.pop_back();

    // get all opperations in reverse order
    vector<char> opps;
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
        string tmp = "";
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
            printf("%lu += %lu\n", running_total, calculation);
            running_total += calculation;
            calculation = 0;
            ++opp_index;
        }
    }
    printf("Total: %lu", running_total);
}

int main()
{
    string filename = "Day_06/input.txt";

    part1(filename);
    part2(filename);

    return 0;
}