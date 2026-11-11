// * Unit tests for compute_average() and print_average() in compute_avg.hpp.

// * Google Test
#include <gtest/gtest.h>

// * Standard library
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "compute_avg.hpp"

namespace {

// * Runs print_average() on `numbers` and returns everything it wrote.
std::string PrintAverage(const std::vector<double>& numbers) {
    std::ostringstream out;
    print_average(numbers, out);
    return out.str();
}

// * Use EXPECT_DOUBLE_EQ (not EXPECT_EQ) for doubles: it allows for tiny
// * rounding errors, e.g. 0.1 + 0.2 != 0.3 exactly.

TEST(ComputeAverageTest, AveragesDefaultList) {
    EXPECT_DOUBLE_EQ(compute_average({ 4.4, 5.5, 6.6, 7.7 }), 6.05);
}

TEST(ComputeAverageTest, SingleNumberIsItsOwnAverage) {
    EXPECT_DOUBLE_EQ(compute_average({ 42.0 }), 42.0);
}

TEST(ComputeAverageTest, AveragesWholeNumbersToFraction) {
    // * Would give 1 with integer division; 0.0 start value keeps it a double.
    EXPECT_DOUBLE_EQ(compute_average({ 1.0, 2.0 }), 1.5);
}

TEST(ComputeAverageTest, AveragesNegativeNumbers) {
    EXPECT_DOUBLE_EQ(compute_average({ -2.0, -4.0, -6.0 }), -4.0);
}

TEST(ComputeAverageTest, MixedSignsCanCancelOut) {
    EXPECT_DOUBLE_EQ(compute_average({ -3.5, 3.5 }), 0.0);
}

TEST(ComputeAverageTest, AllZerosGiveZero) {
    EXPECT_DOUBLE_EQ(compute_average({ 0.0, 0.0, 0.0 }), 0.0);
}

TEST(ComputeAverageTest, EmptyListGivesNaN) {
    EXPECT_TRUE(std::isnan(compute_average({})));
}

TEST(PrintAverageTest, PrintsDefaultList) {
    EXPECT_EQ(PrintAverage({ 4.4, 5.5, 6.6, 7.7 }),
              "Average in number list: 6.05\n");
}

TEST(PrintAverageTest, PrintsWholeNumberWithoutDecimals) {
    // * `std::cout` uses the default format, so 5.0 prints as "5".
    EXPECT_EQ(PrintAverage({ 4.0, 6.0 }), "Average in number list: 5\n");
}

}  // namespace
