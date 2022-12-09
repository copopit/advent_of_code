#include <iostream>
#include <tuple>

#include "../utils/library.h"

struct IndexValuePair {
    int index, value;

    [[nodiscard]] bool compare(int _value) const {
        return value < _value;
    }

    void assign(int _value, int _index) {
        value = _value;
        index = _index;
    }

    bool operator<(const int b) const {
        return value < b;
    }
};

class BlockingTrees {
public:
    IndexValuePair low{0, 0};
    IndexValuePair high{0, 0};

    bool compareLow(const int val, const int index) {
        if (!low.compare(val))
            return false;

        low.assign(val, index);

        return true;
    }

    bool compareHigh(const int val, const int index) {
        if (!high.compare(val))
            return false;

        high.assign(val, index);

        return true;
    }

    void assignLow(const int val, const int index) {
        low.assign(val, index);
    }

    void assignHigh(const int val, const int index) {
        high.assign(val, index);
    }
};

template <typename T>
using Vec2d = std::vector<std::vector<T>>;

using namespace VecOperations;

int main() {
    auto treeHeights = parseInputToContainer<std::vector, std::vector<int>>("input.txt", stringToDigits<std::vector>);

    Vec2d<bool> seen;
    seen.reserve(treeHeights.size());

    for (int row = 0; row < treeHeights.size(); row++) {
        if (row == 0 || row == treeHeights.size()-1)
            seen.emplace_back(treeHeights.size(), true);
        else {
            auto temp = std::vector<bool>(treeHeights.size(), false);
            temp[0] = temp.back() = true;
            seen.emplace_back(temp);
        }
    }

    std::vector<BlockingTrees> treeRows(treeHeights.size());
    std::vector<BlockingTrees> treeColumns(treeHeights.size());

    for (int row = 1; row < treeHeights.size()-1; row++){
        treeRows[row].assignLow(treeHeights[row][0], row);

        treeRows[row].assignHigh(treeHeights[row].back(), row);
    }

    for (int col = 1; col < treeHeights.size() - 1; col++){
        treeColumns[col].assignLow(treeHeights[0][col], col);

        treeColumns[col].assignHigh(treeHeights.back()[col], col);
    }

    for (int it = 1; it < treeHeights.size() - 1; it++) {
        for (int left = 1, right = treeHeights[0].size()-2; right >= 1; left++, right--) {
            if (treeRows[it].compareLow(treeHeights[it][left], left) && !seen[it][left])
                seen[it][left] = true;

            if (treeRows[it].compareHigh(treeHeights[it][right], right) && !seen[it][right])
                seen[it][right] = true;

            if (treeColumns[it].compareLow(treeHeights[left][it], left) && !seen[left][it])
                seen[left][it] = true;

            if (treeColumns[it].compareHigh(treeHeights[right][it], right) && !seen[right][it])
                seen[right][it] = true;
        }
    }

    int totalVisible = 0;

    for (auto& i : seen) {
        for (auto j: i) {
            totalVisible += j;
        }
    }

    Vec2d<int> scenicScores(treeHeights.size(), std::vector<int>(treeHeights.size()));

    int bestScore = 0;

    for (int row = 1; row < treeHeights.size() - 1; row++) {
        for (int col = 1; col < treeHeights[0].size() - 1; col++) {
            int left = 0, right = 0, up = 0, down = 0;

            for (int l = col - 1; l >= 0; l--) {
                left++;
                if (treeHeights[row][l] >= treeHeights[row][col])
                    break;
            }

            for (int u = row - 1; u >= 0; u--) {
                up++;
                if (treeHeights[u][col] >= treeHeights[row][col])
                    break;
            }

            for (int r = col + 1; r < treeHeights.size(); r++) {
                right++;
                if (treeHeights[row][r] >= treeHeights[row][col])
                    break;
            }

            for (int d = row + 1; d < treeHeights.size(); d++) {
                down++;
                if (treeHeights[d][col] >= treeHeights[row][col])
                    break;
            }

            auto totalScore = left * right * up * down;

            if (bestScore < totalScore)
                bestScore = totalScore;
        }
    }

    std::cout << "Total visible trees: " << totalVisible << std::endl;
    std::cout << "Best tree score: " << bestScore << std::endl;


    return 0;
}
