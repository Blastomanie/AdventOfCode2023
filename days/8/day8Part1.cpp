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

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::map<std::string,std::vector<std::string>> nodes;
    std::string instructions;
    if (input.is_open()) {
        bool firstLine = true;
        while (std::getline(input, line)) {
            if (firstLine) {
                instructions = line;
                firstLine = false;
            } else if (!line.empty()) {
                nodes.insert({line.substr(0, 3), createVector(line)}); 
            }
        }
    }
    input.close();

    std::string node = "AAA";
    int i = 0;
    int total = 0;
    while (node != "ZZZ") {
        if (instructions[i] == 'L') {
            node = nodes[node][0];
        } else {
            node = nodes[node][1];
        }
        i++;
        if (i == instructions.size()) i = 0;
        total++;
    }

    std::cout << total;
}