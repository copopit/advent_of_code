#include <iostream>
#include <tuple>

#include "../utils/library.h"

struct TaskRange {
    int start = 0, end = 0;

    auto stringToTaskRange(const std::string& string) {
        auto [first, second] = splitString(string, '-');

        start = std::stoi(first);
        end = std::stoi(second);
    }

    [[nodiscard]] auto overlapsWith(const TaskRange& b) const -> bool {
        return (end >= b.start && end <= b.end || start <= b.end && start >= b.start);
    }

    [[nodiscard]] bool containedIn(const TaskRange& b) const {
        return (start >= b.start && end <= b.end);
    }
};


int main() {
    int sum_p1 = 0, sum_p2 = 0;

    auto data = readInputToStringVector("input.txt");

    for (auto& s : data) {
        auto [first, second] = splitString(s, ',');

        TaskRange elf_1, elf_2;

        elf_1.stringToTaskRange(first);
        elf_2.stringToTaskRange(second);

        if (elf_1.containedIn(elf_2) || elf_2.containedIn(elf_1))
            sum_p1++;

        if (elf_1.overlapsWith(elf_2) || elf_2.overlapsWith(elf_1))
            sum_p2++;
    }

    std::cout << "Total contained tasks: " << sum_p1 << std::endl;
    std::cout << "Total overlapping tasks: " << sum_p2 << std::endl;

    return 0;
}
