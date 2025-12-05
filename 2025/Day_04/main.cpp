#include <fstream>      /* ifstream */
#include <string>       /* string */
#include <cstdio>       /* printf */
#include <cstdint>      /* uint64_t */
#include <vector>       /* vector */

using namespace std;

int numNeighbors(vector<string> lines, int y, int x) {
    int count = 0;
    
    if (y - 1 >= 0) {
        if ( x - 1 >= 0 && lines[y-1][x-1] != '.') {
            count++;
        }
        if (lines[y-1][x] != '.'){
            count++;
        }
        if ( x + 1 < lines[y-1].length() && lines[y-1][x+1] != '.') {
            count++;
        }
    }
    if ( x - 1 >= 0 && lines[y][x-1] != '.') {
        count++;
    }
    if ( x + 1 < lines[y].length() && lines[y][x+1] != '.') {
        count++;
    }
    if (y + 1 < lines.size()) {
        if ( x - 1 >= 0 && lines[y+1][x-1] != '.') {
            count++;
        }
        if (lines[y+1][x] != '.'){
            count++;
        }
        if ( x + 1 < lines[y+1].length() && lines[y+1][x+1] != '.') {
            count++;
        }
    }
    return count;
}

void part1 (string filename)
{
    printf("Part 1:\n");

    ifstream myfile (filename);
    string line;

    vector<string> lines;

    while (getline(myfile, line)) {
        lines.push_back(line);
    }

    uint64_t count = 0;

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].length(); ++j) {
            int neighbors = 0;

            if (lines[i][j] == '@' && numNeighbors(lines, i, j) < 4) {
                ++count;
                lines[i][j] = 'X';
            }
        }
    }

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].length(); ++j) {
            int neighbors = 0;
            printf("%c",lines[i][j]);
        }
        printf("\n");
    }

    printf("Final count = %lu\n", count);

}


void part2 (string filename)
{
    printf("Part 2:\n");

    ifstream myfile (filename);
    string line;

    vector<string> lines;

    while (getline(myfile, line)) {
        lines.push_back(line);
    }

    int count = 0;
    int prevCount = count;

    string frame;
    do {
        frame = "";
        prevCount = count;
        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[i].length(); ++j) {
                int neighbors = 0;
                
                if (lines[i][j] == 'X') {
                    lines[i][j] = '.';
                }
                if (lines[i][j] == '@' && numNeighbors(lines, i, j) < 4) {
                    ++count;
                    lines[i][j] = 'X';
                }
                // printf("%c",lines[i][j]);
            }
            frame += lines[i];
            frame += '\n';
        }
        printf("\x1B[2J\x1B[H");
        printf(frame.c_str());
    } while( count != prevCount);

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].length(); ++j) {
            int neighbors = 0;
            printf("%c",lines[i][j]);
        }
        printf("\n");
    }

    printf("Final count = %d\n", count);
}


int main()
{
    string filename = "Day_04/input.txt";
    // string filename = "Day_04/input_example.txt";

    part1(filename);
    part2(filename);

    return 0;
}
