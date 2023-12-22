#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include "../../utils.h"

struct configuration {
    char mode;
    std::string module;
    std::vector<std::string> destinations;
};

configuration parse(std::string line) {
    configuration config;
    if (line[0] == 'b') {
        config.mode = 'b';
        config.module = line.substr(0, line.find("-") - 1);
    } else {
        config.mode = line[0];
        config.module = line.substr(1, line.find("-") - 2);
    }
    line = line.substr(line.find(">") + 1);
    int64_t pos = line.find(",");
    while (pos != std::string::npos) {
        config.destinations.push_back(line.substr(1, pos - 1));
        line.erase(0, pos + 1);
        pos = line.find(",");
    }
    config.destinations.push_back(line.substr(1));
    return config;
}

// PART 1

int64_t part_1() {
    return 0;
}

// PART 2

int64_t part_2() {
    return 0;
}

int main() {
    std::vector<configuration> module = aoc::parseInput("test", parse);

    // PART 1

    aoc::checkTest(part_1, 0);
    // aoc::showResult(part_1, 0);

    // PART 2

    // aoc::checkTest(part_2);
    // aoc::showResult(part_2);
}