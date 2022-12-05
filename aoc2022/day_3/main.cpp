#include <iostream>
#include <fstream>
#include <vector>

bool isLowercase(const char letter) {
    return (letter >= 97);
}

int rucksackScorePart1(const std::string& rucksack) {
    int middle = (rucksack.size() - 1) / 2;

    for (int left = 0; left <= middle; left++) {
        for (int right = middle+1; right < rucksack.size(); right++) {
            if (rucksack[left] == rucksack[right]) {
                if (isLowercase(rucksack[left])) {
                    return rucksack[left] - 'a' + 1;
                } else {
                    return rucksack[left] - 'A' + 27;
                }
            }
        }
    }

    return 0;
}

int rucksackScorePart2(const std::vector<std::string>& rucksackGroup) {
    for (char first : rucksackGroup[0]) {
        for (char second : rucksackGroup[1]) {
            if (first == second) {
                for (char third : rucksackGroup[2]) {
                    if (third == second) {
                        if (isLowercase(third)) {
                            return third - 'a' + 1;
                        } else {
                            return third - 'A' + 27;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int main() {

    std::fstream file("input.txt", std::fstream::in);

    int sum_p1 = 0, sum_p2 = 0;

    if (file.is_open()) {
        std::string line;
        std::vector<std::string> rucksackGroup(3, "");
        int count = 0;
        while (std::getline(file, line)) {
            sum_p1 += rucksackScorePart1(line);

            rucksackGroup[count] = line;

            if (count == 2) {
                sum_p2 += rucksackScorePart2(rucksackGroup);
                count = 0;
            } else
                count++;
        }
    }

    file.close();


    std::cout << "Total score part 1: " << sum_p1 << std::endl;
    std::cout << "Total score part 2: " << sum_p2 << std::endl;

    return 0;
}
