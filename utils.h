#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#ifndef NDEBUG
#   define assert(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define assert(condition, message) do { } while (false)
#endif


namespace aoc {

    template <typename T>
    std::vector<T> parseInput(std::string inputName, T (*func)(std::string), bool firstPart = true) {
        std::fstream input;
        input.open(inputName + ".txt", std::ios::in);
        std::vector<T> output;
        std::string line;
        if (input.is_open()) {
            while (std::getline(input, line)) {
                if (firstPart) {
                    if (line.empty()) break;
                    output.push_back(func(line));
                } else {
                    if (firstPart) output.push_back(func(line));
                    if (line.empty()) firstPart = !firstPart;
                }
            }
        }
        input.close();
        return output;
    }

    template <typename T2>
    std::map<std::string, std::vector<T2>> parseInput(std::string inputName, std::vector<T2> (*func)(std::string), bool firstPart = true) {
        std::fstream input;
        input.open(inputName + ".txt", std::ios::in);
        std::map<std::string, std::vector<T2>> output;
        std::string line;
        if (input.is_open()) {
            while (std::getline(input, line)) {
                if (firstPart) {
                    if (line.empty()) break;
                    if (firstPart) output[line.substr(0, line.find("{"))] = func(line.substr(line.find("{") + 1));
                } else {
                    if (firstPart) output[line.substr(0, line.find("{"))] = func(line.substr(line.find("{") + 1));
                    if (line.empty()) firstPart = !firstPart;
                }

            }
        }
        input.close();
        return output;
    }

    template <typename T, typename... Args>
    void showResult(T (*part)(Args...), int num, Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "==============================================================" << std::endl;
        std::cout << "The solution of part "<< num << " is : " << part(args...) << std::endl;
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;
        std::cout << "==============================================================" << std::endl;
    }

    template <typename T, typename... Args>
    void checkTest(T (*part)(Args...), int64_t value, Args... args) {
        T output = part(args...);
        assert(output == value, "excepted " << value << " but get " << output);
    }

}