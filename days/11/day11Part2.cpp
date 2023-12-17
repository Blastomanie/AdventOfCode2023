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

std::vector<std::vector<long>> expandUniverse(std::vector<std::vector<std::string>> entry) {
    std::vector<long> line;
    std::vector<long> colone;
    for (int i = 0; i < entry.size(); i++) {
        if (!checkGalaxy(entry[i])) line.push_back(i);
    }
    int k = 0;
    for (int i = 0; i < entry[0].size(); i++) {
        std::vector<std::string> temp;
        for (int j = 0; j < entry.size(); j++) {
            temp.push_back(entry[j][i]);
        }
        if (!checkGalaxy(temp)) {
            colone.push_back(i);
        }
    }
    return {line, colone};
}

std::vector<std::vector<long>> getCoordsGalaxies(std::vector<std::vector<std::string>> entry) {
    std::vector<std::vector<long>> output;
    for (int i = 0; i < entry.size(); i++) {
        for (int j = 0; j < entry[i].size(); j++) {
            if (entry[i][j] == "#") output.push_back({i, j});
        }
    }
    return output;
}

std::vector<long> getOffset(std::vector<std::vector<long>> entry, long indexI, long indexJ) {
    std::vector<long> output {0, 0};
    for (int i = 0; i < entry[0].size(); i++) {
        if (entry[0][i] < indexI) output[0]++;
    }
    for (int i = 0; i < entry[1].size(); i++) {
        if (entry[1][i] < indexJ) output[1]++;
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

    std::vector<std::vector<long>> expandedUniverse = expandUniverse(universe);
    std::vector<std::vector<long>> coordsGalaxies = getCoordsGalaxies(universe);

    long long total = 0;
    for (int i = 0; i < coordsGalaxies.size(); i++) {
        for (int j = i + 1; j < coordsGalaxies.size(); j++) {
            std::vector<long> offsetI = getOffset(expandedUniverse, coordsGalaxies[i][0], coordsGalaxies[i][1]);
            std::vector<long> offsetJ = getOffset(expandedUniverse, coordsGalaxies[j][0], coordsGalaxies[j][1]);
            total += (abs(coordsGalaxies[j][0] + offsetJ[0] * 999999 - coordsGalaxies[i][0] - offsetI[0] * 999999) + abs(coordsGalaxies[j][1] + offsetJ[1] * 999999 - coordsGalaxies[i][1] - offsetI[1] * 999999));
        }
    }

    std::cout << total;
}