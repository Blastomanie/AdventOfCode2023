#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>

std::map<char, long> cardsValue {{'J', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'Q', 12}, {'K', 13}, {'A', 14}};

std::map<std::string, long> createVector(std::string entry) {
    std::map<std::string, long> output;
    int handEnd = entry.find(" ");
    output.insert({entry.substr(0, handEnd), std::stol(entry.substr(handEnd))});
    return output;
}

bool checkTwoHands(std::string firstHand, std::string secondHand) {
    int i = 0;
    while (i < 5) {
        if (cardsValue[firstHand[i]] < cardsValue[secondHand[i]]) return false;
        if (cardsValue[firstHand[i]] > cardsValue[secondHand[i]]) return true;
        i++;
    }
    return true;
}

int findIndex(std::vector<std::vector<long>> rankingHands, std::vector<std::map<std::string, long>> hands, std::vector<long> search) {
    int index = 0;
    for (int i = 0; i < rankingHands.size(); i++) {
        if ((rankingHands[i][0] < search[0])) {
            index++;
        } else if (rankingHands[i][0] == search[0]) {
            if (checkTwoHands(hands[rankingHands[i][1]].begin()->first, hands[search[1]].begin()->first)) return index;
            index++;
        } else return index;
    }
    return index;
}

void changement(std::vector<long> &test, long j) {
    int max = 0;
    for (int i = 0; i < test.size(); i++) {
        if (test[i] >= test[max]) max = i; 
    }
    test[max] += j;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    std::vector<std::map<std::string, long>> hands;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            hands.push_back(createVector(line)); 
        }
    }
    input.close();

    std::vector<std::vector<long>> rankingHands;
    for (int i = 0; i < hands.size(); i++) {
        for (std::map<std::string, long>::iterator itHands = hands[i].begin(); itHands != hands[i].end(); itHands++) {
            std::vector<long> setsHand;
            long j = 0;
            for (std::map<char, long>::iterator itSetHand = cardsValue.begin(); itSetHand != cardsValue.end(); itSetHand++) {
                long n = std::count(itHands->first.begin(), itHands->first.end(), itSetHand->first);
                if (n > 0 && itSetHand->first != 'J') setsHand.push_back(n);
                else if (n > 0 && itSetHand->first == 'J') j = n;
            }
            if (!setsHand.empty()) {changement(setsHand, j);} else {setsHand.push_back(j);};
            std::vector<std::vector<long>>::iterator itRankingHands = rankingHands.begin();
            if (setsHand[0] == 5) rankingHands.insert(std::next(itRankingHands, findIndex(rankingHands, hands, {6, i})), {6, i});
            else if (std::find(std::begin(setsHand), std::end(setsHand), 4) != std::end(setsHand)) rankingHands.insert(std::next(itRankingHands, findIndex(rankingHands, hands, {5, i})), {5, i});
            else if (std::find(std::begin(setsHand), std::end(setsHand), 3) != std::end(setsHand) && std::find(std::begin(setsHand), std::end(setsHand), 2) != std::end(setsHand)) rankingHands.insert(std::next(itRankingHands, findIndex(rankingHands, hands, {4, i})), {4, i});
            else if (std::find(std::begin(setsHand), std::end(setsHand), 3) != std::end(setsHand)) rankingHands.insert(std::next(itRankingHands, findIndex(rankingHands, hands, {3, i})), {3, i});
            else if ((setsHand[0] == 2 && setsHand[1] == 2) || (setsHand[0] == 2 && setsHand[2] == 2) || (setsHand[1] == 2 && setsHand[2] == 2)) rankingHands.insert(std::next(itRankingHands, findIndex(rankingHands, hands, {2, i})), {2, i});
            else if (std::find(std::begin(setsHand), std::end(setsHand), 2) != std::end(setsHand)) rankingHands.insert(std::next(itRankingHands, findIndex(rankingHands, hands, {1, i})), {1, i});
            else rankingHands.insert(std::next(itRankingHands, findIndex(rankingHands, hands, {0, i})), {0, i});
        }
    }

    long total = 0;
    for (int i = 0; i < rankingHands.size(); i++) {
        total += ((i + 1) * hands[rankingHands[i][1]].begin()->second);
    }

    std::cout << total;
}