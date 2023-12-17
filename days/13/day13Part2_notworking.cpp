#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// NOT WORKING

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

std::vector<std::string> fixPattern(std::vector<std::string> pattern, bool inverted = false) {
    int valueAbove = findReflection(pattern);
    if (valueAbove > 0) {
        int valueBelow = pattern.size() - valueAbove;
        if (valueBelow > valueAbove) {
            std::vector<std::string> fixedPattern = pattern;
            for (int i = 0; i < valueBelow - valueAbove; i++) {
                fixedPattern.insert(fixedPattern.begin(), pattern[pattern.size() - (valueBelow - valueAbove) + i]);
            }
            return !inverted ? fixedPattern : invertPattern(fixedPattern);
        } else if (valueBelow < valueAbove) {
            std::vector<std::string> fixedPattern = pattern;
            for (int i = 0; i < valueAbove - valueBelow; i++) {
                fixedPattern.push_back(pattern[valueAbove - valueBelow - i - 1]);
            }
            return !inverted ? fixedPattern : invertPattern(fixedPattern);
        }
        return !inverted ? pattern : invertPattern(pattern);
    }
    return fixPattern(invertPattern(pattern), true);
}

std::vector<int> findBrokenReflection(std::vector<std::string> pattern) {
    std::vector<int> values {0, 0};
    std::vector<std::string> fixedPattern = fixPattern(pattern);
    // for (int i = 0; i < fixedPattern.size(); i++) {
    //     std::cout << fixedPattern[i] << std::endl;
    // }
    // std::cout << std::endl;
    bool first = findReflection(pattern) > 0;
    if (first) {
        for (int i = 0; i < fixedPattern.size(); i++) {
            for (int j = 0; j < fixedPattern[i].length(); j++) {
                std::vector<std::string> brokenPattern = fixedPattern;
                brokenPattern[i][j] = brokenPattern[i][j] == '.' ? '#' : '.';
                int value = findReflection(brokenPattern);
                if (value > 0) return {value, 0};
            }
        }
    }
    for (int i = 0; i < fixedPattern.size(); i++) {
        for (int j = 0; j < fixedPattern[i].length(); j++) {
            std::vector<std::string> brokenPattern = fixedPattern;
            brokenPattern[i][j] = brokenPattern[i][j] == '.' ? '#' : '.';
            int value = findReflection(invertPattern(brokenPattern));
            if (value > 0) return {value, 0};
        }
    }
    return values;
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

    std::vector<std::string> patterntest = fixPattern(patterns[0]);
    for (int i = 0; i < patterntest.size(); i++) {
        std::cout << patterntest[i] << std::endl;
    }

    int columns = 0;
    int rows = 0;
    for (int i = 0; i < patterns.size(); i++) {
        std::vector<int> t = findBrokenReflection(patterns[i]);
        rows += t[0];
        columns += t[1];
        std::cout << t[0] << " " << t[1] << std::endl;
    }

    int total = 100 * rows + columns;
    std::cout << total;

}