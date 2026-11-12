// * Small examples of free functions, templates and namespaces, including
// * random numbers and their average.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// * std::size_t: unsigned integer type for sizes and counts (C++ version of
// * C's <stddef.h>). Included explicitly even though <vector> pulls it in,
// * because only including a header guarantees the name is available.
#include <cstddef>

namespace utils {

// * Returns `n` multiplied by 3.
inline int triple_number(int n) {
    return n * 3;
}

// * Writes `value` followed by a newline to `out`.
// * A template: works with any type that supports `out << value`
// * (int, double, std::string, ...). The compiler generates one version per
// * type it is called with. Templates are implicitly inline.
template <typename T>
void print(const T& value, std::ostream& out) {
    out << value << '\n';
}

// * Returns true if `a` and `b` are close enough to count as equal, like
// * Python's math.isclose(). Use it for floating-point values, where rounding
// * makes `==` unreliable (0.1 + 0.2 == 0.3 is false).
// * Close enough means the difference is at most 1e-9 of the larger value
// * (relative), or at most 1e-12 (absolute, needed near zero, where a
// * relative tolerance shrinks to nothing).
inline bool is_close(double a, double b) {
    const double rel_tol = 1e-9;
    const double abs_tol = 1e-12;
    const double tolerance =
        std::max(rel_tol * std::max(std::fabs(a), std::fabs(b)), abs_tol);
    return std::fabs(a - b) <= tolerance;
}

// * Returns true if `a` and `b` are equal: is_close() for float/double,
// * `a == b` for any other type.
// * Both arguments must have the same type `T`: are_equal(1, 1.0) doesn't
// * compile, write are_equal(1.0, 1.0) or are_equal<double>(1, 1.0) instead.
// ! `if constexpr` (C++17) drops its body at compile time when the condition
// ! is false, so std::string never compiles is_close(). The code after it is
// ! always compiled, which is why it must work for every T: `a == b` does.
template <typename T>
bool are_equal(const T& a, const T& b) {
    if constexpr (std::is_floating_point_v<T>) return is_close(a, b);
    return a == b;
}

// * Returns the largest value in `values`, like Python's max().
// * Works with any type that supports `<` (int, double, std::string, ...);
// * strings compare alphabetically, uppercase before lowercase.
// ! Throws std::invalid_argument if `values` is empty: there is no maximum,
// ! and returning a made-up value such as 0 would hide the bug.
template <typename T>
T max_value(const std::vector<T>& values) {
    if (values.empty()) throw std::invalid_argument("max_value() of an empty list");
    // * std::max_element returns an iterator (a position) to the largest
    // * element; `*` reads the value at that position.
    return *std::max_element(values.begin(), values.end());
}

// * Converts `temp` between Celsius ('C') and Fahrenheit ('F').
// * Returns `temp` unchanged if the units are the same or unrecognized.
inline double convert_temperature(double temp, char from_unit, char to_unit) {
    if (from_unit == 'C' && to_unit == 'F') return (temp * 9.0 / 5.0) + 32.0;
    if (from_unit == 'F' && to_unit == 'C') return (temp - 32.0) * 5.0 / 9.0;
    return temp;
}

// * Writes a greeting with `name` and `age` to `out`.
inline void say_hello(const std::string& name, int age, std::ostream& out) {
    out << "Hello, " << name << "! You are " << age << " years old.\n";
}

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

}  // namespace utils
