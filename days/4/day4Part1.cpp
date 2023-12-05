#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

std::vector<int> deck(std::string num) {
    std::vector<int> numbers;
    int deckBegin = 0;
    while (deckBegin < num.length()) {
        int value = std::stoi(num.substr(deckBegin, 2));
        numbers.push_back(value);
        deckBegin += 3;
    }
    return numbers;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    int total = 0;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            std::vector<int> numbers, winningNumbers;
            int n = 0;
            int deb = line.find(":") + 2;
            int end = line.find("|");
            numbers = deck(line.substr(deb, end - deb));
            winningNumbers = deck(line.substr(end + 2));
            for (int i = 0; i < numbers.size(); i++) {
                if (std::find(winningNumbers.begin(), winningNumbers.end(), numbers[i]) != winningNumbers.end()) n++;
            }
            total += n == 0 ? 0 : pow(2, n - 1);
        }
    }
    input.close();
    
    std::cout << total;
}