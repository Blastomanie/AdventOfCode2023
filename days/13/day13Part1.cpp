#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

int findReflection(std::vector<std::string> pattern) {
    int i = 0;
    while (i < pattern.size() - 1) {
        int j = i;
        int k = i + 1;
        while (pattern[j] == pattern[k]) {
            j--;
            k++;
            if ((j < 0) || (k == pattern.size())) return i + 1;
        }
        i++;
    }
    return 0;
}

std::vector<std::string> invertPattern(std::vector<std::string> pattern) {
    std::vector<std::string> invertedPattern;
    for (int i = 0; i < pattern[0].size(); i++) {
        std::string line;
        for (int j = 0; j < pattern.size(); j++) {
            line += pattern[j][i];
        }
        invertedPattern.push_back(line);
    }
    return invertedPattern;
}

int main() {
    std::fstream input;
    input.open("test.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<std::string>> patterns;
    std::vector<std::string> pattern;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            if (!line.empty()) {
                pattern.push_back(line);
            } else {
                patterns.push_back(pattern);
                pattern = {};
            }
        }
    }
    patterns.push_back(pattern);
    input.close();

    int columns = 0;
    int rows = 0;
    for (int i = 0; i < patterns.size(); i++) {
        int value = findReflection(patterns[i]);
        if (value > 0) rows += value;
        else columns += findReflection(invertPattern(patterns[i]));
    }

    int total = 100 * rows + columns;
    std::cout << total;

}