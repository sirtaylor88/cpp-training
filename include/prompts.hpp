// * Interactive prompts that read from an input stream and write to an
// * output stream:
// * - greet_prompt(): asks for a name and an age, then greets the user.
// * - sum_prompt(): asks for two numbers, then prints their sum.
// * - max_prompt(): asks for numbers until the user stops, then prints the
// *   largest.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "functions.hpp"

// * Prompts for a name and an age, then writes a greeting to `out`.
inline void greet_prompt(std::istream& in, std::ostream& out) {
    std::string username;
    int user_age;

    out << "What is your name? ";
    in >> username;

    out << "What is your age? ";
    in >> user_age;

    out << "Hello, " << username << "! You are " << user_age << " years old.\n";
}

// * Prompts for 2 numbers, then writes their sum to `out`.
inline void sum_prompt(std::istream& in, std::ostream& out) {
    // * Initialize so a failed read leaves 0, not garbage.
    int a = 0;

    out << "Enter first number: ";
    in >> a;

    out << "Enter second number: ";
    int b = 0;
    in >> b;

    int sum = a + b;

    out << "The sum of " << a << " and " << b << " is " << sum << ".\n";
}

// * Prompts for numbers until the user types anything that isn't a number
// * (e.g. `q`) or ends the input (Ctrl+D), then writes the largest to `out`.
inline void max_prompt(std::istream& in, std::ostream& out) {
    std::vector<int> numbers;
    int number = 0;
    while (true) {
        out << "Enter a number (q to stop): ";
        // * `in >> number` is false when the input isn't a number or has ended.
        if (!(in >> number)) break;
        numbers.push_back(number);
    }

    // * Make the stream usable again for later reads: clear the error left
    // * by the stop input, then skip the rest of that line (the `q`).
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // * Guard clause: utils::max_value() throws on an empty list.
    if (numbers.empty()) {
        out << "No numbers entered.\n";
        return;
    }
    out << "The max value is " << utils::max_value(numbers) << ".\n";
}
