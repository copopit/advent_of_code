#ifndef UTILS_LIBRARY_H
#define UTILS_LIBRARY_H

#include <iostream>
#include <fstream>

#include <numeric>
#include <vector>
#include <tuple>

namespace Compare {
    template <typename T> auto largest(T a, T b);
    template <typename T> auto smallest(T a, T b);
    template <typename T> auto add(T a, T b);
    template <typename T> auto multiply(T a, T b);

    template <typename T>
    auto largest(const T a, const T b) {
        return (a < b ? b : a);
    }

    template <typename T>
    auto smallest(const T a, const T b) {
        return (a < b ? a : b);
    }

    template <typename T>
    auto add(const T a, const T b) {
        return a + b;
    }

    template <typename T>
    auto multiply(const T a, const T b) {
        return a * b;
    }
}

namespace VecOperations {
    using namespace Compare;

    template <typename T> auto average(T arr);
    template <typename T, typename K> auto find(T arr, K (*f)(K, K));
    template <typename T, typename K> auto sum(T arr, K (*f)(K, K));

    template <typename T>
    auto average(T arr) {
        return sum(arr, add) / arr.size();
    }

    template <typename T, typename K>
    auto find(K (*f)(K, K), T in) {
        return std::accumulate(in.begin() + 1, in.end(), in[0], f);
    }

    template <typename T, typename K>
    auto sum(K (*f)(K, K), T in) {
        return std::accumulate(in.begin(), in.end(), 0, f);
    }

    template <typename Op, template<typename>typename T>
    auto stringTo(Op (*f)(std::basic_string<char>), T<std::string> arr) {
        T<Op> newContainer;

        for (auto& elem : arr)
            newContainer.push_back(f(elem));

        return newContainer;
    }
}

int x() {
    std::vector<std::string> l({"1234567", "345678", "89475", "3384283"});

    auto result = VecOperations::stringTo<int>(std::stoi, l);
}

auto readInputToStringVector(const std::string& path) -> std::vector<std::string>;
auto splitString(const std::string& string, char delimiter) -> std::tuple<std::string, std::string>;

#endif //UTILS_LIBRARY_H
