#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <limits>

std::map<char, std::pair<uint64_t, uint64_t>> orientationCoordinates {
    {'0', {0, 1}},
    {'2', {0, -1}},
    {'3', {-1, 0}},
    {'1', {1, 0}}
};

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::pair<char, uint64_t>> digPlan;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            digPlan.push_back({line[line.length() - 2], std::stoull(line.substr(line.find("#") + 1, 5), nullptr, 16)});
        }
    }
    input.close();

    std::vector<std::pair<uint64_t, uint64_t>> points {{0, 0}};
    uint64_t i = 0;
    uint64_t perimeter = 0;
    for (std::pair<char, uint64_t> dig : digPlan) {
        std::pair<uint64_t, uint64_t> point;
        perimeter += dig.second;
        point.first = points[i].first + dig.second * orientationCoordinates[dig.first].first;
        point.second = points[i].second + dig.second * orientationCoordinates[dig.first].second;
        points.push_back(point);
        i++;
    }
    uint64_t area = 0;
    for (uint64_t i = 0; i < points.size(); i++) {
        if (i < points.size() - 1) area += (-points[i + 1].second * points[i].first + points[i].second * points[i + 1].first);
        else area += (-points[i].second * points[0].first + points[i].second * points[0].first);
    }

    std::cout << area / 2 + perimeter / 2 + 1;
}