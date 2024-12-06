#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

bool isLooped(std::vector<std::vector<std::string>>& map, int gx, int gy) {
    std::vector<std::vector<int>> visited(map.size());
    for (unsigned int i = 0; i < map.size(); i++)
        visited[i] = std::vector<int>(map[0].size(), -1);
    
    int direction = 0000; // 0 = up, 1 = right, 2 = down, 3 = left

    visited[gy][gx] = direction;
    while ((gx > 0 && gx < map[0].size() - 1) && (gy > 0 && gy < map.size() - 1)) {
        if (direction == 0)
            if (map[gy - 1][gx] == ".")
                gy--;
            else
                direction = 1;
        else if (direction == 1)
            if (map[gy][gx + 1] == ".")
                gx++;
            else
                direction = 2;
        else if (direction == 2)
            if (map[gy + 1][gx] == ".")
                gy++;
            else
                direction = 3;
        else if (direction == 3)
            if (map[gy][gx - 1] == ".")
                gx--;
            else
                direction = 0;

        if (visited[gy][gx] == -1) visited[gy][gx] = direction;
        else if (visited[gy][gx] == direction) return true;
    }

    return false;
}

int main() {
    std::ifstream file("Day 6.txt");

    std::vector<std::vector<std::string>> map;
    int x, y;
    int direction = 0; // 0 = up, 1 = right, 2 = down, 3 = left

    std::string line;
    int j = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> row;
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line.substr(i, 1) == "^") {
                row.push_back(".");
                x = i;
                y = j;
            } else row.push_back(line.substr(i, 1));
        }
        
        j++;
        map.push_back(row);
    }


    // Part 1
    std::vector<std::vector<bool>> visited(map.size());
    for (unsigned int i = 0; i < map.size(); i++)
        visited[i] = std::vector<bool>(map[0].size());
    int gx = x;
    int gy = y;

    while ((gx > 0 && gx < map[0].size() - 1) && (gy > 0 && gy < map.size() - 1)) {
        if (direction == 0)
            if (map[gy - 1][gx] == ".")
                gy--;
            else
                direction = 1;
        else if (direction == 1)
            if (map[gy][gx + 1] == ".")
                gx++;
            else
                direction = 2;
        else if (direction == 2)
            if (map[gy + 1][gx] == ".")
                gy++;
            else
                direction = 3;
        else if (direction == 3)
            if (map[gy][gx - 1] == ".")
                gx--;
            else
                direction = 0;

        visited[gy][gx] = true;
    }

    int visitedCount = 1;
    for (unsigned int i = 0; i < visited.size(); i++)
        for (unsigned int j = 0; j < visited[i].size(); j++)
            if (visited[i][j]) visitedCount++;

    printf("The guard visited %d distinct spots\n", visitedCount);


    // Part 2
    int loops = 0;
    for (unsigned int i = 0; i < map.size(); i++)
        for (unsigned int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == "#" || map[i][j] == "^") continue;
            std::vector<std::vector<std::string>> temp = map;
            temp[i][j] = "#";

            if (isLooped(temp, x, y)) loops++;
        }

    printf("There are %d options to loop the gaurd\n", loops);
}