#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>

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

std::vector<std::pair<int, int>> get(std::string level, char comp) {
    std::vector<std::pair<int, int>> test;
    int count = 0;
    int j = 0;
    for (int i = 0; i < level.length(); i++) {
        if (level[i] == comp) count++;
        else if (level[i] == '#') {
            if (i != 0) test.push_back(std::make_pair(j, count));
            count = 0;
            j = i + 1;
        }
    }
    test.push_back(std::make_pair(j, count));
    return test;
}

std::vector<std::string> modify(std::vector<std::string> platform, std::string comp) {
    std::vector<std::string> output;
    for (int i = 0; i < platform.size(); i++) {
        std::string oui;
        std::vector<std::pair<int, int>> t = get(platform[i], comp[0]);
        for (int j = 0; j < t.size(); j++) {
            if (t[j].first - 1 >= 0) {
                oui += "#";
            }
            int number = t[j].second;
            int end = j + 1 < t.size() ? (t[j + 1].first - t[j].first - 1) - number : platform[0].length() - (number + t[j].first);
            for (int k = 0; k < number; k++) {
                oui += comp[0];
            }
            for (int k = 0; k < end; k++) {
                oui += comp[1];
            }
        }
        output.push_back(oui);
    }
    return output;
}

std::vector<std::string> cycle(std::vector<std::string> platform) {
    for (std::string c : {"O.", ".O"}) {
        platform = invertPlatform(modify(invertPlatform(platform), c));
        platform = modify(platform, c);
    }
    return platform;
}

long findIndex(std::vector<std::vector<std::string>> cycleList, std::vector<std::string> t) {
    for (int i = 0; i < cycleList.size(); i++) {
        if (cycleList[i] == t) return i;
    }
    return -1;
}

std::vector<std::string> findCycle(std::vector<std::string> platform, long cycles) {
    int j = 0;
    long beginCycle = -1;
    std::vector<std::vector<std::string>> cycl;
    bool findCycle = false;
    cycl.push_back(platform);
    while (!findCycle && j < cycles) {
        j++;
        platform = cycle(platform);
        beginCycle = findIndex(cycl, platform);
        if (beginCycle != -1) {
            findCycle = true;
        } else {
            cycl.push_back(platform);
        }
    }
    return cycl[(cycles - beginCycle) % (j - beginCycle) + beginCycle];
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

    std::vector<std::string> mod = findCycle(platform, 1000000000);
    int height = mod.size();
    int total = 0;
    for (int i = 0; i < height; i++) {
        total += (height - i) * std::count(mod[i].begin(), mod[i].end(), 'O');
    }

    std::cout << total;
}