#include <iostream>
#include <set>

#include "../utils/library.h"

using namespace VecOperations;

enum Direction {
    R = 82,
    L = 76,
    U = 85,
    D = 68
};

struct Coords {
    int x;
    int y;

    bool operator==(const Coords& b) const {
        return x == b.x && y == b.y;
    }

    bool operator<(const Coords& b) const {
        return x < b.x || y < b.y;
    }
};

struct Instruction {
    Direction dir;
    int value;
};

auto adjacentCoordinate(int h, int t) {
    return (-1 <= h - t && h - t <= 1);
}

auto isAdjacent(Coords head, Coords tail) {
    if (adjacentCoordinate(head.x, tail.x)
     && adjacentCoordinate(head.y, tail.y)) {
        return true;
    }

    return false;
}

int main() {
    auto strInput = readInputToStringVector("input.txt");

    std::vector<Instruction> instructions;
    instructions.reserve(strInput.size());

    for (auto& i : strInput) {
        auto [dir, val] = splitString(i, ' ');

        instructions.push_back(Instruction{(Direction)dir[0], std::stoi(val)});
    }

    Coords head{0, 0}, previousHead = head;
    Coords tail = head, previousTail{-1, -1};

    std::set<Coords> visited;

    /*
            +y
            ^
      -x <- + -> +x
            |
            -y
     */

    //std::vector<std::vector<char>> exampleVisualized(5, std::vector<char>(6, '.'));

    for (auto& instruction : instructions) {
        for (int i = 0; i < instruction.value; i++) {
            if (!isAdjacent(head, tail))
                tail = previousHead;

            if (tail != previousTail) {
                visited.insert(tail);
                //exampleVisualized[4-tail.y][tail.x] = '#';
            }

            //printContainer(exampleVisualized);

            previousHead = head;

            switch (instruction.dir) {
                case R:
                    head.x++;
                    break;
                case L:
                    head.x--;
                    break;
                case U:
                    head.y++;
                    break;
                case D:
                    head.y--;
                    break;

                default:
                    break;
            }
        }
    }

    std::cout << "Number of visited squares: " << visited.size() << std::endl;

    return 0;
}
