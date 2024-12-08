#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

bool vectorContains(std::vector<std::string> vector, std::string value) {
    for (unsigned int i = 0; i < vector.size(); i++)
        if (vector[i] == value) return true;

    return false;
}

std::vector<std::vector<bool>> findAntinodes(std::vector<std::string> map, std::string node, bool partTwo = false) {
    std::vector<std::vector<bool>> antinodes(map.size());
    for (unsigned int i = 0; i < map.size(); i++)
        antinodes[i] = std::vector<bool>(map[0].size());

    for (unsigned int i = 0; i < map.size(); i++) {
        for (unsigned int j = 0; j < map[i].size(); j++) {
            std::string character = map[i].substr(j, 1);

            if (character != node) continue;

            for (unsigned int k = 0; k < map.size(); k++) {
                for (unsigned int l = 0; l < map[k].size(); l++) {
                    std::string character = map[k].substr(l, 1);

                    if (character != node) continue;
                    if (i == k && j == l) continue;

                    int dx = k - i;
                    int dy = l - j;

                    if (partTwo) {
                        for (unsigned int m = 0; m < 71; m++) {
                            int dxm = dx * m;
                            int dym = dy * m;

                            if (i - dxm >= 0 && i - dxm < map.size() && j - dym >= 0 && j - dym < map[i - dxm].size()) antinodes[i - dxm][j - dym] = true;
                            if (k + dxm >= 0 && k + dxm < map.size() && l + dym >= 0 && l + dym < map[k + dxm].size()) antinodes[k + dxm][l + dym] = true;
                        }
                    } else {
                        if (i - dx >= 0 && i - dx < map.size() && j - dy >= 0 && j - dy < map[i - dx].size()) antinodes[i - dx][j - dy] = true;
                        if (k + dx >= 0 && k + dx < map.size() && l + dy >= 0 && l + dy < map[k + dx].size()) antinodes[k + dx][l + dy] = true;
                    }
                }
            }
        }
    }

    return antinodes;
}

int main() {
    std::ifstream file("Day 8.txt");

    std::vector<std::string> unique;
    std::vector<std::string> map;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        for (unsigned int i = 0; i < line.size(); i++) {
            std::string character = line.substr(i, 1);

            if (character == ".") continue;
            if (!vectorContains(unique, character)) unique.push_back(character);
        }

        map.push_back(line);
    }


    // Part 1
    std::vector<std::vector<bool>> antinodes(map.size());
    for (unsigned int i = 0; i < map.size(); i++)
        antinodes[i] = std::vector<bool>(map[0].size());

    for (unsigned int i = 0; i < unique.size(); i++) {
        std::vector<std::vector<bool>> localAntinodes = findAntinodes(map, unique[i]);

        for (unsigned int j = 0; j < localAntinodes.size(); j++)
            for (unsigned int k = 0; k < localAntinodes[j].size(); k++)
                if (localAntinodes[j][k]) antinodes[j][k] = true;
    }

    int total = 0;
    for (unsigned int i = 0; i < antinodes.size(); i++)
        for (unsigned int j = 0; j < antinodes[i].size(); j++)
            if (antinodes[i][j]) total++;

    printf("There are %d unique antinodes\n", total);


    // Part 1
    std::vector<std::vector<bool>> harmonicAntinodes(map.size());
    for (unsigned int i = 0; i < map.size(); i++)
        harmonicAntinodes[i] = std::vector<bool>(map[0].size());

    for (unsigned int i = 0; i < unique.size(); i++) {
        std::vector<std::vector<bool>> localAntinodes = findAntinodes(map, unique[i], true);

        for (unsigned int j = 0; j < localAntinodes.size(); j++)
            for (unsigned int k = 0; k < localAntinodes[j].size(); k++)
                if (localAntinodes[j][k]) harmonicAntinodes[j][k] = true;
    }

    total = 0;
    for (unsigned int i = 0; i < harmonicAntinodes.size(); i++)
        for (unsigned int j = 0; j < harmonicAntinodes[i].size(); j++)
            if (harmonicAntinodes[i][j]) total++;

    printf("There are %d unique harmonic antinodes\n", total);
}