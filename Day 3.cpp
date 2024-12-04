#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <tuple>

std::regex multiplyRegex("(mul|do|don't)\\((([0-9]{1,3}),([0-9]{1,3})|)\\)");

int main() {
    std::ifstream file("Day 3.txt");

    int total1 = 0;
    int total2 = 0;
    bool active = true;

    std::string line;
    while (std::getline(file, line)) {
        std::smatch match;
        std::string::const_iterator searchStart(line.cbegin());

        while (std::regex_search(searchStart, line.cend(), match, multiplyRegex)) {
            searchStart = match.suffix().first;
            std::string operation = match[1];

            if (operation == "mul") {
                total1 += std::stoi(match[3]) * std::stoi(match[4]);
                if (active) total2 += std::stoi(match[3]) * std::stoi(match[4]);
            } else if (operation == "do")
                active = true;
            else if (operation == "don't")
                active = false;

        }
    }

    printf("The total of all multiplications is %d\n", total1);
    printf("The total of the valid multiplications is %d\n", total2);
}