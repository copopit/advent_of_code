#include <iostream>
#include <stack>

#include "../utils/library.h"

auto moveSingleCrate() -> std::string {
    auto crates = readInputToStringVector("crates.txt");

    std::vector<std::stack<char>> stackCrates(crates[0].size());

    for (int i = crates.size()-1; i >= 0; i--)
        for (int j = 0; j < crates[i].size(); j++)
            if (crates[i][j] != ' ') {
                stackCrates[j].push(crates[i][j]);
            }

    auto moves = readInputToStringVector("moves.txt");

    for (auto& move : moves) {
        auto [n, fromTo] = splitString(move, ',');
        auto [s_from, s_to] = splitString(fromTo, ':');

        auto from = std::stoi(s_from) - 1, to = std::stoi(s_to) - 1;

        for (int i = 0; i < std::stoi(n); i++) {
            auto fromValue = stackCrates[from].top();
            stackCrates[from].pop();
            stackCrates[to].push(fromValue);
        }
    }

    std::string finalString;

    for (auto& elem : stackCrates)
        finalString.push_back(elem.top());

    return finalString;
}

auto moveMultipleCrates() -> std::string {
    auto crates = readInputToStringVector("crates.txt");

    std::vector<std::stack<char>> stackCrates(crates[0].size());

    for (int i = crates.size()-1; i >= 0; i--)
        for (int j = 0; j < crates[i].size(); j++)
            if (crates[i][j] != ' ') {
                stackCrates[j].push(crates[i][j]);
            }

    auto moves = readInputToStringVector("moves.txt");

    for (auto& move : moves) {
        auto [s_n, fromTo] = splitString(move, ',');
        auto [s_from, s_to] = splitString(fromTo, ':');

        auto from = std::stoi(s_from) - 1,
             to = std::stoi(s_to) - 1,
             n = std::stoi(s_n);

        std::vector<char> letters;

        for (int i = 0; i < n; i++) {
            auto fromValue = stackCrates[from].top();
            stackCrates[from].pop();

            letters.push_back(fromValue);
        }

        for (int i = letters.size()-1; i >= 0; i--) {
            stackCrates[to].push(letters[i]);
        }
    }

    std::string finalString;

    for (auto& elem : stackCrates)
        finalString.push_back(elem.top());

    return finalString;
}

int main() {

    auto part_1_string = moveSingleCrate();

    auto part_2_string = moveMultipleCrates();

    std::cout << "Part 1 crate string: " << part_1_string << std::endl;
    std::cout << "Part 2 crate string: " << part_2_string << std::endl;

    return 0;
}
