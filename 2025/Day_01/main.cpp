#include <fstream>      /* file */
#include <string>       /* std::string */
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */


int main()
{
    int count_1 = 0;
    int count_2 = 0;      // Rolling count times it passes zero
    int pos = 50;       // Position of the current turn
    int last_pos;       // The position of the last turn
    
    // File handeling
    std::string line;
    std::ifstream myfile ("input.txt");

    if(myfile.is_open()) {
        while( getline(myfile,line)) {
            std::string direction = line.substr(0,1);
            std::string digits_char = line.substr(1);
            int digits = atoi(digits_char.c_str());
            
            bool once = false;  // track if we have passed the zero once or more, used for when the position is zero
            last_pos = pos;

            // Todo: Harden
            if( direction == "L"){
                pos -= digits; // Turn the padlock left
            }
            else {
                pos += digits; // Turn the padlock right
            }


            while (pos < 0) {
                pos += 100;
                // if the previous position was 0 don't count the first turn past zero
                if ((last_pos == 0) && once == false) {
                    once = true;
                } else {
                    ++count_2;
                }
            }

            while (pos > 99) {
                pos -= 100;
                // if the current position is zero don't count the last turn past zero
                if (( pos % 100 == 0) && once == false) {
                    once = true;
                } else {
                    ++count_2;
                }
            }

            if (pos == 0) {
                ++count_1;
                ++count_2;
            }
        }

        last_pos = pos;
        printf("Part One Answer: %d\n", count_1);
        printf("Part Two Answer: %d\n", count_2);
    }

    return 0;
}