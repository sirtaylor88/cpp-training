// * Interactive prompt that asks the user for two numbers, then prints
// * their sum.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <iostream>
#include <string>

// * Prompts for 2 numbers, then writes their sum to `out`.
inline void run_prompt(std::istream& in, std::ostream& out) {
    // * Initialize so a failed read leaves 0, not garbage.
    int a = 0;

    out << "Enter first number: ";
    in >> a;

    out << "Enter second number: ";
    int b = 0;
    in >> b;

    int sum = a + b;

    out << "The sum of " << a << " and " << b << " is " << sum << "." << std::endl;
}
