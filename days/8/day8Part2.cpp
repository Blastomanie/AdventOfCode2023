#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

std::vector<std::string> createVector(std::string entry) {
    std::vector<std::string> output;
    output.push_back(entry.substr(entry.find("(") + 1, 3));
    output.push_back(entry.substr(entry.find(",") + 2, 3));
    return output;
}

long long gcd(long long a, long long b) {
    for(;;) {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

long long lcm(long long a, long long b) {
    return (a * b) / gcd(a, b);
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::map<std::string,std::vector<std::string>> nodes;
    std::string instructions;
    std::vector<std::string> startNodes;
    if (input.is_open()) {
        bool firstLine = true;
        while (std::getline(input, line)) {
            if (firstLine) {
                instructions = line;
                firstLine = false;
            } else if (!line.empty()) {
                if (line[2] == 'A') startNodes.push_back(line.substr(0, 3));
                nodes.insert({line.substr(0, 3), createVector(line)}); 
            }
        }
    }
    input.close();

    int j = 0;
    std::vector<long long> counters;
    for (int i = 0; i < startNodes.size(); i++) {
        counters.push_back(0);
        while (startNodes[i][2] != 'Z') {
            if (instructions[j] == 'L') {
                startNodes[i] = nodes[startNodes[i]][0];
            } else {
                startNodes[i] = nodes[startNodes[i]][1];
            }
            j++;
            if (j == instructions.size()) j = 0;
            counters[i]++;
        }
    }

    long long total = counters[0];
    for (int i = 1; i < counters.size(); i++) {
        total = lcm(total, counters[i]);
    }

    std::cout << total << std::endl;
}