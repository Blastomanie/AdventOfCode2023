#include <iostream>
#include <fstream>
#include <string>

void min_color_bag(std::string bag, int *blue, int *red, int *green) {
    int color_deb = 0;
    int color_fin = bag.find(",");
    std::string bag_subset;
    while (color_fin != std::string::npos) {
        bag_subset = bag.substr(color_deb, color_fin);
        int value = std::stoi(bag_subset);
        if (bag_subset.find("blue") != std::string::npos) *blue = value > *blue ? value : *blue;
        else if (bag_subset.find("red") != std::string::npos) *red = value > *red ? value : *red;
        else if (bag_subset.find("green") != std::string::npos) *green = value > *green ? value : *green;
        color_deb += (color_fin + 2);
        color_fin = bag.substr(color_deb).find(",");
    }
    bag_subset = bag.substr(color_deb, color_fin);
    int value = std::stoi(bag_subset);
    if (bag_subset.find("blue") != std::string::npos) *blue = value > *blue ? value : *blue;
    else if (bag_subset.find("red") != std::string::npos) *red = value > *red ? value : *red;
    else if (bag_subset.find("green") != std::string::npos) *green = value > *green ? value : *green;
}

int game_total(std::string game) {
    int min_blue, min_red, min_green = 0;
    int bag_deb = game.find(":") + 2;
    int bag_fin = game.find(";") - bag_deb;
    while (bag_fin != std::string::npos) {
        std::string bag = game.substr(bag_deb, bag_fin);
        min_color_bag(bag, &min_blue, &min_red, &min_green);
        bag_deb += (bag_fin + 2);
        bag_fin = game.substr(bag_deb).find(";");
    }
    min_color_bag(game.substr(bag_deb, bag_fin), &min_blue, &min_red, &min_green);
    return min_blue * min_red * min_green;
}

int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);
    std::string line;
    int total = 0;
    int id_game = 1;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            total += game_total(line);
            id_game++;
        }
    }
    input.close();
    std::cout << total;
}