#include <exception>
#include <iostream>
#include <random>
#include <vector>

#include "functions.hpp"

using namespace std;

int main() {
    // * max_value() throws on an empty list: catch it here so the program
    // * prints a message and exits with an error code instead of crashing.
    try {
        utils::say_hello("Alice", 30, cout);

        cout << "Triple of 5: ";
        utils::print(utils::triple_number(5), cout);

        double f_temp = utils::convert_temperature(100.0, 'C', 'F');
        cout << "100 Celsius in Fahrenheit: ";
        utils::print(f_temp, cout);

        // * std::boolalpha prints bools as true/false instead of 1/0.
        cout << boolalpha;
        cout << "Is the triple of 5 equal to 15? ";
        utils::print(utils::are_equal(utils::triple_number(5), 15), cout);
        cout << "Is " << f_temp << " Fahrenheit equal to 100? ";
        utils::print(utils::are_equal(f_temp, 100.0), cout);

        const vector<int> numbers{4, 9, 2, 7};
        cout << "Max of {4, 9, 2, 7}: ";
        utils::print(utils::max_value(numbers), cout);

        vector<int> extended{1, 2};
        utils::extend(extended, {3, 4});
        cout << "{1, 2} extended with {3, 4}:";
        for (int n : extended) cout << ' ' << n;
        cout << '\n';

        // * Seed the engine from the OS so each run gives different numbers.
        mt19937 engine(random_device{}());
        const vector<double> random_list = utils::random_numbers(engine);
        utils::print_numbers(random_list, cout);
        utils::print_average(random_list, cout);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
