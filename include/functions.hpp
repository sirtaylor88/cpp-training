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

// * Writes "The triple of <n> is <3n>." to `out`.
inline void print_triple_number(int n, std::ostream& out) {
    int result = triple_number(n);
    out << "The triple of " << n << " is " << result << "." << std::endl;
}

}  // namespace utils

// * Writes a greeting with `name` and `age` to `out`.
// ! No `using namespace std;` in a header: it would leak into every file
// ! that includes it.
inline void say_hello(const std::string& name, int age, std::ostream& out) {
    out << "Hello, " << name << "! You are " << age << " years old." << std::endl;
}
