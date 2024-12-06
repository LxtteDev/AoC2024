#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

bool contains(int n, std::vector<int> v) {
    for (unsigned int i = 0; i < v.size(); i++)
        if (v[i] == n) return true;
    return false;
}

bool verifyLine(std::vector<int> line, std::map<int, std::vector<int>>& order) {
    for (unsigned int i = 0; i < line.size(); i++) {
        int character = line[i];
        std::vector<int> rules = order[character];

        for (unsigned int j = 0; j < i; j++)
            if (contains(line[j], rules)) return false;
    }

    return true;
}

std::vector<int> sortLine(std::vector<int> line, std::map<int, std::vector<int>>& order) {
    bool sorted = verifyLine(line, order);

    while (!sorted) {
        for (unsigned int i = 0; i < line.size(); i++) {
            int character = line[i];
            std::vector<int> rules = order[character];
            bool moved = false;

            for (unsigned int j = 0; j < i; j++)
                if (contains(line[j], rules)) {
                    int temp = line[j];
                    line[j] = line[i];
                    line[i] = temp;

                    moved = true;
                }

            if (moved) {
                sorted = verifyLine(line, order);
                break;
            }
        }
    }

    return line;
}

int main() {
    std::ifstream file("Day 5.txt");

    std::map<int, std::vector<int>> order; // X | Y's (X Before Y)
    std::vector<std::vector<int>> lines;

    std::string line;
    bool orders = true;
    while (std::getline(file, line)) {
        if (line.empty()) {
            orders = false;
            continue;
        }

        if (orders) {
            int x = std::stoi(line.substr(0, 2));
            int y = std::stoi(line.substr(3, 2));

            if (order.find(x) == order.end()) order[x] = std::vector<int>();
            order[x].push_back(y);
        } else {
            std::vector<int> myLine;

            std::istringstream lineStream(line);
            std::string character;

            while (getline(lineStream, character, ','))
                myLine.push_back(std::stoi(character));

            lines.push_back(myLine);
        }
    }

    int total = 0;
    int correctedTotal = 0;
    for (unsigned int i = 0; i < lines.size(); i++)
        if (verifyLine(lines[i], order)) total += lines[i][(lines[i].size() - 1) / 2];
        else {
            std::vector<int> sorted = sortLine(lines[i], order);
            correctedTotal += sorted[(sorted.size() - 1) / 2];
        }

    printf("The total of all correct middle terms is %d\n", total);
    printf("The total of all incorrect middle terms is %d\n", correctedTotal);
}