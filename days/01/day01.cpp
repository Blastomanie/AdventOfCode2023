#include <iostream>
#include <string>
#include <map>
#include "../../utils.h"

std::string parse(std::string line) {
    return line;
}

// PART 1

int64_t part_1(std::vector<std::string> numbers) {
    int64_t total = 0;
    for (std::string line : numbers) {
        std::string number = "";
        for (char c : line) {
            if (isdigit(c)) number += c;
        }
        total += (std::stoll(number.substr(0,1))) * 10 + std::stoll(number.substr(number.length() - 1, number.length()));
    }
    return total;
}

// PART 2

int64_t part_2(std::vector<std::string> numbers) {
    std::vector<std::string> convertNumber {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int64_t total = 0;
    for (std::string line : numbers) {
        std::string number = "";
        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) number += line[i];
            for (int j = 0; j < convertNumber.size(); j++) {
                if (line.substr(i, convertNumber[j].length()).find(convertNumber[j]) != std::string::npos) {
                    number += std::to_string(j);
                }
            }
        }
        total += (std::stoll(number.substr(0,1))) * 10 + std::stoll(number.substr(number.length() - 1, number.length()));
    }
    return total;
}

int main() {
    std::vector<std::string> numbers = aoc::parseInput("input", parse);
    
    // PART 1

    std::vector<std::string> numbersTest01 = aoc::parseInput("test01", parse);
    aoc::checkTest(part_1, 142, numbersTest01);
    aoc::showResult(part_1, 1, numbers);

    // PART 2

    std::vector<std::string> numbersTest02 = aoc::parseInput("test02", parse);
    aoc::checkTest(part_2, 281, numbersTest02);
    aoc::showResult(part_2, 2, numbers);
}