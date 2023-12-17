#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>

int getHashCode(std::string seq) {
    int value = 0;
    for (char i : seq) {
        value += i;
        value *= 17;
        value %= 256;
    }
    return value;
}

int findInList(std::vector<std::pair<std::string, int>> seq, std::string label) {
    for (int i = 0; i < seq.size(); i++) {
        if (seq[i].first == label) return i;
    }
    return -1;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::string> sequences;
    std::string sequence;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] != ',') {
                    sequence += line[i];
                } else {
                    sequences.push_back(sequence);
                    sequence = "";
                }
            }
        }
    }
    sequences.push_back(sequence);
    input.close();

    std::vector<std::vector<std::pair<std::string, int>>> test(256);
    for (std::string seq : sequences) {
        int equalsIndex = seq.find("=");
        if (equalsIndex != std::string::npos) {
            std::string label = seq.substr(0, equalsIndex);
            int focal = std::stoi(seq.substr(equalsIndex + 1));
            int hashLabel = getHashCode(label);
            int i = findInList(test[hashLabel], label);
            if (i != -1) {
                test[hashLabel][i].second = focal;
            } else {
                test[hashLabel].push_back(std::make_pair(label, focal));
            }
        } else {
            std::string label = seq.substr(0, seq.length() - 1);
            int hashLabel = getHashCode(label);
            int i = findInList(test[hashLabel], label);
            if (i != -1) test[hashLabel].erase(test[hashLabel].begin() + i);
        }
    }

    int total = 0;
    for (int i = 0; i < test.size(); i++) {
        for (int j = 0; j < test[i].size(); j++) {
            total += ((i + 1) * (j + 1) * test[i][j].second);
        }
    }

    std::cout << total;
}