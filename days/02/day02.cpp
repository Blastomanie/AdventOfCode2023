#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../../utils.h"

std::map<std::string, int64_t> colors {{"blue", 14}, {"red", 12}, {"green", 13}};

std::string parse(std::string line) {
    return line;
}

// PART 1

bool colorBag(std::string bag) {
    int64_t colorBegin = -2;
    int64_t colorEnd = 0;
    while (colorEnd != std::string::npos) {
        colorBegin += (colorEnd + 2);
        colorEnd = bag.substr(colorBegin).find(",");
        std::string bagSubset = bag.substr(colorBegin, colorEnd);
        for (std::map<std::string, int64_t>::iterator it = colors.begin(); it != colors.end(); it++) {
            if (bagSubset.find(it->first) != std::string::npos) {
                if (std::stoll(bagSubset) > it->second ) return false;
                break;
            } 
        }
    }
    return true;
}

bool gameCorrect(std::string game) {
    int64_t bagBegin = game.find(":") + 2;
    int64_t bagEnd = -2;
    while (bagEnd != std::string::npos) {
        bagBegin += (bagEnd + 2);
        bagEnd = game.substr(bagBegin).find(";");
        if (!colorBag(game.substr(bagBegin, bagEnd))) return false;
    }
    return true;
}

int64_t part_1(std::vector<std::string> games) {
    int64_t total = 0;
    for (int i = 0; i < games.size(); i++) {
        total += gameCorrect(games[i]) ? i + 1 : 0;
    }
    return total;
}

//PART 2

void minColorBag(std::string bag, int64_t *blue, int64_t *red, int64_t *green) {
    int colorBegin = -2;
    int colorEnd = 0;
    while (colorEnd != std::string::npos) {
        colorBegin += (colorEnd + 2);
        colorEnd = bag.substr(colorBegin).find(",");
        std::string bagSubset = bag.substr(colorBegin, colorEnd);
        int value = std::stoi(bagSubset);
        if (bagSubset.find("blue") != std::string::npos) *blue = value > *blue ? value : *blue;
        else if (bagSubset.find("red") != std::string::npos) *red = value > *red ? value : *red;
        else if (bagSubset.find("green") != std::string::npos) *green = value > *green ? value : *green;
    }
}

int gameTotal(std::string game) {
    int64_t minBlue = 0;
    int64_t minRed = 0;
    int64_t minGreen = 0;
    int64_t bagBegin = game.find(":") + 2;
    int64_t bagEnd = -2;
    while (bagEnd != std::string::npos) {
        bagBegin += (bagEnd + 2);
        bagEnd = game.substr(bagBegin).find(";");
        minColorBag(game.substr(bagBegin, bagEnd), &minBlue, &minRed, &minGreen);
    }
    return minBlue * minRed * minGreen;
}

int64_t part_2(std::vector<std::string> games) {
    int64_t total = 0;
    for (std::string game : games) {
        total += gameTotal(game);
    }
    return total;
}

int main() {
    std::vector<std::string> games = aoc::parseInput("input", parse);
    
    // PART 1

    std::vector<std::string> gamesTest = aoc::parseInput("test", parse);
    aoc::checkTest(part_1, 8, gamesTest);
    aoc::showResult(part_1, 1, games);

    // PART 2

    aoc::checkTest(part_2, 2286, gamesTest);
    aoc::showResult(part_2, 2, games);
}