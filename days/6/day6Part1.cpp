#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

std::string digits = "0123456789";

std::vector<double> createVector(std::string entry) {
    std::vector<double> output;
    int outputBegin = 0;
    int outputEnd = 0;
    while (outputEnd < entry.length()) {
        outputBegin += (outputEnd + entry.substr(outputBegin + outputEnd).find_first_of(digits));
        outputEnd = entry.substr(outputBegin).find(" ");
        float value = std::stod(entry.substr(outputBegin, outputEnd));
        output.push_back(value);
    }
    return output;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<double>> races;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            races.push_back(createVector(line.substr(line.find_first_of(digits)))); 
        }
    }
    input.close();

    long total = 1;
    for (int i = 0; i < races[0].size(); i++) {
        double time = races[0][i];
        double distance = races[1][i];
        double max = ceil(time / 2 + 0.5 * sqrt(time * time - 4 * distance) - 1);
        double min = floor(time / 2 - 0.5 * sqrt(time * time - 4 * distance) + 1);
        total *= (max - min + 1);
    }

    std::cout << total;
}