#include <iostream>
#include <vector>

#include "compute_avg.hpp"

int main() {
    std::vector<double> numbers = { 4.4, 5.5, 6.6, 7.7 };
    print_average(numbers, std::cout);
    return 0;
}
