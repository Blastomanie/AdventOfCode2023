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

std::vector<std::vector<long long>> rangeCalc(std::vector<std::vector<std::vector<long long>>> seedsVector, int i, std::vector<std::vector<long long>> range) {
    std::vector<std::vector<long long>> output = range;
    std::vector<std::vector<long long>> neverAgain;
    for (int j = 0; j < seedsVector[i].size(); j++) {
        long long srcMin = seedsVector[i][j][1];
        long long srcMax = srcMin + seedsVector[i][j][2] - 1;
        std::vector<std::vector<long long>> newOutput;
        for (int k = 0; k < output.size(); k++) {
            long long begin = output[k][0];
            long long end = output[k][1];
            if (begin < srcMin) newOutput.push_back(std::vector<long long> {begin, (srcMin <= end ? srcMin - 1 : end)});
            if ((end >= srcMin) && (begin <= srcMax)) neverAgain.push_back(std::vector<long long> {(srcMin > begin ? srcMin : begin) + (seedsVector[i][j][0] - seedsVector[i][j][1]), (srcMax < end ? srcMax : end) + (seedsVector[i][j][0] - seedsVector[i][j][1])});
            if (end > srcMax) newOutput.push_back(std::vector<long long> {(srcMax > begin ? srcMax + 1: begin), end});
        }
        output = newOutput;
    }
    for (int j = 0; j < neverAgain.size(); j++) {
        output.push_back(neverAgain[j]);
    }
    return output;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
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

    std::vector<std::vector<long long>> seedsRange;
    for (int i = 0; i < seedsVector[0][0].size(); i += 2) {
        std::vector<long long> range {seedsVector[0][0][i], seedsVector[0][0][i] + seedsVector[0][0][i + 1] - 1};
        seedsRange.push_back(range);
    }

    std::vector<long long> minList;
    for (int i = 0; i < seedsRange.size(); i++) {
        std::vector<std::vector<long long>> range = seedsRange;
        for (int j = 1; j < seedsVector.size(); j++) {
            range = rangeCalc(seedsVector, j, range);
        }
        long long min = range[0][0];
        for (int j = 0; j < range.size(); j++) {
            min = min > range[j][0] ? range[j][0] : min;
        }
        minList.push_back(min);
    }
    
    std::cout << *min_element(minList.begin(), minList.end());
}