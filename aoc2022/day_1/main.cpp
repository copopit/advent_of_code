#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

std::vector<int> readInput(const std::string& path) {
    std::vector<int> elfCalorieList;
    std::fstream inputFile(path, std::fstream::in);

    std::string line;
    int sum = 0;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            if (!line.empty()) {
                sum += std::stoi(line);
            } else {
                elfCalorieList.push_back(sum);

                sum = 0;
            }
        }
    }

    inputFile.close();

    return elfCalorieList;
}

int main() {

    auto elfCalories = readInput("input.txt");

    std::sort(elfCalories.begin(), elfCalories.end());

    for (auto& i : elfCalories)
        std::cout << i << std::endl;

    auto top3 = std::accumulate(elfCalories.end() - 3, elfCalories.end(), 0);

    std::cout << "Most calories carried by an elf: " << elfCalories.back() << std::endl;
    std::cout << "Total calories carried by top 3 elves: " << top3 << std::endl;

    return 0;
}
