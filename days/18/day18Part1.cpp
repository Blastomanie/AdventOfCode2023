#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <limits>

/* Use the Shoelace formula to determine the area :
* 2 * area = sum det ([[x_i x_(i+1)], [y_i y_(i+1)]]) for i (0, n) number of points and n + 1 = 0 
* This formula does not calculate the all surface of this problem but needs also a part of the boundary (perimeter / 2 + 1)
*/

std::map<char, std::pair<int, int>> orientationCoordinates {
    {'R', {0, 1}},
    {'L', {0, -1}},
    {'U', {-1, 0}},
    {'D', {1, 0}}
};

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::pair<char, int>> digPlan;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            digPlan.push_back({line[0], std::stoi(line.substr(2, line.substr(2).find(" ")))});
        }
    }
    input.close();

    std::vector<std::pair<int, int>> points {{0, 0}};
    int i = 0;
    int perimeter = 0;
    for (std::pair<char, int> dig : digPlan) {
        std::pair<int, int> point;
        perimeter += dig.second;
        point.first = points[i].first + dig.second * orientationCoordinates[dig.first].first;
        point.second = points[i].second + dig.second * orientationCoordinates[dig.first].second;
        points.push_back(point);
        i++;
    }

    int area = 0;
    for (int i = 0; i < points.size(); i++) {
        if (i < points.size() - 1) area += (points[i + 1].second * points[i].first - points[i].second * points[i + 1].first);
        else area += (points[i].second * points[0].first - points[i].second * points[0].first);
    }

    std::cout << abs(area) / 2 + perimeter / 2 + 1;
}