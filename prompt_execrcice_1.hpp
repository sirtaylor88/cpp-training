// * Interactive prompt that asks the user for their name and age, then
// * greets them.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <iostream>
#include <string>

// * Prompts for a name and an age, then writes a greeting to `out`.
//
// * Reads a single whitespace-delimited word from `in` as the name, followed
// * by an integer as the age. Each prompt is written to `out` before the
// * corresponding read. If the age cannot be parsed as an integer, it is
// * reported as 0.
//
// * Example:
// * std::istringstream in("Alice 30");
// * run_prompt(in, std::cout);
//   // Prints: What is your name? What is your age? Hello, Alice! You are
//   //         30 years old.
inline void run_prompt(std::istream& in, std::ostream& out) {
    std::string username;
    int user_age;

    out << "What is your name? ";
    in >> username;

    out << "What is your age? ";
    in >> user_age;

    out << "Hello, " << username
        << "! You are " << user_age << " years old." << std::endl;
}
