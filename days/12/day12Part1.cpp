#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

std::string digits = "0123456789";

std::vector<long long> createVector(std::string entry) {
    std::vector<long long> output;
    int outputBegin = 0;
    int outputEnd = 0;
    while (outputEnd < entry.length()) {
        outputBegin += (outputEnd + entry.substr(outputBegin + outputEnd).find_first_of(digits));
        outputEnd = entry.substr(outputBegin).find(",");
        output.push_back(std::stoll(entry.substr(outputBegin, outputEnd)));
    }
    return output;
}

std::vector<long long> notFirst(std::vector<long long> input) {
    std::vector<long long> list;
    for (int i = 1; i < input.size(); i++) {
        list.push_back(input[i]);
    }
    return list;
}

std::map<std::pair<std::string, std::vector<long long>>, long long> cache;

long long get(std::string row, std::vector<long long> groups) {
    if (groups.size() == 0) {
        return !(row.find("#") != std::string::npos);
    }
    row = row.find_first_of("?#") != std::string::npos ? row.substr(row.find_first_of("?#")) : "";
    if (row.length() == 0) return groups.size() == 0;
    char c = row[0];
    long long group = groups[0];
    if (c == '#') {
        if (row.length() < group || row.substr(0, group).find('.') != std::string::npos) return 0;
        else if (row.length() == group) return groups.size() == 1;
        else if (row[group] == '#') return 0;
        else {
            if (cache.find({row.substr(group + 1), notFirst(groups)}) != cache.end()) return cache[{row.substr(group + 1), notFirst(groups)}];
            cache[{row.substr(group + 1), notFirst(groups)}] = get(row.substr(group + 1), notFirst(groups));
            return cache[{row.substr(group + 1), notFirst(groups)}];
        }
    }
    if (!(cache.find({(row.length() - 1 > 0) ? '#' + row.substr(1) : "#", groups}) != cache.end())) cache[{(row.length() - 1 > 0) ? '#' + row.substr(1) : "#", groups}] = get((row.length() - 1 > 0) ? '#' + row.substr(1) : "#", groups);
    if (!(cache.find({row.length() - 1 > 0 ? row.substr(1) : "", groups}) != cache.end())) cache[{row.length() - 1 > 0 ? row.substr(1) : "", groups}] = get(row.length() - 1 > 0 ? row.substr(1) : "", groups);
    return cache[{(row.length() - 1 > 0) ? '#' + row.substr(1) : "#", groups}] + cache[{row.length() - 1 > 0 ? row.substr(1) : "", groups}];
}

std::string repeat(std::string t, char c) {
    std::string s;
    s += t;
    for (int i = 0; i < 4; i++) {
        s += c;
        s += t;
    }
    return s;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::string> rows;
    std::vector<std::vector<long long>> groups;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            rows.push_back(repeat(line.substr(0, line.find_first_of(" ")), '?'));
            groups.push_back(createVector(repeat(line.substr(line.find_first_of(" ") + 1), ',')));
        }
    }
    input.close();

    long long total = 0;
    for (long long i = 0; i < rows.size(); i++) {
        total += get(rows[i], groups[i]);
    }
    std::cout << total;
}