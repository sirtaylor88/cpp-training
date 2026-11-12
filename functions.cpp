#include <iostream>

#include "functions.hpp"

using namespace std;

int main() {
    utils::say_hello("Alice", 30, cout);
    utils::print(utils::triple_number(5), cout);
    double f_temp = utils::convert_temperature(100.0, 'C', 'F');
    utils::print(f_temp, cout);

    // * std::boolalpha prints bools as true/false instead of 1/0.
    cout << boolalpha;
    utils::print(utils::are_equal(utils::triple_number(5), 15), cout);
    utils::print(utils::are_equal(f_temp, 100.0), cout);
    return 0;
}
