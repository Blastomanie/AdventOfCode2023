#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    int total = 0;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            std::string number = "";
            for (int i = 0; i < line.length(); i++) {
                if (isdigit(line[i])) {
                    number += line[i];
                }
            }
            total += (std::stoi(number.substr(0,1))) * 10 + std::stoi(number.substr(number.length() - 1, number.length()));
        }
    }
    input.close();

    std::cout << total;
}