#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>

std::vector<std::string> splitSpace(std::string input) {
    std::vector<std::string> output;

    size_t pos = 0;
    std::string token;
    while ((pos = input.find_first_of(" ")) != std::string::npos) {
        token = input.substr(0, pos);
        output.push_back(token);
        input.erase(0, pos + 1);
    }

    output.push_back(input);
    return output;
}

int verifyReport(std::vector<int> report) {
    int state = 0;

    for (unsigned int j = 0; j < report.size() - 1; j++) {
        int current = report[j];
        int next = report[j + 1];

        if (current > next && state != 2) state = 1;
        else if (current < next && state != 1) state = 2;
        else {
            return false;
        }

        if (std::abs(next - current) > 3 || next - current == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ifstream file("Day 2.txt");

    std::vector<std::vector<int>> reports;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> splitLine = splitSpace(line);
        std::vector<int> report(splitLine.size());

        for (unsigned int i = 0; i < splitLine.size(); i++) report[i] = std::stoi(splitLine[i]);

        reports.push_back(report);
    }


    // Part 1
    int safeReports = 0;
    for (unsigned int i = 0; i < reports.size(); i++) {
        std::vector<int> report = reports[i];
        if (verifyReport(report)) safeReports++;
    }

    printf("There are %d safe reports!\n", safeReports);

    // Part 2
    safeReports = 0;
    for (unsigned int i = 0; i < reports.size(); i++) {
        std::vector<int> report = reports[i];
        if (verifyReport(report)) {
            safeReports++;
            continue;
        }

        // Try removing one number
        bool safe = false;
        for (unsigned int j = 0; j < report.size(); j++) {
            std::vector<int> newReport = report;
            newReport.erase(newReport.begin() + j);
            if (verifyReport(newReport)) {
                safe = true;
                break;
            }
        }

        if (safe) safeReports++;
    }

    printf("With the Problem Damper, there are %d safe reports!\n", safeReports);
}