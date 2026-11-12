// * Small examples of free functions and namespaces.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <iostream>
#include <string>

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

// * Converts `temp` between Celsius ('C') and Fahrenheit ('F').
// * Returns `temp` unchanged if the units are the same or unrecognized.
inline double convert_temperature(double temp, char from_unit, char to_unit) {
    if (from_unit == 'C' && to_unit == 'F') return (temp * 9.0 / 5.0) + 32.0;
    if (from_unit == 'F' && to_unit == 'C') return (temp - 32.0) * 5.0 / 9.0;
    return temp;
}

// * Writes a greeting with `name` and `age` to `out`.
// ! No `using namespace std;` in a header: it would leak into every file
// ! that includes it.
inline void say_hello(const std::string& name, int age, std::ostream& out) {
    out << "Hello, " << name << "! You are " << age << " years old.\n";
}

}  // namespace utils
