// * Computes the average of a list of numbers and prints it.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <iostream>
#include <numeric>
#include <vector>

// * Returns the arithmetic mean of `numbers`.
// * An empty list gives NaN (0.0 / 0), matching plain floating-point division.
inline double compute_average(const std::vector<double>& numbers) {
    // * Start from 0.0 (not 0) so the sum is accumulated as a double.
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    return sum / numbers.size();
}

// * Writes the average of `numbers` to `out`.
inline void print_average(const std::vector<double>& numbers, std::ostream& out) {
    out << "Average in number list: " << compute_average(numbers) << std::endl;
}
