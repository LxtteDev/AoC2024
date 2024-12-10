#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

struct File {
    unsigned long int start;
    int size;
    int id;
};

int main() {
    std::ifstream file("Day 9.txt");

    std::string line;
    std::getline(file, line);

    std::vector<unsigned long int> filesystem;
    std::vector<File> files;
    std::vector<File> emptyFiles;

    unsigned long int id = 0;
    for (int i = 0; i < line.size(); i++) {
        int number = std::stoi(line.substr(i, 1));

        if (i % 2 == 0) {
            files.push_back(File {
                filesystem.size(),
                number,
                (int)id
            });

            for (unsigned int j = 0; j < number; j++)
                filesystem.push_back(id);

            id++;
        } else {
            emptyFiles.push_back(File {
                filesystem.size(),
                number,
                -1
            });

            for (unsigned int j = 0; j < number; j++)
                filesystem.push_back(-1);
        }
    }

    unsigned long int checksum = 0;
    for (unsigned int i = 0; i < filesystem.size(); i++) {
        if (filesystem[i] == -1) {
            std::swap(filesystem[i], filesystem.back());

            do filesystem.pop_back();
            while (filesystem.back() == -1);
        }

        checksum += filesystem[i] * i;
    }


    printf("The file checksum is %lu\n", checksum);

    checksum = 0;
    while (!files.empty()) {
        File& file = files.back();

        for (unsigned int i = 0; i < files.size(); i++) {
            File& empty = emptyFiles[i];

            if (empty.size >= file.size && empty.start < file.start) {
                file.start = empty.start;
                empty.size -= file.size;
                empty.start += file.size;
                break;
            }
        }

        for (unsigned int i = 0; i < file.size; i++)
            checksum += file.id * (file.start + i);

        files.pop_back();
    }

    printf("The new file checksum is %lu\n", checksum);
}