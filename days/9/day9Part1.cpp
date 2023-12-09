#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

std::string digits = "0123456789-";

std::vector<long long> createVector(std::string entry) {
    std::vector<long long> output;
    int outputBegin = 0;
    int outputEnd = 0;
    while (outputEnd < entry.length()) {
        outputBegin += (outputEnd + entry.substr(outputBegin + outputEnd).find_first_of(digits));
        outputEnd = entry.substr(outputBegin).find(" ");
        long long value = std::stoll(entry.substr(outputBegin, outputEnd));
        output.push_back(value);
    }
    return output;
}

bool verifyZero(std::vector<long long> entry) {
    for (int i = 0; i < entry.size(); i++) {
        if (entry[i] != 0) return false;
    }
    return true;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<long long>> history;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            history.push_back(createVector(line));
        }
    }
    input.close();

    long long total = 0;
    for (int i = 0; i < history.size(); i++) {
        std::vector<std::vector<long long>> dataSets;
        dataSets.push_back(history[i]);
        int last = 0;
        while (!verifyZero(dataSets[last])) {
            std::vector<long long> step;
            for (int j = 0; j < dataSets[last].size() - 1; j++) {
                step.push_back(dataSets[last][j + 1] - dataSets[last][j]);
            }
            last++;
            dataSets.push_back(step);
        }
        dataSets.back().push_back(0);
        for (int j = 1; j < dataSets.size(); j++) {
            dataSets[last - j].push_back(dataSets[last - j + 1].back() + dataSets[last - j].back());
        }
        total += dataSets[0].back();
    }

   std::cout << total;
}