#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string, std::string> convertNumber {{"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};

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
                for (std::map<std::string, std::string>::iterator it = convertNumber.begin(); it != convertNumber.end(); it++) {
                    if (line.substr(i, it->first.length()).find(it->first) != std::string::npos) {
                        number += it->second;
                    }
                }
            }
            total += (std::stoi(number.substr(0,1))) * 10 + std::stoi(number.substr(number.length() - 1, number.length()));
        }
    }
    input.close();
    
    std::cout << total;
}