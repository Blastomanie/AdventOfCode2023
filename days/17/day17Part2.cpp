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

struct entry {
    std::pair<int, int> coords;
    std::pair<int, int> dir;
    int count;

    bool operator==(const entry &a) const {
        return coords == a.coords && dir == a.dir && count == a.count;
    }

    bool operator<(const entry &a) const {
        if (coords != a.coords) return coords < a.coords;
        if (dir != a.dir) return dir < a.dir;
        return count < a.count;
    }
};

struct nodeEntry {
    int count;
    entry node;

    bool operator==(const nodeEntry &a) const {
        return count == a.count && node == a.node;
    }

    bool operator<(const nodeEntry &a) const {
        if (count != a.count) return count < a.count;
        return node < a.node;
    }

};

int getIndex(std::vector<std::pair<int, entry>> nodes) {
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

int dijkstra(std::vector<std::vector<int>> blocks) {
    std::pair<int, int> start = {0, 0};
    std::pair<int, int> stop = {blocks.size() - 1, blocks[0].size() - 1};
    std::map<entry, int> distances {{{start, {0, 0}, 0}, 0}};
    std::vector<nodeEntry> nodes {{{0, {start, {0, 0}, 0}}}};
    while (nodes.size() > 0) {
        int dist = nodes[0].count;
        entry node1 = nodes[0].node;
        nodes.erase(nodes.begin());
        if (node1.coords == stop) return dist;
        if (node1.dir != start && node1.count + 1 <= 10) {
            entry node2 = node1;
            node2.coords.first += node1.dir.first;
            node2.coords.second += node1.dir.second;
            node2.count = node1.count + 1;
            if ((node2.coords.first >= 0) && (node2.coords.first < blocks.size()) && (node2.coords.second >= 0) && (node2.coords.second < blocks[0].size())) {
                int d2 = distances.find(node2) == distances.end() ? std::numeric_limits<int>::max() : distances[node2];
                if (d2 > dist + blocks[node2.coords.first][node2.coords.second]) {
                    distances[node2] = dist + blocks[node2.coords.first][node2.coords.second];
                    nodeEntry val;
                    val.count = dist + blocks[node2.coords.first][node2.coords.second];
                    val.node = node2;
                    std::vector<nodeEntry>::iterator it = std::lower_bound(nodes.begin(), nodes.end(), val);
                    nodes.insert(it, val);
                }
            }
        }
        for (std::pair<int, int> head : coordsCardinalPoints[node1.dir]) {
            entry node2 = node1;
            node2.coords.first += head.first * 4;
            node2.coords.second += head.second * 4;
            node2.dir = head;
            node2.count = 4;
            if ((node2.coords.first >= 0) && (node2.coords.first < blocks.size()) && (node2.coords.second >= 0) && (node2.coords.second < blocks[0].size())) {
                int d2 = distances.find(node2) == distances.end() ? std::numeric_limits<int>::max() : distances[node2];
                int d = 0;
                for (int i = 1; i <= 4; i++) {
                    d += blocks[node1.coords.first + head.first * i][node1.coords.second + head.second * i];
                }
                if (d2 > dist + d) {
                    distances[node2] = dist + d;
                    nodeEntry val;
                    val.count = dist + blocks[node2.coords.first][node2.coords.second];
                    val.node = node2;
                    std::vector<nodeEntry>::iterator it = std::lower_bound(nodes.begin(), nodes.end(), val);
                    nodes.insert(it, val);
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

    // std::vector<int> test = {};
    // int val = 4;
    // auto it = std::lower_bound(test.begin(), test.end(), val);
    // test.insert(it, val);

    // for (int j : test) {
    //     std::cout << j << " ";
    // }

}