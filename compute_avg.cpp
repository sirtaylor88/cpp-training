#include <iostream>
#include <random>
#include <vector>

#include "compute_avg.hpp"

using namespace std;

int main() {
    // * Seed the engine from the OS so each run gives different numbers.
    mt19937 engine(random_device{}());
    vector<double> numbers = random_numbers(engine);

    print_numbers(numbers, cout);
    print_average(numbers, cout);
    return 0;
}
