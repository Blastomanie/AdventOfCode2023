#include <iostream>
#include <fstream>
#include <string>

void minColorBag(std::string bag, int *blue, int *red, int *green) {
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
    int minBlue = 0;
    int minRed = 0;
    int minGreen = 0;
    int bagBegin = game.find(":") + 2;
    int bagEnd = -2;
    while (bagEnd != std::string::npos) {
        bagBegin += (bagEnd + 2);
        bagEnd = game.substr(bagBegin).find(";");
        minColorBag(game.substr(bagBegin, bagEnd), &minBlue, &minRed, &minGreen);
    }
    return minBlue * minRed * minGreen;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    int total = 0;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            total += gameTotal(line);
        }
    }
    input.close();
    std::cout << total;
}