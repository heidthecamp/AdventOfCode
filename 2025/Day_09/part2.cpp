#include <fstream>
#include <vector>
#include <algorithm> // min, max, sort
#include <ctime>

#include <SDL2/SDL.h>

#include "common.hpp"

struct Rectangle {
    Point a;
    Point b;
    int64_t area;
};

bool sort_rect(Rectangle lhs, Rectangle rhs) {
    return lhs.area > rhs.area;
}

void part2(std::string filename)
{

    // I decided agains adding SDL for this example but though it could be a nice visualization.
    // SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_Window* win = SDL_CreateWindow(
    //     "Day9 part2",
    //     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    //     1024, 768,
    //     0
    // );
    // SDL_Renderer* ren = SDL_CreateRenderer(win, 0, 0);
    time_t timer ;
    
    printf("Part 2:\n");

    std::ifstream myfile (filename);
    std::string line;

    std::vector<Point> points;

    int64_t max_x = 0;
    int64_t max_y = 0;
    int64_t min_x = -1;
    int64_t min_y = -1;

    printf("\tLoading file\n");
    while(std::getline(myfile, line)) {
        Point p = {
            .x = atol(line.substr(0, line.find(',')).c_str()),
            .y = atol(line.substr(line.find(',') + 1).c_str()),
        };

        if (max_x < p.x) {
            max_x = p.x;
        }
        if (max_y < p.y) {
            max_y = p.y;
        }

        if (min_x > p.x || min_x == -1) {
            min_x = p.x;
        }
        if (min_y > p.y || min_y == -1) {
            min_y = p.y;
        }

        points.push_back(p);
    }
    printf("\tFile Loaded:\n");


    printf("\tBuilding tile map\n");
    std::vector<std::vector<bool>> tiles(max_y+1, std::vector<bool>(max_x+1, false));
    for (int i = 0; i < points.size(); ++i) {
        tiles[points[i].y][points[i].x] = true;
    }

    printf("\tTile map skeleton\n");

    /* Display tiles */
    // for (auto it : tiles) {
    //     for (auto jt : it) {
    //         char c = '.';
    //         if (jt) {
    //             c = 'X';
    //         }
    //         printf("%c", c);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    int cur_low = tiles[0].size();
    int prev_low = cur_low;
    int cur_high = -1;
    int prev_high = cur_high;
    for (int index = min_y-1; index < tiles.size(); ++index) {
        int low = min_x - 1;
        bool capture = false;
        while (low < tiles[index].size() && (low <= cur_low || capture == true)){
            if (tiles[index][low] == true) {
                
                if (low < cur_low) {
                    cur_low = low;
                    break;
                } else if (low == cur_low) {
                    capture = true;
                } else if (capture) {
                    cur_low = low;
                    break;
                }
            }
            ++low;
        }
        int high = tiles[index].size();
        capture = false;
        while (high >= min_x && (high >= cur_high || capture == true)) {
            if (tiles[index][high] == true) {
                if (high > cur_high) {
                    cur_high = high;
                    break;
                } else if (high == cur_high) {
                    capture = true;
                } else if (capture) {
                    cur_high = high;
                    break;
                }
            }
            --high;
        }

        low = std::min(cur_low, prev_low);
        high = std::max(cur_high, prev_high);

        bool write = true;
        if (low > 0 && low < tiles[index].size() &&
            high > 0 && high < tiles[index].size() &&
            low < high
        ) {
            for (int j = low; j <= high; ++j) {
                if (
                    j != low && j != cur_low && j != prev_low && 
                    j!= high && j!= cur_high && j!= prev_high && 
                    tiles[index][j]
                ) {
                    write = !write;
                }
                if (write) {
                    tiles[index][j] = true;
                }
            }
        }
        prev_low = cur_low;
        prev_high = cur_high;
    }

    printf("\tTile map built\n");

    printf("\tCalculating areas\n");

    std::vector<Rectangle> areas;
    for (int i = 0; i < points.size(); ++i) {
        for(int j = i + 1; j < points.size(); ++j) {
            int64_t a = area(points[i], points[j]);
            areas.push_back(Rectangle(points[i], points[j], a));
        }
    }

    printf("\tAreas calculated\n");

    printf("\tSorting areas\n");

    std::sort(areas.begin(), areas.end(), sort_rect);

    printf("\tAreas sorted\n");

    printf("\tGetting max vaid area\n");

    int64_t max_area = -1;

    for (auto it : areas) {
        int64_t minx = std::min(it.a.x, it.b.x);
        int64_t miny = std::min(it.a.y, it.b.y);
        int64_t maxx = std::max(it.a.x, it.b.x);
        int64_t maxy = std::max(it.a.y, it.b.y);
        bool valid = true;


        // check edges first to reduce time 
        for (int64_t x = minx; valid && x <= maxx; ++x){
            if (!tiles[miny][x] || !tiles[maxy][x]) {
                valid = false;
            }
        }
        for (int64_t y = miny; valid && y <= maxy; ++y){
            if (!tiles[y][minx] || !tiles[y][maxx]) {
                valid = false;
            }
        }

        // check all internal values to catch any edge cases
        for(int64_t y = miny + 1; valid && y < maxy; ++y){
            for (int64_t x = minx + 1; valid && x < maxx; ++x){
                if (!tiles[y][x]){
                    valid = false;
                }
            }
        }

        if (valid) {
            max_area = it.area;
            break;
        }
    }


    printf("\tMax area: %ld\n", max_area);

    // bool running = true;

    // while (running) {
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             running = false;
    //         }
    //     }
        
    //     SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    //     SDL_RenderClear(ren);

    //     SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    //     SDL_Rect rect = {0, 0, 100, 100};
    //     SDL_RenderFillRect(ren, &rect);

    //     SDL_RenderPresent(ren);
    // }

    // printf("\tMax area: %ld\n", max_area);

    // SDL_DestroyRenderer(ren);
    // SDL_DestroyWindow(win);
    // SDL_Quit();
}