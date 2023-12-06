#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::string digits = "0123456789";

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<double> race;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            race.push_back(std::stod(line.substr(line.find_first_of(digits)))); 
        }
    }
    input.close();

    double time = race[0];
    double distance = race[1];
    double max = ceil(time / 2 + 0.5 * sqrt(time * time - 4 * distance) - 1);
    double min = floor(time / 2 - 0.5 * sqrt(time * time - 4 * distance) + 1);
    long total = (max - min + 1);

    std::cout << total;
}