// * Fills a list with random numbers, then computes and prints its average.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <algorithm>
#include <iostream>
// * std::size_t: unsigned integer type for sizes and counts (C++ version of
// * C's <stddef.h>). Included explicitly even though <vector> pulls it in,
// * because only including a header guarantees the name is available.
#include <cstddef>
#include <numeric>
#include <random>
#include <vector>

// * Returns `count` random numbers, each uniformly drawn from [min, max).
// * The engine is passed in so tests can use a fixed seed and get
// * reproducible numbers.
inline std::vector<double> random_numbers(std::mt19937& engine,
                                          std::size_t count = 4,
                                          double min = 0.0,
                                          double max = 10.0) {
    std::uniform_real_distribution<double> dist(min, max);
    std::vector<double> numbers(count);
    // * Fill each slot with a new random draw.
    std::generate(numbers.begin(), numbers.end(), [&] { return dist(engine); });
    return numbers;
}

// * Returns the arithmetic mean of `numbers`.
// * An empty list gives NaN (0.0 / 0), matching plain floating-point division.
inline double compute_average(const std::vector<double>& numbers) {
    // * Start from 0.0 (not 0) so the sum is accumulated as a double.
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    return sum / static_cast<double>(numbers.size());
}

// * Writes "Numbers: a b c ..." to `out`.
inline void print_numbers(const std::vector<double>& numbers, std::ostream& out) {
    out << "Numbers:";
    for (double number : numbers) {
        out << ' ' << number;
    }
    out << '\n';
}

// * Writes the average of `numbers` to `out`.
inline void print_average(const std::vector<double>& numbers, std::ostream& out) {
    out << "Average in number list: " << compute_average(numbers) << '\n';
}
