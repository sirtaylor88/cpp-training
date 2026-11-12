#include <iostream>

#include "functions.hpp"

int main() {
    say_hello("Alice", 30, std::cout);
    number_utils::print_triple_number(5, std::cout);
    return 0;
}
