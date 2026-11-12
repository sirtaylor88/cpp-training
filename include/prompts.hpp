// * Interactive prompts that read from an input stream and write to an
// * output stream:
// * - greet_prompt(): asks for a name and an age, then greets the user.
// * - sum_prompt(): asks for two numbers, then prints their sum.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <iostream>
#include <string>

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
