#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

std::map<std::string, std::vector<int>> coordsCardinalPoints {
    {"N", {-1, 0}},
    {"E", {0, 1}},
    {"S", {1, 0}},
    {"W", {0, -1}}
};

std::map<std::string, std::string> oppositeDirections {
    {"N", "S"},
    {"E", "W"},
    {"S", "N"},
    {"W", "E"}
};

std::map<std::string, std::vector<std::string>> pipesDefinition {
    {"|", {"N", "S"}},
    {"-", {"E", "W"}},
    {"J", {"N", "W"}},
    {"L", {"N", "E"}},
    {"F", {"E", "S"}},
    {"7", {"W", "S"}}
};

std::vector<std::string> createVector(std::string entry) {
    std::vector<std::string> output;
    int outputBegin = 0;
    while (outputBegin < entry.length()) {
        std::string tile = entry.substr(outputBegin, 1);
        outputBegin++;
        output.push_back(tile);
    }
    return output;
}

std::string nextPipeDirection(std::string pipe, std::string direction) {
    std::vector<std::string> pipeConnections = pipesDefinition[pipe];
    if (std::find(pipeConnections.begin(), pipeConnections.end(), oppositeDirections[direction]) != pipeConnections.end()) {
        if (oppositeDirections[direction] == pipeConnections[0]) return pipeConnections[1];
        return pipeConnections[0];
    } else {
        return "NULL";
    }
}

std::vector<int> getIndexStart(std::vector<std::vector<std::string>> entry) {
    for (int i = 0; i < entry.size(); i++) {
        for (int j = 0; j < entry[i].size(); j++) {
            if (entry[i][j] == "S") return {i, j};
        }
    }
    return {-1, -1};
}

std::vector<std::string> findStartConnections(std::vector<std::vector<std::string>> entry, int indexI, int indexJ) {
    std::vector<std::string> directions = {"N", "E", "S", "W"};
    std::vector<std::string> startConnections;
    for (std::string direction : directions) {
        if ((indexI + coordsCardinalPoints[direction][0] > 0) && (indexI + coordsCardinalPoints[direction][0] < entry.size()) && (indexJ + coordsCardinalPoints[direction][1] > 0) && (indexJ + coordsCardinalPoints[direction][1] < entry[0].size())) {
            std::vector<std::string> nextPipe = pipesDefinition[entry[indexI + coordsCardinalPoints[direction][0]][indexJ + coordsCardinalPoints[direction][1]]];
            if (std::find(nextPipe.begin(), nextPipe.end(), oppositeDirections[direction]) != nextPipe.end()) startConnections.push_back(direction);
        }
    }
    return startConnections;
}

std::vector<std::vector<int>> findPath(std::vector<std::vector<std::string>> entry, std::vector<int> start, std::string direction) {
    std::vector<int> pos = start;
    std::vector<std::vector<int>> path;
    for(;;) {
        path.push_back(pos);
        pos[0] += coordsCardinalPoints[direction][0];
        pos[1] += coordsCardinalPoints[direction][1];
        if (entry[pos[0]][pos[1]] == "S") {
            return path;
        }
        direction = nextPipeDirection(entry[pos[0]][pos[1]], direction);
    }
    return path;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<std::string>> maze;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            maze.push_back(createVector(line));
        }
    }
    input.close();

    std::vector<int> startCoordinates = getIndexStart(maze);
    std::vector<std::string> startDirections = findStartConnections(maze, startCoordinates[0], startCoordinates[1]);
    std::vector<std::vector<std::string>> newMaze = maze;

    for (int i = 0; i < startDirections.size(); i++) {
        std::vector<std::vector<int>> path = findPath(maze, startCoordinates, startDirections[i]);
        for (int indexI = 0; indexI < newMaze.size(); indexI++) {
            for (int indexJ = 0; indexJ < newMaze[indexI].size(); indexJ++) {
                std::vector<int> t {indexI, indexJ};
                if (!(std::find(path.begin(), path.end(), t) != path.end())) {
                    newMaze[indexI][indexJ] = ".";
                }
            }
        }
    }

    for (std::map<std::string, std::vector<std::string>>::iterator it = pipesDefinition.begin(); it != pipesDefinition.end(); it++) {
        if ((std::find(it->second.begin(), it->second.end(), startDirections[0]) != it->second.end()) && (std::find(it->second.begin(), it->second.end(), startDirections[1]) != it->second.end())) {
            newMaze[startCoordinates[0]][startCoordinates[1]] = it->first;
        }
    }

    bool isEnclosed = false;
    int total = 0;
    std::string test = "|LJ";
    for (int i = 0; i < newMaze.size(); i++) {
        for (int j = 0; j < newMaze[i].size(); j++) {
            if (test.find(newMaze[i][j]) != std::string::npos) {
                isEnclosed = !isEnclosed;
            }
            if ((newMaze[i][j] == ".") && isEnclosed) {
                total++;
            }
        }
    }
    
    std::cout << total;
}