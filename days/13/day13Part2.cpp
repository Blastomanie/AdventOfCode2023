#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<std::vector<std::string>> halfPattern(std::vector<std::string> pattern, int i) {
    std::vector<std::string> topHalf;
    std::vector<std::string> bottomHalf;
    for (int j = 0; j < i; j++) {
        topHalf.insert(topHalf.begin(), pattern[j]);
    }
    for (int j = i; j < pattern.size(); j++) {
        bottomHalf.push_back(pattern[j]);
    }
    return {topHalf, bottomHalf};
}

int findReflection(std::vector<std::string> pattern) {
    int i = 1;
    while (i < pattern.size()) {
        std::vector<std::vector<std::string>> seperatedPattern = halfPattern(pattern, i);
        std::vector<std::string> topHalf = seperatedPattern[0];
        std::vector<std::string> bottomHalf = seperatedPattern[1];

        int min = topHalf.size() > bottomHalf.size() ? bottomHalf.size() : topHalf.size();
        int missCount = 0;

        for (int j = 0; j < min; j++) {
            for (int k = 0; k < pattern[0].length(); k++) {
                if (topHalf[j][k] != bottomHalf[j][k]) missCount++;
            }
        }
        if (missCount == 1) return i;
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
    input.open("input.txt", std::ios::in);
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