#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string, int> colors {{"blue", 14}, {"red", 12}, {"green", 13}};

bool colorBag(std::string bag) {
    int colorBegin = -2;
    int colorEnd = 0;
    while (colorEnd != std::string::npos) {
        colorBegin += (colorEnd + 2);
        colorEnd = bag.substr(colorBegin).find(",");
        std::string bagSubset = bag.substr(colorBegin, colorEnd);
        for (std::map<std::string, int>::iterator it = colors.begin(); it != colors.end(); it++) {
            if (bagSubset.find(it->first) != std::string::npos) {
                if (std::stoi(bagSubset) > it->second ) return false;
                break;
            } 
        }
    }
    return true;
}

bool gameCorrect(std::string game) {
    int bagBegin = game.find(":") + 2;
    int bagEnd = -2;
    while (bagEnd != std::string::npos) {
        bagBegin += (bagEnd + 2);
        bagEnd = game.substr(bagBegin).find(";");
        if (!colorBag(game.substr(bagBegin, bagEnd))) return false;
    }
    return true;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    int total = 0;
    int idGame = 1;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            total += gameCorrect(line) ? idGame : 0;
            idGame++;
        }
    }
    input.close();
    std::cout << total;
}