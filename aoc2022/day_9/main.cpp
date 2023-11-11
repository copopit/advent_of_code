#include <iostream>
#include <set>
#include <unordered_set>

#include "../utils/library.h"

using namespace VecOperations;

struct Coords {
    int x;
    int y;

    Coords(int _x, int _y) : x(_x), y(_y) {}

    Coords operator-(const Coords& b) const {
        return {x-b.x, y-b.y};
    }

    Coords operator+(const Coords& b) const {
        return {x+b.x, y+b.y};
    }

    bool operator==(const Coords& b) const {
        return x == b.x && y == b.y;
    }

    bool operator<(const Coords& b) const {
        return (x < b.x) || (x == b.x && y < b.y);
    }
};

struct Instruction {
    char direction;
    int distance;
};

class Rope {
    std::vector<Coords> segments;
    std::vector<std::vector<char>> grid;

    std::set<Coords> visited;

    static auto adjacentCoordinate(int h, int t) {
        return (-1 <= h - t && h - t <= 1);
    }

    static auto isAdjacent(Coords head, Coords tail) {
        if (adjacentCoordinate(head.x, tail.x)
            && adjacentCoordinate(head.y, tail.y)) {
            return true;
        }

        return false;
    }

    auto follow(const Coords& leader, Coords& follower) {
        auto [d_x, d_y] = leader - follower;

        if (d_x < 0)
            follower.x--;
        else if (d_x > 0)
            follower.x++;

        if (d_y < 0)
            follower.y--;
        else if (d_y > 0)
            follower.y++;
    }

    auto moveHead(Instruction instruction) {
        /*
                -y
                |
          -x <- + -> +x
                |
                +y
         */
        switch (instruction.direction) {
            case 'R':
                segments[0].x++;
                break;
            case 'L':
                segments[0].x--;
                break;
            case 'U':
                segments[0].y--;
                break;
            case 'D':
                segments[0].y++;
                break;

            default:
                break;
        }
    }

public:
    explicit Rope(int _length = 2, Coords start = {0, 0}, Coords gridSize = {1, 1})
        : segments(std::vector<Coords>(_length, start)),
          grid(gridSize.y, std::vector<char>(gridSize.x, '.'))
        {
        grid[start.y][start.x] = 'S';
        visited.insert(start);
    }

    void moveRope(Instruction instruction) {
        moveHead(instruction);

        for (int segment = 1; segment < segments.size(); segment++) {
            if (isAdjacent(segments[segment-1], segments[segment]))
                break;

            follow(segments[segment-1], segments[segment]);

            if (segment == segments.size()-1)
                visited.insert(segments.back());
        }
    }

    void printGrid() {
        for (auto& row : grid)
            for (auto& col : row)
                if (col != '.' && col != 'S')
                    col = '.';

        for (int seg = 0; seg < segments.size(); seg++) {
            if (grid[segments[seg].y][segments[seg].x] == 'S')
                continue;

            if (seg == 0)
                grid[segments[seg].y][segments[seg].x] = 'H';
            else
                grid[segments[seg].y][segments[seg].x] = char(seg + '0');
        }

        printContainer(grid, "");
        std::cout << std::endl;
    }

    void paintVisited() {
        for (auto& elem : visited) {
            grid[elem.y][elem.x] = '#';
        }

        printContainer(grid, "");
    }

    [[nodiscard]] auto totalVisitedSquares() const {
        return visited.size();
    }
};

auto strToInstruction(const std::string& str) -> Instruction {
    auto [dir, val] = splitString(str, ' ');

    return Instruction{dir[0], std::stoi(val)};
}

int main() {
    auto instructions = parseInputToContainer<std::vector, Instruction>("input.txt", strToInstruction);

    Rope rope(10);

    /*
                -y
                |
          -x <- + -> +x
                |
                +y
    */

    for (auto& instruction : instructions)
        for (int i = 1; i <= instruction.distance; i++)
            rope.moveRope(instruction);

    std::cout << "Number of visited squares: " << rope.totalVisitedSquares() << std::endl;

    return 0;
}
