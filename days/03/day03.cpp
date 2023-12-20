#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../utils.h"

std::string alpha = "0123456789.";
std::string alphaNumbers = "0123456789";

std::string parse(std::string line) {
    return line;
}

void abstract(std::vector<std::string> schematic, int64_t &total, int i, int j, bool part1 = true) {
    std::vector<int64_t> numbers = {};
    for (int c_i = -1; c_i <= 1; c_i++) {
        for (int c_j = -1; c_j <= 1; c_j++) {
            if ((alphaNumbers.find(schematic[i + c_i][j + c_j]) != std::string::npos)) {
                int k = 0;
                std::string num = "";
                while ((alphaNumbers.find(schematic[i + c_i][j + c_j + k]) != std::string::npos)) {
                    if (j + c_j + k == 0) { break; } else { k--; }
                }
                if ((alphaNumbers.find(schematic[i + c_i][j + c_j + k]) == std::string::npos)) k++;
                while ((alphaNumbers.find(schematic[i + c_i][j + c_j + k]) != std::string::npos)) {
                    num += schematic[i + c_i][j + c_j + k];
                    k++;
                }
                int64_t value = std::stoll(num);
                if ((std::find(numbers.begin(), numbers.end(), value) == numbers.end())) {
                    numbers.push_back(value);
                    if (part1) total += value;
                }
            }
        }
    }
    if (!part1 && (numbers.size() == 2)) total += (numbers[0] * numbers[1]);
}

// PART 1

int64_t part_1(std::vector<std::string> schematic) {
    int64_t total = 0;
    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[i].length(); j++) {
            if ((alpha.find(schematic[i][j]) == std::string::npos)) {
                abstract(schematic, total, i, j);
            }
        }
    }
    return total;
}

// PART 2

int64_t part_2(std::vector<std::string> schematic) {
    int64_t total = 0;
    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[i].size(); j++) {
            if (schematic[i][j] == '*') {
                abstract(schematic, total, i, j, false);
            }
        }
    }
    return total;
}

int main() {
    std::vector<std::string> schematic = aoc::parseInput("input", parse);

    // PART 1

    std::vector<std::string> schematicTest = aoc::parseInput("test", parse);
    aoc::checkTest(part_1, 4361, schematicTest);
    aoc::showResult(part_1, 1, schematic);

    // PART 2

    aoc::checkTest(part_2, 467835, schematicTest);
    aoc::showResult(part_2, 2, schematic);
}