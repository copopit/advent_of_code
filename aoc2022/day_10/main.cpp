#include <iostream>

#include "../utils/library.h"

using namespace VecOperations;

struct Instruction {
    std::string cmd;
    int value;
};

class CRT_Screen {
    std::vector<Instruction> instructions;
    std::vector<std::vector<char>> scanlines;

    unsigned long cycle = 0;
    int nextInstruction = 0;
    int x_value = 1;
    int sum = 0;

    [[nodiscard]] auto isXAdjacentTo(int pixel) const {
        return (-1 <= x_value-pixel && x_value-pixel <= 1);
    }

    auto incrementCycle() {
        if (instructions[nextInstruction].cmd == "addx") {
            cycle += 2;
        } else {
            cycle++;
        }
        nextInstruction++;
    }

public:
    explicit CRT_Screen(const std::vector<Instruction>& _instructions) :
        instructions(_instructions),
        scanlines(6, std::vector<char>(40, ' '))
    {
        if (instructions.begin()->cmd == "addx")
            cycle +=2;
        else
            cycle++;
    }

    auto run() {
        for (int row = 0; row < scanlines.size(); row++) {
            for (int pixel = 0; pixel < scanlines[row].size(); pixel++) {
                if (isXAdjacentTo(pixel))
                    scanlines[row][pixel] = '#';
                else
                    scanlines[row][pixel] = '.';

                if (cycle % 40 == pixel) {
                    x_value += instructions[nextInstruction].value;
                    incrementCycle();
                }

                if (pixel == 19)
                    sum += x_value * (row * 20 + 20);
            }

        }
    }

    [[nodiscard]] auto getSum() const {
        return sum;
    }

    auto print() {
        printContainer(scanlines, "");
    }
};

auto strToInstruction(const std::string& str) -> Instruction {
    auto [cmd, val] = splitString(str, ' ');

    if (val.empty())
        return Instruction{cmd, 0};

    return Instruction{cmd, std::stoi(val)};
}

int main() {
    auto input = parseInputToContainer<std::vector, Instruction>("input.txt", strToInstruction);

    CRT_Screen screen(input);

    screen.run();

    screen.print();

    std::cout << "Total: " << screen.getSum() << std::endl;

    return 0;
}
