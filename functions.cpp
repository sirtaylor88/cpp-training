#include <iostream>

#include "functions.hpp"

using namespace std;

int main() {
    utils::say_hello("Alice", 30, cout);
    utils::print(utils::triple_number(5), cout);
    double f_temp = utils::convert_temperature(100.0, 'C', 'F');
    utils::print(f_temp, cout);
    return 0;
}
