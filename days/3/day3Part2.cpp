#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> alpha {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
std::vector<std::string> alphaNumbers {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    int total = 0;
    std::vector<std::vector<std::string>> matrix;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            std::vector<std::string> matrixLine;
            for (int i = 0; i < line.length(); i++) {
                matrixLine.push_back(line.substr(i, 1));
            }
            matrix.push_back(matrixLine);
        }
    }
    input.close();

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == "*") {
                std::vector<int> numbers = {};
                for (int c_i = -1; c_i <= 1; c_i++) {
                    for (int c_j = -1; c_j <= 1; c_j++) {
                        if ((std::find(alphaNumbers.begin(), alphaNumbers.end(), matrix[i + c_i][j + c_j]) != alphaNumbers.end())) {
                            int k = 0;
                            std::string num = "";
                            while ((std::find(alphaNumbers.begin(), alphaNumbers.end(), matrix[i + c_i][j + c_j + k]) != alphaNumbers.end())) {
                                if (j + c_j + k == 0) { break; } else { k--; }
                            }
                            if (!(std::find(alphaNumbers.begin(), alphaNumbers.end(), matrix[i + c_i][j + c_j + k]) != alphaNumbers.end())) k++;
                            while ((std::find(alphaNumbers.begin(), alphaNumbers.end(), matrix[i + c_i][j + c_j + k]) != alphaNumbers.end())) {
                                num += matrix[i + c_i][j + c_j + k];
                                k++;
                            }
                            int value = std::stoi(num);
                            if (!(std::find(numbers.begin(), numbers.end(), value) != numbers.end())) {
                                numbers.push_back(value);
                            }
                        }
                    }
                }
                if (numbers.size() == 2) total += (numbers[0] * numbers[1]);
            }
        }
    }

    std::cout << total;
}