#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include "../../utils.h"

struct rule_S {
    char part;
    char comparator;
    int64_t value;
    std::string destination;
};

std::map<char, char> contraryComp = {
    {'<', '>'},
    {'>', '<'}
};

std::vector<rule_S> parseRule(std::string line) {
    std::vector<rule_S> rules;
    int64_t outputEnd = 0;
    while (outputEnd != std::string::npos) {
        rule_S rule;
        int64_t outputBegin = 0;
        rule.part = line[outputBegin];
        rule.comparator = line[outputBegin + 1];
        int64_t found = line.substr(outputBegin).find(":");
        rule.value = std::stoll(line.substr(outputBegin + 2, found - 2));
        outputEnd = line.substr(found + 1).find_first_of(",");
        rule.destination = line.substr(found + 1, outputEnd);
        rules.push_back(rule);
        line = line.substr(line.find(",") + 1);
        if (!(line.find(",") != std::string::npos)) break;
    }
    rule_S rule;
    rule.destination = line.substr(0, line.length() - 1);
    rules.push_back(rule);
    return rules;
}

std::map<char, int64_t> parseRating(std::string line) {
    std::map<char, int64_t> rating;
    line = line.substr(1);
    while (line.length() > 0) {
        rating[line[0]] = std::stoll(line.substr(2, line.find(",") - 2));
        line = line.substr(line.find(",") + 1);
        if (!(line.find(",") != std::string::npos)) break;
    }
    rating[line[0]] = std::stoll(line.substr(2, line.length() - 2));
    return rating;
}

// PART 1

std::string workflowSelector(std::vector<rule_S> workflow, std::map<char, int64_t> rating) {
    for (int i = 0; i < workflow.size() - 1; i++) {
        int value = rating[workflow[i].part];
        if (workflow[i].comparator == '>') {
            if (value > workflow[i].value) return workflow[i].destination;
        } else {
            if (value < workflow[i].value) return workflow[i].destination;
        }
    }
    return workflow[workflow.size() - 1].destination;
}

int64_t part_1(std::map<std::string, std::vector<rule_S>> workflows, std::vector<std::map<char, int64_t>> ratings) {
    int64_t total = 0;
    for (std::map<char, int64_t> rating : ratings) {
        std::string enter = "in";
        while (enter != "A" && enter != "R") {
            std::vector<rule_S> workflow = workflows[enter];
            enter = workflowSelector(workflow, rating);
        }
        total += enter == "A" ? rating['x'] + rating['m'] + rating['a'] + rating['s'] : 0;
    }
    return total;
}

// PART 2

std::pair<std::string, int64_t> searchDestination(std::map<std::string, std::vector<rule_S>> workflows, std::string dest) {
    for (std::map<std::string, std::vector<rule_S>>::iterator it = workflows.begin(); it != workflows.end(); it++) {
        for (int64_t i = 0; i < it->second.size(); i++) {
            if (it->second[i].destination == dest) return {it->first, i};
        }
    }
    return {"NULL", 0};
}

int64_t calculateCombinations(std::map<char, std::vector<rule_S>> categories) {
    int64_t total = 1;
    for (std::map<char, std::vector<rule_S>>::iterator it = categories.begin(); it != categories.end(); it++) {
        std::vector<int64_t> l {4000, 0};
        for (int i = 0; i < it->second.size(); i++) {
            if (it->second[i].comparator == '<' && it->second[i].value < l[0]) l[0] = it->second[i].value;
            else if (it->second[i].comparator == '>' && it->second[i].value > l[1])  l[1] = it->second[i].value;
        }
        total *= abs(l[0] - l[1]);
    }
    return total * pow(4000, 4 - categories.size());
}

// This part can be optimized by saving the path if multiple A are present

int64_t calculateCombinationsWorkflow(std::map<std::string, std::vector<rule_S>> workflows, std::string from, std::vector<rule_S> ruleFrom) {
    int64_t total = 0;
    for (int i = 0; i < ruleFrom.size(); i++) {
        std::map<char, std::vector<rule_S>> categories;
        if (ruleFrom[i].destination == "A") {
            int64_t k = i;
            std::string enter = from;
            while (enter != "in") {
                std::vector<rule_S> rules = workflows[enter];
                for (int j = 0; j < k; j++) {
                    rule_S rule = rules[j];
                    rule.comparator = contraryComp[rule.comparator];
                    if (rule.comparator == '>') rule.value--;
                    categories[rule.part].push_back(rule);
                }
                if (k < rules.size() - 1) {
                    rule_S rule = rules[k];
                    if (rule.comparator == '<') rule.value--;
                    categories[rule.part].push_back(rule);
                }
                std::pair<std::string, int64_t> pe = searchDestination(workflows, enter);
                enter = pe.first;
                k = pe.second;
            }
            std::vector<rule_S> rules = workflows[enter];
            for (int j = 0; j < k; j++) {
                rule_S rule = rules[j];
                rule.comparator = contraryComp[rule.comparator];
                if (rule.comparator == '>') rule.value--;
                categories[rule.part].push_back(rule);
            }
            if (k < rules.size() - 1) {
                rule_S rule = rules[k];
                if (rule.comparator == '<') rule.value--;
                categories[rule.part].push_back(rule);
            }
            total += calculateCombinations(categories);
        }
    }
    return total;
}

int64_t part_2(std::map<std::string, std::vector<rule_S>> workflows) {
    int64_t total = 0;
    for (std::map<std::string, std::vector<rule_S>>::iterator it = workflows.begin(); it != workflows.end(); it++) {
        std::string from = it->first;
        std::vector<rule_S> rules = it->second;
        total += calculateCombinationsWorkflow(workflows, from, rules);
    }
    return total;
}

int main() {
    std::map<std::string, std::vector<rule_S>> workflows = aoc::parseInput("input", parseRule);
    std::vector<std::map<char, int64_t>> ratings = aoc::parseInput("input", parseRating, false);

    std::map<std::string, std::vector<rule_S>> workflowsTest = aoc::parseInput("test", parseRule);
    std::vector<std::map<char, int64_t>> ratingsTest = aoc::parseInput("test", parseRating, false);

    // PART 1

    aoc::checkTest(part_1, 19114, workflowsTest, ratingsTest);
    aoc::showResult(part_1, 1, workflows, ratings);

    // PART 2

    aoc::checkTest(part_2, 167409079868000, workflowsTest);
    aoc::showResult(part_2, 2, workflows);
}