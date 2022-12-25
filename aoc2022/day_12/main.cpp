#include <iostream>
#include <set>
#include <cmath>
#include <queue>

#include "../utils/library.h"

using namespace VecOperations;

template<typename T>
using Matrix = std::vector<std::vector<T>>;

struct Tile {
    char elevation = 'a';
    bool visited;
    int distance;

    explicit Tile(const char c) {
        elevation = c;
        visited = false;
        distance = 1;
    }
};

struct Coordinate {
    int i, j;

    Coordinate(int _i, int _j) {
        i = _i;
        j = _j;
    }

    auto operator<(const Coordinate &b) const -> bool {
        return std::tie(i, j) < std::tie(b.i, b.j);
    }

    auto operator!=(const Coordinate &b) const -> bool {
        return !(*this == b);
    }

    auto operator==(const Coordinate &b) const -> bool {
        return (i == b.i && j == b.j);
    }
};


class Path {
    Matrix<Tile> heightmap;
    Matrix<char> pathway;
    Coordinate start{0, 0}, end{0, 0};
    std::queue<Coordinate> wavefront;

    bool visitedEnd = false;

    auto up(const Coordinate &current) -> Coordinate {
        return {current.i - 1, current.j};
    }

    auto down(const Coordinate &current) -> Coordinate {
        return {current.i + 1, current.j};
    }

    auto left(const Coordinate &current) -> Coordinate {
        return {current.i, current.j - 1};
    }

    auto right(const Coordinate &current) -> Coordinate {
        return {current.i, current.j + 1};
    }

    [[nodiscard]] auto coordsToChar(const Coordinate &coord) const -> char {
        if (coord.i < 0 || coord.j < 0 || coord.i >= heightmap.size() || coord.j >= heightmap[0].size())
            return '~';

        return heightmap[coord.i][coord.j].elevation;
    }

    auto getTile(const Coordinate& c) {
        return heightmap[c.i][c.j];
    }

public:
    Path(Matrix<Tile>& _heightmap, Coordinate& _start, Coordinate& _end) : heightmap(_heightmap) {
        start = _start;
        end = _end;

        heightmap[start.i][start.j].distance = 0;
        heightmap[start.i][start.j].visited = true;

        pathway = std::vector<std::vector<char>>(heightmap.size(), std::vector<char>(heightmap[0].size()));

        wavefront.push(start);
    }


    auto drawVisited() {
        for (int row = 0; row < heightmap.size(); row++) {
            for (int e = 0; e < heightmap[0].size(); e++) {
                if (heightmap[row][e].visited)
                    pathway[row][e] = '.';
                else
                    pathway[row][e] = heightmap[row][e].elevation;
            }
        }
    }

    auto print() {
        printContainer(pathway);
    }

    [[nodiscard]] auto isReachable(const Coordinate &current, const Coordinate &potential) -> bool {
        char cur = coordsToChar(current);
        char pot = coordsToChar(potential);

        if (pot == 'E')
            pot = 'z';

        if (cur == 'S')
            cur = 'a';

        int result = cur - pot;

        return (-1 <= result && result <= 26);
    }

    auto expandWavefront() {
        auto current = wavefront.front();

        if (getTile(current).elevation == 'E') {
            visitedEnd = true;
            wavefront.pop();
            return;
        }

        auto _up = up(current);
        auto _down = down(current);
        auto _left = left(current);
        auto _right = right(current);

        if (isReachable(current, _up) && !heightmap[_up.i][_up.j].visited) {
            heightmap[_up.i][_up.j].distance += heightmap[current.i][current.j].distance;
            heightmap[_up.i][_up.j].visited = true;
            wavefront.push(_up);
        }

        if (isReachable(current, _down) && !heightmap[_down.i][_down.j].visited) {
            heightmap[_down.i][_down.j].distance += heightmap[current.i][current.j].distance;
            heightmap[_down.i][_down.j].visited = true;
            wavefront.push(_down);
        }

        if (isReachable(current, _left) && !heightmap[_left.i][_left.j].visited) {
            heightmap[_left.i][_left.j].distance += heightmap[current.i][current.j].distance;
            heightmap[_left.i][_left.j].visited = true;
            wavefront.push(_left);
        }

        if (isReachable(current, _right) && !heightmap[_right.i][_right.j].visited) {
            heightmap[_right.i][_right.j].distance += heightmap[current.i][current.j].distance;
            heightmap[_right.i][_right.j].visited = true;
            wavefront.push(_right);
        }

        wavefront.pop();
    }

    auto foundEnd() {
        return wavefront.empty() || visitedEnd;
    }

    auto steps() {
        return heightmap[end.i][end.j].distance;
    }

    auto findPathToEnd() -> bool {

        while (!foundEnd()) {
            expandWavefront();
        }

        if (visitedEnd)
            return true;

        heightmap[end.i][end.j].distance = 0;

        return false;
    }
};


int main() {
    auto heightmap = parseInputToContainer<std::vector, std::vector<Tile>>("input.txt", stringToContainerT<std::vector, Tile>);

    Coordinate start(0,0), end(0,0);

    for (int row = 0; row < heightmap.size(); ++row) {
        for (int col = 0; col < heightmap[0].size(); ++col) {
            if (heightmap[row][col].elevation == 'S')
                start = {row, col};

            if (heightmap[row][col].elevation == 'E')
                end = {row, col};
        }
    }

    Path part1(heightmap, start, end);

    if (part1.findPathToEnd())
        std::cout << "Steps: " << part1.steps() << std::endl;
    else
        std::cout << "There was no path" << std::endl;

    std::vector<Coordinate> startingLocations;

    for (int row = 0; row < heightmap.size(); ++row) {
        for (int col = 0; col < heightmap[0].size(); ++col) {
            if (heightmap[row][col].elevation == 'a')
                startingLocations.emplace_back(row, col);
        }
    }

    int shortestPath = 1000;

    for (auto& _start : startingLocations ){
        Path part2(heightmap, _start, end);

        if (part2.findPathToEnd())
            if (part2.steps() < shortestPath)
                shortestPath = part2.steps();
    }

    std::cout << "Shortest path is: " << shortestPath << std::endl;


    return 0;
}
