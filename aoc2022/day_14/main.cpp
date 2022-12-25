#include <iostream>

#include "../utils/library.h"

struct Coordinate {
    int x = 0, y = 0;

    Coordinate(int _x, int _y) {
        x = _x;
        y = _y;
    }

    explicit Coordinate(std::tuple<std::string, std::string> _values) {
        x = std::stoi(get<0>(_values));
        y = std::stoi(get<1>(_values));
    }

    struct hash {
        size_t operator()(const Coordinate& a) const {
            return ((a.x + a.y) * (a.x + a.y + 1)) / 2 + a.y;
        }
    };

    auto operator<(const Coordinate& b) const {
        return std::tie(x, y) < std::tie(b.x, b.y);
    }

    auto operator==(const Coordinate& b) const {
        return x == b.x && y == b.y;
    }

    auto operator!=(const Coordinate& b) const {
        return x != b.x && y != b.y;
    }

    auto operator=(const Coordinate& b) -> Coordinate& = default;
};

auto down(const Coordinate& coordinate) {
    return Coordinate{coordinate.x, coordinate.y+1};
}

auto diag_left(const Coordinate& coordinate) {
    return Coordinate{coordinate.x-1, coordinate.y+1};
}

auto diag_right(const Coordinate& coordinate) {
    return Coordinate{coordinate.x+1, coordinate.y+1};
}

enum class Type {
    Sand,
    Rock
};

using GridMap = std::unordered_map<Coordinate, Type, Coordinate::hash>;

auto validPosition(const GridMap& grid, const Coordinate& value, int max_y) -> Coordinate {
    /// Part 1 :
//    if (value.y >= max_y)
//        return {-1, max_y};

    /// Part 2 :
    if (down(value).y >= max_y + 2)
        return value;

    if (grid.find(down(value)) == grid.end())
        return validPosition(grid, down(value), max_y);

    if (grid.find(diag_left(value)) == grid.end())
        return validPosition(grid, diag_left(value), max_y);

    if (grid.find(diag_right(value)) == grid.end())
        return validPosition(grid, diag_right(value), max_y);

    return value;
}

int main() {
    GridMap grid;
    int max_y = 0;

    std::fstream file("example.txt");

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::string values, remaining = line;
            Coordinate prev(-1, -1);
            do {
                std::tie(values, remaining) = split(remaining, " -> ");
                Coordinate r(split(values, ","));

                if (r.y > max_y)
                    max_y = r.y;

                grid[r] = Type::Rock;

                if (prev != Coordinate{-1, -1}) {
                    if (prev.x == r.x) {
                        auto min = std::min(prev.y, r.y);
                        auto max = std::max(prev.y, r.y);
                        for (int i = min + 1; i < max; i++)
                            grid[{r.x, i}] = Type::Rock;
                    }

                    else if (prev.y == r.y) {
                        auto min = std::min(prev.x, r.x);
                        auto max = std::max(prev.x, r.x);
                        for (int i = min + 1; i < max; i++)
                            grid[{i, r.y}] = Type::Rock;
                    }
                }

                prev = r;
            } while (!remaining.empty());
        }
    }

    file.close();

    Coordinate start(500, 0);

    int sand = 0;

    while (true) {
        auto newPosition = validPosition(grid, start, max_y);

        /// Part 1
//        if (newPosition.y >= max_y)
//            break;

        sand++;

        /// Part 2
        if (newPosition == start)
            break;

        grid[newPosition] = Type::Sand;
    }

    std::cout << "Total iterations before no more start : " << sand << std::endl;


    /// Print example for visual (x-489)
    /*std::vector<std::vector<char>> render(16, std::vector<char>(40, '.'));

    render[start.y][start.x - 480] = '+';

    for (auto& item : grid) {
        int y = item.first.y;
        int x = item.first.x - 480;

        if (item.second == Type::Rock) {
            render[y][x] = '#';
        } else {
            render[y][x] = 'o';
        }
    }

    for (auto& i : render) {
        for (auto& j: i)
            std::cout << j;
        std::cout << "\n";
    }*/

    return 0;
}
