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

void getBeams(std::vector<std::string> contraption, std::map<std::pair<int, int>, std::vector<char>> &uniqueBeams, std::pair<int, int> start = {0, 0}, char heading = 'E') {
    bool isEnd = false;
    std::pair<int, int> coords = start;
    if ((coords.first >= 0) && (coords.first < contraption.size()) && (coords.second >= 0) && (coords.second < contraption[0].length())) {
        while (!isEnd && !(std::find(uniqueBeams[coords].begin(), uniqueBeams[coords].end(), heading) != uniqueBeams[coords].end())) {
            uniqueBeams[coords].push_back(heading);
            if (splitersDefinition.find({contraption[coords.first][coords.second], oppositeDirections[heading]}) != splitersDefinition.end()) {
                heading = splitersDefinition[{contraption[coords.first][coords.second], oppositeDirections[heading]}];
            } else {
                if (contraption[coords.first][coords.second] == '-') {
                    getBeams(contraption, uniqueBeams,{coords.first, coords.second + 1}, 'E');
                    heading = 'W';
                } else if (contraption[coords.first][coords.second] == '|') {
                    getBeams(contraption, uniqueBeams,{coords.first - 1, coords.second}, 'N');   
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

    std::map<std::pair<int, int>, std::vector<char>> uniqueBeams;
    getBeams(contraption, uniqueBeams);
    int max = uniqueBeams.size();
    for (int i = 0; i < contraption.size(); i++) {
        uniqueBeams.clear();
        getBeams(contraption, uniqueBeams, {i, 0});
        max = uniqueBeams.size() > max ? uniqueBeams.size() : max;
        uniqueBeams.clear();
        getBeams(contraption, uniqueBeams, {i, contraption[0].length()}, 'W');
        max = uniqueBeams.size() > max ? uniqueBeams.size() : max;
    }
    
    for (int i = 0; i < contraption[0].size(); i++) {
        uniqueBeams.clear();
        getBeams(contraption, uniqueBeams, {0, i}, 'S');
        max = uniqueBeams.size() > max ? uniqueBeams.size() : max;
        uniqueBeams.clear();
        getBeams(contraption, uniqueBeams, {contraption.size(), i}, 'N');
        max = uniqueBeams.size() > max ? uniqueBeams.size() : max;
    }

    std::cout << max;
}