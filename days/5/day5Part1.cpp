#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

std::vector<long long> createVector(std::string entry) {
    std::vector<long long> output;
    int outputBegin = -1;
    int outputEnd = 0;
    while (outputEnd < entry.length()) {
        outputBegin += (outputEnd + 1);
        outputEnd = entry.substr(outputBegin).find(" ");
        long long value = std::stoll(entry.substr(outputBegin, outputEnd));
        output.push_back(value);
    }
    return output;
}

int main() {
    std::fstream input;
    input.open("test.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<std::vector<long long>>> seedsVector;
    std::vector<std::vector<long long>> convertVector;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            if (line.substr(0, line.find(":")).find("map") != std::string::npos) {
                seedsVector.push_back(convertVector);
                convertVector = {};
            } else if (!line.empty()) {
                int start = line.find(":") != std::string::npos ? line.find(":") + 2 : 0;
                std::vector<long long> seeds = createVector(line.substr(start));
                convertVector.push_back(seeds);
            }
        }
        seedsVector.push_back(convertVector);
    }
    input.close();
    
    for (int i = 0; i < seedsVector[0][0].size(); i++) {
        long long seed = seedsVector[0][0][i];
        for (int j = 1; j < seedsVector.size(); j++) {
            for (int k = 0; k < seedsVector[j].size(); k++) {
                long long min = seedsVector[j][k][1];
                long long max = min + seedsVector[j][k][2] - 1;
                if ((seed <= max) && (seed >= min)) {
                    seed += seedsVector[j][k][0] - seedsVector[j][k][1];
                    seedsVector[0][0][i] = seed;
                    break;
                }
            }
        }
    }
    
    std::cout << *min_element(seedsVector[0][0].begin(), seedsVector[0][0].end());
}