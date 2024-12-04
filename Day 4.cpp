#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

bool checkInput(std::string string) {
    return string == "XMAS" || string == "SAMX";
}

int searchGrid(std::vector<std::string> grid, int x, int y, bool part2 = false) {
    int count = 0;

    if (!part2) {

        bool up = y == 3;
        bool down = y == 0 || (y == 3 && grid.size() > 4);
        bool left = x == 3;
        bool right = x == 0 || (x == 3 && grid[0].size() > 4);

        // Straight
        if (up) if (checkInput( grid[0].substr(x, 1) + grid[1].substr(x, 1) + grid[2].substr(x, 1) + grid[3].substr(x, 1) )) count++;
        if (down) if (checkInput( grid[y].substr(x, 1) + grid[y + 1].substr(x, 1) + grid[y + 2].substr(x, 1) + grid[y + 3].substr(x, 1) )) count++;
        if (left) if (checkInput(grid[y].substr(0, 4).c_str())) count++;
        if (right) if (checkInput(grid[y].substr(x, 4).c_str())) count++;

        // // Diagonal
        if (up && left)
            if (checkInput( grid[y].substr(x, 1) + grid[y - 1].substr(x - 1, 1) + grid[y - 2].substr(x - 2, 1) + grid[y - 3].substr(x - 3, 1) )) count++;
        if (up && right)
            if (checkInput( grid[y].substr(x, 1) + grid[y - 1].substr(x + 1, 1) + grid[y - 2].substr(x + 2, 1) + grid[y - 3].substr(x + 3, 1) )) count++;
        if (down && left)
            if (checkInput( grid[y].substr(x, 1) + grid[y + 1].substr(x - 1, 1) + grid[y + 2].substr(x - 2, 1) + grid[y + 3].substr(x - 3, 1) )) count++;
        if (down && right)
            if (checkInput( grid[y].substr(x, 1) + grid[y + 1].substr(x + 1, 1) + grid[y + 2].substr(x + 2, 1) + grid[y + 3].substr(x + 3, 1) )) count++;

    } else {

        std::string raise = grid[2].substr(0, 1) + grid[1].substr(1, 1) + grid[0].substr(2, 1);
        std::string fall = grid[0].substr(0, 1) + grid[1].substr(1, 1) + grid[2].substr(2, 1);

        if (raise == "SAM" || raise == "MAS")
            if (fall == "SAM" || fall == "MAS") {
                for (unsigned int i = 0; i < grid.size(); i++) {
                    printf("%s\n", grid[i].c_str());
                }
                printf("\n");
                return 1;
            }
    }

    return count;
}

int main() {
    std::ifstream file("Day 4.txt");

    std::vector<std::string> input;
    std::string line;
    while (std::getline(file, line))
        if (!line.empty()) input.push_back(line);

    int part1 = 0;
    int part2 = 0;

    for (unsigned int i = 0; i < input.size(); i++) {
        std::string line = input[i];

        for (unsigned int j = 0; j < line.size(); j++) {
            std::string character = line.substr(j, 1);

            if (character == "X") {

                std::vector<std::string> grid;
                std::vector<std::string> vertical;

                if (i > 2) {
                    vertical.push_back(input[i - 3]);
                    vertical.push_back(input[i - 2]);
                    vertical.push_back(input[i - 1]);
                }
                vertical.push_back(input[i]);
                if (i < input.size() - 3) {
                    vertical.push_back(input[i + 1]);
                    vertical.push_back(input[i + 2]);
                    vertical.push_back(input[i + 3]);
                }

                for (unsigned int k = 0; k < vertical.size(); k++)
                    grid.push_back(vertical[k].substr(j > 2 ? j - 3 : j, j > 2 ? j < line.size() - 3 ? 7 : 4 : 4));

                part1 += searchGrid(grid, j > 2 ? 3 : 0, i > 2 ? 3 : 0);

            } else if (character == "A") {
                if (!(i > 0 && i < input.size() - 1)) continue;
                if (!(j > 0 && j < line.size() - 1)) continue;

                std::vector<std::string> grid;
                
                grid.push_back(input[i - 1].substr(j - 1, 3));
                grid.push_back(input[i].substr(j - 1, 3));
                grid.push_back(input[i + 1].substr(j - 1, 3));

                part2 += searchGrid(grid, 1, 1, true);
            }
        }
    }

    printf("The total count of \"XMAS\" is %d\n", part1);
    printf("The total count of \"X-MAS\" is %d\n", part2);
}