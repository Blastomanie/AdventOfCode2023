#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

std::vector<std::string> invertPlatform(std::vector<std::string> platform) {
    std::vector<std::string> invertedPlatform;
    for (int i = 0; i < platform[0].size(); i++) {
        std::string line;
        for (int j = 0; j < platform.size(); j++) {
            line += platform[j][i];
        }
        invertedPlatform.push_back(line);
    }
    return invertedPlatform;
}

std::vector<std::pair<int, int>> get(std::string level) {
    std::vector<std::pair<int, int>> test;
    int count = 0;
    int j = 0;
    for (int i = 0; i < level.length(); i++) {
        if (level[i] == 'O') count++;
        else if (level[i] == '#') {
            test.push_back(std::make_pair(j, count));
            count = 0;
            j = i + 1;
        }
    }
    if (j < level.size()) test.push_back(std::make_pair(j, count));
    return test;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::string> platform;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            platform.push_back(line);
        }
    }
    input.close();

    std::vector<std::string> invP = invertPlatform(platform);
    int total = 0;
    int height = platform.size();
    for (int i = 0; i < invP.size(); i++) {
        std::vector<std::pair<int, int>> t = get(invP[i]);
        for (std::pair<int, int> j : t) {
            for (int k = 0; k < j.second; k++) {
                total += (height - k - j.first);
            }
        }
    }

    std::cout << total;

}