#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <limits>

std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> coordsCardinalPoints {
    {{-1, 0}, {{0, 1}, {0, -1}}},
    {{0, 1}, {{-1, 0}, {1, 0}}},
    {{1, 0}, {{0, 1}, {0, -1}}},
    {{0, -1}, {{-1, 0}, {1, 0}}},
    {{0, 0}, {{0, 1}, {1, 0}}}
};

std::vector<int> createVector(std::string entry) {
    std::vector<int> output;
    int outputBegin = 0;
    while (outputBegin < entry.length()) {
        output.push_back(std::stoi(entry.substr(outputBegin, 1)));
        outputBegin++;
    }
    return output;
}

std::vector<std::pair<int, int>> getCoords(int lenI, int lenJ) {
    std::vector<std::pair<int, int>> output;
    for (int i = 0; i < lenI; i++) {
        for (int j = 0; j < lenJ; j++) {
            output.push_back({i, j});
        }
    }
    return output;
}

int getIndex(std::vector<std::pair<int, std::vector<std::pair<int, int>>>> nodes) {
    int min = std::numeric_limits<int>::max();
    int j = 0;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].first < min) {
            min = nodes[i].first;
            j = i;
        }
    }
    return j;
}

int dijkstra(std::vector<std::vector<int>> input) {
    std::pair<int, int> start = {0, 0};
    std::pair<int, int> stop = {input.size() - 1, input[0].size() - 1};
    std::map<std::vector<std::pair<int, int>>, int> distances {{{start, {0, 0}, {0, 0}}, 0}};
    std::vector<std::pair<int, std::vector<std::pair<int, int>>>> nodes {{{0, {start, {0, 0}, {0, 0}}}}};
    while (nodes.size() > 0) {
        int index = getIndex(nodes);
        int dist = nodes[index].first;
        std::vector<std::pair<int, int>> node1 = nodes[index].second;
        nodes.erase(nodes.begin() + index);
        if (node1[0] == stop) return dist;
        if (node1[1] != start && node1[2].first + 1 <= 3) {
            std::vector<std::pair<int, int>> node2 = node1;
            node2[0].first += node1[1].first;
            node2[0].second += node1[1].second;
            node2[2] = {node1[2].first + 1, 0};
            if ((node2[0].first >= 0) && (node2[0].first < input.size()) && (node2[0].second >= 0) && (node2[0].second < input[0].size())) {
                int d2 = distances.find(node2) == distances.end() ? std::numeric_limits<int>::max() : distances[node2];
                if (d2 > dist + input[node2[0].first][node2[0].second]) {
                    distances[node2] = dist + input[node2[0].first][node2[0].second];
                    nodes.push_back({dist + input[node2[0].first][node2[0].second], node2});
                }
            }
        }
        for (std::pair<int, int> head : coordsCardinalPoints[node1[1]]) {
            std::vector<std::pair<int, int>> node2 = node1;
            node2[0].first += head.first;
            node2[0].second += head.second;
            node2[1] = head;
            node2[2] = {1, 0};
            if ((node2[0].first >= 0) && (node2[0].first < input.size()) && (node2[0].second >= 0) && (node2[0].second < input[0].size())) {
                int d2 = distances.find(node2) == distances.end() ? std::numeric_limits<int>::max() : distances[node2];
                if (d2 > dist + input[node2[0].first][node2[0].second]) {
                    distances[node2] = dist + input[node2[0].first][node2[0].second];
                    nodes.push_back({dist + input[node2[0].first][node2[0].second], node2});
                }
            }
        }
    }
    return -1;
}

int main() {
    std::fstream input;
    input.open("test.txt", std::ios::in);
    std::string line;
    std::vector<std::vector<int>> blocks;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            blocks.push_back(createVector(line));
        }
    }
    input.close();

    std::cout << dijkstra(blocks);
}