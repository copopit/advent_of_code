#include <iostream>
#include <cmath>

#include "../utils/library.h"

class Monkey {
    std::list<unsigned long long> items;
    char op = '+';
    int formulaNumber = 1;
public:
    int divisor{1}, throwToTrue = 0, throwToFalse = 0;
    unsigned long inspectedCount = 0;

    int lcm = 1;

    bool operator<(const Monkey &b) const {
        return inspectedCount > b.inspectedCount;
    }

    auto addStartingItems(const std::string &_items) {
        int val = 0, pos = 1;
        for (int i = _items.size() - 1; i >= 0; i--) {
            if (_items[i] == ' ' && i != 0) {
                continue;
            }

            if (_items[i] == ',' || i == 0) {
                items.push_front(val);
                pos = 1;
                val = 0;
            } else {
                val += (pos * (_items[i] - 48));
                pos *= 10;
            }
        }
    }

    auto addOperator(const std::string &_formula) {
        op = _formula[11];
        if (_formula.substr(13) == "old")
            formulaNumber = -1;
        else
            formulaNumber = std::stoi(_formula.substr(13));
    }

    [[nodiscard]] auto isCarryingItems() const -> bool {
        return !items.empty();
    }

    [[nodiscard]] auto executeFormula(const unsigned long long num) const -> unsigned long long {
        if (formulaNumber == -1) {
            switch (op) {
                case '+':
                    return num + num;
                case '*':
                    return num * num;
            }
        }

        switch (op) {
            case '+':
                return num + formulaNumber;
            case '*':
                return num * formulaNumber;
        }

        return num;
    }

    auto inspect() -> bool {

        // Part 1 :
//        items.front() = std::floor(executeFormula(items.front()) / 3);

        // Part 2:
        items.front() = executeFormula(items.front()) % lcm;

        if (items.front() % divisor == 0)
            return true;

        return false;
    }

    auto pop() {
        auto value = items.front();
        items.pop_front();
        return value;
    }

    auto push(unsigned long long item) {
        items.push_back(item);
    }

    auto print() {
        std::cout << "Starting items: ";
        for (auto &i: items)
            std::cout << i << ", ";
        std::cout << std::endl;
    }
};

int main() {
    std::fstream file("input.txt", std::ios::in);

    std::vector<Monkey> monkeys;

    if (file.is_open()) {
        while (!file.eof()) {
            std::string line;

            Monkey monke;

            std::vector<std::string> lines;
            while (true) {
                std::getline(file, line);
                if (line.empty())
                    break;

                if (line.find("Monkey") != std::string::npos) continue;

                auto [_, value] = splitString(line, ':');

                lines.emplace_back(value);

                if (file.eof())
                    break;
            }

            for (int elem = 0; elem < lines.size(); elem++) {
                switch (elem) {
                    case 0:
                        monke.addStartingItems(lines[elem]);
                        break;
                    case 1:
                        monke.addOperator(lines[elem]);
                        break;
                    case 2:
                        monke.divisor = std::stoi(lines[elem].substr(13));
                        break;
                    case 3:
                        monke.throwToTrue = std::stoi(lines[elem].substr(17));
                        break;
                    case 4:
                        monke.throwToFalse = std::stoi(lines[elem].substr(17));
                        break;
                    default:
                        break;
                }
            }

            monkeys.emplace_back(monke);
        }
    }

    int common_lcm = 1;
    for (auto &monkey: monkeys) {
        common_lcm = std::lcm(common_lcm, monkey.divisor);
    }

    for (auto &monke: monkeys) {
        monke.lcm = common_lcm;
    }

    std::cout << "common lcm " << common_lcm << std::endl;

    for (int round = 0; round < 10000; round++) {
        for (auto &monke: monkeys) {
            while (monke.isCarryingItems()) {

                monke.inspectedCount++;

                if (monke.inspect())
                    monkeys[monke.throwToTrue].push(monke.pop());
                else
                    monkeys[monke.throwToFalse].push(monke.pop());
            }
        }
    }

    for (auto &elem: monkeys)
        elem.print();

    std::cout << "\n\n\n";


    for (auto &elem: monkeys)
        std::cout << elem.inspectedCount << std::endl;

    std::cout << "\n\n\n";

    std::sort(monkeys.begin(), monkeys.end());


    std::cout << "Monke 1: " << monkeys[0].inspectedCount << "\nMonke 2: " << monkeys[1].inspectedCount << std::endl;

    std::cout << "Total: " << monkeys[0].inspectedCount * monkeys[1].inspectedCount << std::endl;


    return 0;
}
