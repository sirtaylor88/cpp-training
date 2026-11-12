#include <exception>
#include <iostream>

#include "prompts.hpp"

using namespace std;

int main() {
    // * Catch any exception so the program prints a message instead of
    // * crashing.
    try {
        greet_prompt(cin, cout);
        sum_prompt(cin, cout);
        max_prompt(cin, cout);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
