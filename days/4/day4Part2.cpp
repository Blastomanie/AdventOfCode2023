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
    std::vector<std::vector<int>> cards, winningCards;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            std::vector<int> numbers, winningNumbers;
            int deb = line.find(":") + 2;
            int end = line.find("|");
            numbers = deck(line.substr(deb, end - deb));
            winningNumbers = deck(line.substr(end + 2));
            cards.push_back(numbers);
            winningCards.push_back(winningNumbers);
        }
    }
    input.close();

    std::vector<int> instances;
    for (int i = 0; i < cards.size(); i++) {
        instances.push_back(1);
    }

    for (int i = 0; i < cards.size(); i++) {
        int n = 0;
        for (int j = 0; j < cards[i].size(); j++) {
            if (std::find(winningCards[i].begin(), winningCards[i].end(), cards[i][j]) != winningCards[i].end()) {
                n++;
                if (i + n < instances.size()) instances[i + n] += instances[i];
            }
        }
    }
    for (int i = 0; i < instances.size(); i++) {
        total += instances[i];
    }
    
    std::cout << total;
}