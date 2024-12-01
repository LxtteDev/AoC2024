#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>

int main() {
    std::ifstream file("Day 1.txt");

    std::vector<int> leftList;
    std::vector<int> rightList;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::string firstStr = line.substr(0, 5);
        std::string secondStr = line.substr(8, 5);

        int first = std::stoi(firstStr);
        int second = std::stoi(secondStr);

        leftList.push_back(first);
        rightList.push_back(second);
    }


    // Part 1
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    int totalDistance = 0;
    for (unsigned int i = 0; i < leftList.size(); i++)
        totalDistance += std::abs(leftList[i] - rightList[i]);

    printf("The total distance between the two lists is %d units!\n", totalDistance);


    // Part 2
    int similarity = 0;

    for (unsigned int i = 0; i < leftList.size(); i++) {
        int left = leftList[i];
        int count = 0;

        for (unsigned int j = 0; j < rightList.size(); j++) 
            if (left == rightList[j]) count++;

        similarity += count * left;
    }

    printf("The similarit score between the two lists is %d\n", similarity);
}