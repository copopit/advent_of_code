#ifndef UTILS_LIBRARY_H
#define UTILS_LIBRARY_H

#include <iostream>
#include <fstream>

#include <numeric>
#include <vector>
#include <tuple>
#include <functional>
#include <list>
#include <map>

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
    auto sum(std::function<K(K, K)> f, T in) {
        return std::accumulate(in.begin(), in.end(), 0, f);
    }


    template <template<typename>typename Container>
    auto stringToDigits(const std::string& str) {
        Container<int> newContainer;

        for (auto& digit : str)
            newContainer.emplace_back(digit - '0');

        return newContainer;
    }

    template <template<typename>typename Container, template<typename>typename C>
    auto stringContainerToDigits(C<std::string>& arr) {
        Container<Container<int>> newContainer;

        for (auto& elem : arr)
            newContainer.emplace_back(stringToDigits<Container>(elem));

        return newContainer;
    }

    template <template<typename>typename Container, typename T>
    auto parseInputToContainer(const std::string& path, std::function<T(std::string)> f) {
        Container<T> data;

        std::fstream file(path, std::fstream::in);

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                data.push_back(f(line));
            }
        }

        return data;
    }
}

/**
 * Doesn't work with bool values because j cannot reference it. Container needs a << overload to work
 * @tparam T
 * @param container 2D container to iterate over
 * @return
 */
template <typename T>
auto printContainer(T container) {
    for (auto& i : container) {
        for (auto& j: i)
            std::cout << j << ", ";
        std::cout << "\n";
    }
}

auto readInputToStringVector(const std::string& path) -> std::vector<std::string>;
auto splitString(const std::string& string, char delimiter) -> std::tuple<std::string, std::string>;

#endif //UTILS_LIBRARY_H
