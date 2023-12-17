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

std::vector<std::vector<int>> init(std::vector<std::vector<int>> input, std::pair<int, int> deb) {
    std::vector<std::vector<int>> output;
    for (int i = 0; i < input.size(); i++) {
        std::vector<int> line;
        for (int j = 0; j < input[i].size(); j++) {
            line.push_back(std::numeric_limits<int>::max());
        }
        output.push_back(line);
    }
    output[deb.first][deb.second] = 0;
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

int getIndex(std::vector<std::vector<int>> distances, std::vector<std::pair<int, int>> nodes) {
    int min = std::numeric_limits<int>::max();
    int j = 0;
    for (int i = 0; i < nodes.size(); i++) {
        if (distances[nodes[i].first][nodes[i].second] < min) {
            min = distances[nodes[i].first][nodes[i].second];
            j = i;
        }
    }
    return j;
}

void majDistance(std::vector<std::vector<int>> weight, std::vector<std::vector<int>> &distances, std::pair<int, int> node1, std::pair<int, int> node2) {
    if (distances[node2.first][node2.second] > distances[node1.first][node1.second] + weight[node2.first][node2.second]) {
        std::cout <<"new " << node2.first << " " << node2.second << std::endl;
        distances[node2.first][node2.second] = distances[node1.first][node1.second] + weight[node2.first][node2.second];
    }
}

int dijkstra(std::vector<std::vector<int>> input) {
    std::pair<int, int> start = {0, 0};
    std::vector<std::vector<int>> distances = init(input, start);
    std::vector<std::pair<int, int>> nodes = getCoords(input.size(), input[0].size());
    std::map<std::pair<int, int>, std::pair<std::pair<int, int>, int>> prev;
    std::pair<int, int> stop = {input.size() - 1, input[0].size() - 1};
    while (nodes.size() > 0) {
        int index = getIndex(distances, nodes);
        std::pair<int, int> node1 = nodes[index];
        nodes.erase(nodes.begin() + index);
        std::cout << node1.first << " " << node1.second <<  " " << prev[node1].first.first << " " << prev[node1].first.second << " " << prev[node1].second << std::endl;
        if (node1 == stop) return distances[node1.first][node1.second];
        std::pair<int, int> heading = {node1.first - prev[node1].first.first, node1.second - prev[node1].first.second};
        std::cout << "heading " << heading.first << " " << heading.second << std::endl;
        if (heading != start && prev[node1].second + 1 <= 3) {
            std::pair<int, int> node2 = node1;
            node2.first += heading.first;
            node2.second += heading.second;
            std::cout << "inf " << node2.first << " " << node2.second << std::endl;
            if ((node2.first >= 0) && (node2.first < input.size()) && (node2.second >= 0) && (node2.second < input[0].size()) && std::find(nodes.begin(), nodes.end(), node2) != nodes.end()) {
                prev[node2].first = node1;
                prev[node2].second = prev[node1].second + 1;
                majDistance(input, distances, node1, node2);
            }
        }
        for (std::pair<int, int> head : coordsCardinalPoints[heading]) {
            std::pair<int, int> node2 = node1;
            node2.first += head.first;
            node2.second += head.second;
            std::cout << "pas inf " << node2.first << " " << node2.second << std::endl;
            if ((node2.first >= 0) && (node2.first < input.size()) && (node2.second >= 0) && (node2.second < input[0].size()) && std::find(nodes.begin(), nodes.end(), node2) != nodes.end()) {
                prev[node2].first = node1;
                prev[node2].second = 1;
                majDistance(input, distances, node1, node2);
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

    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[0].size(); j++) {
            std::cout << blocks[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << dijkstra(blocks);
}