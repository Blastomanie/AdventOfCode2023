#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

std::vector<std::string> createVector(std::string entry) {
    std::vector<std::string> output;
    int outputBegin = 0;
    output.push_back(entry.substr(outputBegin, 1));
    while (outputBegin < entry.length() - 1) {
        outputBegin++;
        output.push_back(entry.substr(outputBegin, 1));
    }
    return output;
}

bool checkGalaxy(std::vector<std::string> entry) {
    for (int i = 0; i < entry.size(); i++) {
        if (entry[i] == "#") return true;
    }
    return false;
}

std::vector<std::vector<std::string>> expandUniverse(std::vector<std::vector<std::string>> entry) {
    std::vector<std::vector<std::string>> output;
    for (int i = 0; i < entry.size(); i++) {
        output.push_back(entry[i]);
        if (!checkGalaxy(entry[i])) output.push_back(entry[i]);
    }
    int k = 0;
    for (int i = 0; i < entry[0].size(); i++) {
        std::vector<std::string> temp;
        for (int j = 0; j < entry.size(); j++) {
            temp.push_back(entry[j][i]);
        }
        if (!checkGalaxy(temp)) {
            for (int j = 0; j < output.size(); j++) {
                output[j].insert(output[j].begin() + i + k, ".");
            }
            k++;
        }
    }
    return output;
}

std::vector<std::vector<int>> getCoordsGalaxies(std::vector<std::vector<std::string>> entry) {
    std::vector<std::vector<int>> output;
    for (int i = 0; i < entry.size(); i++) {
        for (int j = 0; j < entry[i].size(); j++) {
            if (entry[i][j] == "#") output.push_back({i, j});
        }
    }
    return output;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<std::string>> universe;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            universe.push_back(createVector(line));
        }
    }
    input.close();

    std::vector<std::vector<std::string>> expandedUniverse = expandUniverse(universe);

    std::vector<std::vector<int>> coordsGalaxies = getCoordsGalaxies(expandedUniverse);

    int total = 0;
    for (int i = 0; i < coordsGalaxies.size(); i++) {
        for (int j = i + 1; j < coordsGalaxies.size(); j++) {
            total += (abs(coordsGalaxies[j][0] - coordsGalaxies[i][0]) + abs(coordsGalaxies[j][1] - coordsGalaxies[i][1]));
        }
    }

    std::cout << total;
}