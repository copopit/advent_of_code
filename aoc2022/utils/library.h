#ifndef UTILS_LIBRARY_H
#define UTILS_LIBRARY_H

#include <iostream>
#include <fstream>

#include <vector>
#include <tuple>


auto readInputToStringVector(const std::string& path) -> std::vector<std::string>;
auto splitString(const std::string& string, char delimiter) -> std::tuple<std::string, std::string>;

#endif //UTILS_LIBRARY_H
