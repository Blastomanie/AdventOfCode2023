#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include "../../utils.h"

std::string parse(std::string line) {
    return line;
}

// PART 1

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

struct data {
    int i;
    int j;

    bool operator==(const data &other) const {
        return i == other.i && j == other.j;
    }
};

std::pair<int, int> findS(std::vector<std::string> map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].length(); j++) {
            if (map[i][j] == 'S') return {i, j};
        } 
    }
    return {-1, -1};
}

bool notIn(std::vector<data> l, data comp) {
    for (data datas : l) {
        if (datas == comp) return false;
    }
    return true;
}

int64_t part_1(std::vector<std::string> map, int steps) {
    std::pair<int, int> Scoords = findS(map);
    std::vector<data> l {{Scoords.first, Scoords.second}};
    while (steps > 0) {
        int size = l.size();
        for (int i = 0; i < size; i++) {
            data one = l[0];
            l.erase(l.begin());
            for (std::map<char, std::pair<int, int>>::iterator it = coordsCardinalPoints.begin(); it != coordsCardinalPoints.end(); it++) {
                if (map[one.i + it->second.first][one.j + it->second.second] != '#' && notIn(l, {one.i + it->second.first, one.j + it->second.second})) {
                    l.push_back({one.i + it->second.first, one.j + it->second.second});
                }
            }
        }
        steps--;
    }
    return l.size();
}

// PART 2

int64_t part_2() {
    return 0;
}

int main() {
    std::vector<std::string> map = aoc::parseInput("input", parse);
    std::vector<std::string> mapTest = aoc::parseInput("test", parse);

    // PART 1

    // aoc::checkTest(part_1, 16, mapTest, 6);
    // aoc::showResult(part_1, 1, map, 64);

    // PART 2

    aoc::checkTest(part_1, 50, mapTest, 10);
    // aoc::showResult(part_2);
}