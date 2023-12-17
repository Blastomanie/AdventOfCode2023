#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

int getHashCode(std::string seq) {
    int value = 0;
    for (char i : seq) {
        value += i;
        value *= 17;
        value %= 256;
    }
    return value;
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

    int total = 0;
    for (std::string seq : sequences) {
        total += getHashCode(seq);
    }

    std::cout << total;
}