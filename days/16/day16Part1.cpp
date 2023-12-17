#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>

std::map<char, std::pair<int, int>> coordsCardinalPoints {
    {'N', {-1, 0}},
    {'E', {0, 1}},
    {'S', {1, 0}},
    {'W', {0, -1}}
};

std::map<char, char> oppositeDirections {
    {'N', 'S'},
    {'E', 'W'},
    {'S', 'N'},
    {'W', 'E'}
};

std::map<std::pair<char, char>, char> splitersDefinition {
    {{'/', 'N'}, 'W'},
    {{'/', 'W'}, 'N'},
    {{'/', 'E'}, 'S'},
    {{'/', 'S'}, 'E'},
    {{'\\', 'N'}, 'E'},
    {{'\\', 'E'}, 'N'},
    {{'\\', 'W'}, 'S'},
    {{'\\', 'S'}, 'W'},
    {{'-', 'E'}, 'W'},
    {{'-', 'W'}, 'E'},
    {{'|', 'N'}, 'S'},
    {{'|', 'S'}, 'N'}
};

std::map<std::pair<int, int>, std::vector<char>> uniqueBeams;

void getBeams(std::vector<std::string> contraption, std::pair<int, int> start = {0, 0}, char heading = 'E') {
    bool isEnd = false;
    std::pair<int, int> coords = start;
    if ((coords.first >= 0) && (coords.first < contraption.size()) && (coords.second >= 0) && (coords.second < contraption[0].length())) {
        while (!isEnd && !(std::find(uniqueBeams[coords].begin(), uniqueBeams[coords].end(), heading) != uniqueBeams[coords].end())) {
            uniqueBeams[coords].push_back(heading);
            if (splitersDefinition.find({contraption[coords.first][coords.second], oppositeDirections[heading]}) != splitersDefinition.end()) {
                heading = splitersDefinition[{contraption[coords.first][coords.second], oppositeDirections[heading]}];
            } else {
                if (contraption[coords.first][coords.second] == '-') {
                    getBeams(contraption, {coords.first, coords.second + 1}, 'E');
                    heading = 'W';
                } else if (contraption[coords.first][coords.second] == '|') {
                    getBeams(contraption, {coords.first - 1, coords.second}, 'N');   
                    heading = 'S';
                }
            }
            coords.first += coordsCardinalPoints[heading].first;
            coords.second += coordsCardinalPoints[heading].second;
            if ((coords.first < 0) || (coords.first >= contraption.size()) || (coords.second < 0) || (coords.second >= contraption[0].length())) {
                isEnd = true;
            }
        }
    }
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::string> contraption;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            contraption.push_back(line);
        }
    }
    input.close();

    getBeams(contraption);
    
    std::cout << uniqueBeams.size() << std::endl;
}