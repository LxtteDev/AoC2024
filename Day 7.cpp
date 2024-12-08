#include <inttypes.h>
#include <stdint.h>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

// Part 1
uint64_t operate(std::vector<int> numbers, std::vector<bool> operation) {
    uint64_t total = numbers[0];

    for (unsigned int i = 1; i < numbers.size(); i++) {
        if (operation[i - 1]) total *= numbers[i];
        else total += numbers[i];
    }

    return total;
}

std::vector<bool> next(std::vector<bool> operations) {
    for (unsigned int i = 0; i < operations.size(); i++) {
        int index = operations.size() - 1 - i;

        operations[index] = !operations[index];
        if (operations[index]) break;
    }

    return operations;
}

bool calibrate(uint64_t target, std::vector<int> numbers) {
    std::vector<bool> operations(numbers.size() - 1);

    while(true) {
        uint64_t result = operate(numbers, operations);
        if (result == target) return true;

        int total = 0;
        for (unsigned int i = 0; i < operations.size(); i++)
            if (operations[i]) total++;
        if (total == operations.size()) return false;

        operations = next(operations);
    }

    return false;
}

// Part 2
uint64_t operate2(std::vector<int> numbers, std::vector<int> operation) {
    uint64_t total = numbers[0];

    for (unsigned int i = 1; i < numbers.size(); i++) {
        if (operation[i - 1] == 0) total *= numbers[i];
        else if (operation[i - 1] == 1) total += numbers[i];
        else if (operation[i - 1] == 2) {
            std::string t = std::to_string(total);
            t += std::to_string(numbers[i]);

            uint64_t value;
            std::istringstream iss(t);
            iss >> value;

            total = value;
        };
    }

    return total;
}

std::vector<int> next2(std::vector<int> operations) {
    for (unsigned int i = 0; i < operations.size(); i++) {
        int index = operations.size() - 1 - i;

        operations[index] = (operations[index] + 1) % 3;
        if (operations[index] != 0) break;
    }

    return operations;
}

bool calibrate2(uint64_t target, std::vector<int> numbers) {
    std::vector<int> operations(numbers.size() - 1);

    while(true) {
        uint64_t result = operate2(numbers, operations);
        if (result == target) return true;

        int total = 0;
        for (unsigned int i = 0; i < operations.size(); i++)
            total += operations[i];
        if (total == operations.size() * 2) return false;

        operations = next2(operations);
    }

    return false;
}

int main() {
    std::ifstream file("Day 7.txt");

    std::vector<std::tuple<uint64_t, std::vector<int>>> calibrations;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::string total = line.substr(0, line.find(":"));

        std::vector<int> numbers;
        std::string number;
        for (unsigned int i = 0; i < line.size() - total.size() - 2; i++) {
            std::string character = line.substr(total.size() + 2 + i, 1).c_str();

            if (character == " ") {
                uint64_t value;
                std::istringstream iss(number);
                iss >> value;
                numbers.push_back(value);
                number = "";
            } else number += character;
        }

        uint64_t value;
        std::istringstream iss(number);
        iss >> value;
        numbers.push_back(value);

        calibrations.push_back(std::make_tuple(std::stoll(total), numbers));
    }


    // Part 1
    uint64_t total = 0;
    for (unsigned int i = 0; i < calibrations.size(); i++) {
        uint64_t target = std::get<0>(calibrations[i]);
        std::vector<int> numbers = std::get<1>(calibrations[i]);

        if (calibrate(target, numbers)) total += target;
    }

    printf("The total calibration result is %" PRIu64 "\n", total);


    // Part 2
    total = 0;
    for (unsigned int i = 0; i < calibrations.size(); i++) {
        uint64_t target = std::get<0>(calibrations[i]);
        std::vector<int> numbers = std::get<1>(calibrations[i]);

        if (calibrate2(target, numbers)) total += target;
    }

    printf("The new calibration result is %" PRIu64 "\n", total);
}