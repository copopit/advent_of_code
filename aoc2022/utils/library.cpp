#include "library.h"

auto readInputToStringVector(const std::string& path) -> std::vector<std::string> {
    std::vector<std::string> data;

    std::fstream file(path, std::fstream::in);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            data.push_back(line);
        }
    }

    return data;
}

auto splitString(const std::string& string, const char delimiter) -> std::tuple<std::string, std::string> {
    std::string left, right;

    auto delim = string.find(delimiter);

    left = string.substr(0, delim);
    right = string.substr(left.size()+1, string.size() - left.size());

    return std::make_tuple(left, right);
}
