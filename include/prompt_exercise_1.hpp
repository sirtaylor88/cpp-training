// * Interactive prompt that asks the user for their name and age, then
// * greets them.

// * `include` this header file (.hpp) only once per .cpp file being compiled
#pragma once

#include <iostream>
#include <string>

// * Prompts for a name and an age, then writes a greeting to `out`.
inline void run_prompt(std::istream& in, std::ostream& out) {
    std::string username;
    int user_age;

    out << "What is your name? ";
    in >> username;

    out << "What is your age? ";
    in >> user_age;

    out << "Hello, " << username << "! You are " << user_age << " years old.\n";
}
