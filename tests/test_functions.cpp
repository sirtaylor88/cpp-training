// * Unit tests for functions.hpp: triple_number(), print(), is_close(),
// * are_equal(), max_value(), convert_temperature(), say_hello(),
// * random_numbers(), compute_average(), print_numbers() and print_average().

// * Google Test
#include <gtest/gtest.h>

// * Standard library
#include <cmath>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "functions.hpp"

namespace {

// * Runs print() on `value` and returns everything it wrote.
template <typename T>
std::string Print(const T& value) {
    std::ostringstream out;
    utils::print(value, out);
    return out.str();
}

// * Runs say_hello() and returns everything it wrote.
std::string SayHello(const std::string& name, int age) {
    std::ostringstream out;
    utils::say_hello(name, age, out);
    return out.str();
}

TEST(TripleNumberTest, TriplesPositiveNumber) {
    EXPECT_EQ(utils::triple_number(5), 15);
}

TEST(TripleNumberTest, TripleOfZeroIsZero) {
    EXPECT_EQ(utils::triple_number(0), 0);
}

TEST(TripleNumberTest, TriplesNegativeNumber) {
    EXPECT_EQ(utils::triple_number(-4), -12);
}

TEST(TripleNumberTest, TriplesOne) {
    EXPECT_EQ(utils::triple_number(1), 3);
}

TEST(PrintTest, PrintsInt) {
    EXPECT_EQ(Print(15), "15\n");
    EXPECT_EQ(Print(-6), "-6\n");
    EXPECT_EQ(Print(0), "0\n");
}

TEST(PrintTest, PrintsDouble) {
    EXPECT_EQ(Print(212.0), "212\n");
    EXPECT_EQ(Print(6.05), "6.05\n");
}

TEST(PrintTest, PrintsString) {
    EXPECT_EQ(Print(std::string("Hello")), "Hello\n");
    EXPECT_EQ(Print("C-string"), "C-string\n");
}

TEST(PrintTest, PrintsResultOfAnotherFunction) {
    EXPECT_EQ(Print(utils::triple_number(5)), "15\n");
}

TEST(IsCloseTest, AcceptsRoundingErrors) {
    EXPECT_TRUE(utils::is_close(0.1 + 0.2, 0.3));
    EXPECT_TRUE(utils::is_close(0.1 + 0.2 - 0.3, 0.0));
}

TEST(IsCloseTest, RejectsRealDifferences) {
    EXPECT_FALSE(utils::is_close(1.0, 1.001));
    EXPECT_FALSE(utils::is_close(0.0000001, 0.0));
}

TEST(AreEqualTest, ComparesInts) {
    EXPECT_TRUE(utils::are_equal(15, 15));
    EXPECT_FALSE(utils::are_equal(15, -15));
}

TEST(AreEqualTest, ComparesDoubles) {
    EXPECT_TRUE(utils::are_equal(212.0, 212.0));
    EXPECT_FALSE(utils::are_equal(212.0, 100.0));
}

TEST(AreEqualTest, IgnoresRoundingErrors) {
    // * 0.1 + 0.2 is 0.30000000000000004, so `==` would say false.
    EXPECT_TRUE(utils::are_equal(0.1 + 0.2, 0.3));
    // * Relative tolerance: large numbers that differ only by rounding.
    EXPECT_TRUE(utils::are_equal(1e20, 1e20 * (1 + 1e-15)));
    // * Absolute tolerance: a tiny rounding leftover is equal to 0.
    EXPECT_TRUE(utils::are_equal(0.1 + 0.2 - 0.3, 0.0));
}

TEST(AreEqualTest, KeepsSmallButRealDifferences) {
    // * Converting to strings with 6 decimals would call all of these equal.
    EXPECT_FALSE(utils::are_equal(0.0000004, 0.0000001));
    EXPECT_FALSE(utils::are_equal(0.0000001, 0.0));
    EXPECT_FALSE(utils::are_equal(0.3000005, 0.3000004));
}

TEST(AreEqualTest, ComparesFloats) {
    EXPECT_TRUE(utils::are_equal(0.5F, 0.5F));
    EXPECT_FALSE(utils::are_equal(0.5F, 0.25F));
}

TEST(AreEqualTest, ComparesStrings) {
    EXPECT_TRUE(utils::are_equal(std::string("Alice"), std::string("Alice")));
    EXPECT_FALSE(utils::are_equal(std::string("Alice"), std::string("alice")));
}

TEST(AreEqualTest, ComparesResultOfAnotherFunction) {
    EXPECT_TRUE(utils::are_equal(utils::triple_number(5), 15));
    EXPECT_TRUE(utils::are_equal(utils::convert_temperature(100.0, 'C', 'F'), 212.0));
}

TEST(MaxValueTest, ReturnsLargestInt) {
    EXPECT_EQ(utils::max_value(std::vector<int>{4, 9, 2, 7}), 9);
}

TEST(MaxValueTest, HandlesNegativeNumbers) {
    EXPECT_EQ(utils::max_value(std::vector<int>{-8, -3, -5}), -3);
}

TEST(MaxValueTest, ReturnsLargestDouble) {
    EXPECT_DOUBLE_EQ(utils::max_value(std::vector<double>{4.4, 7.7, 5.5}), 7.7);
}

TEST(MaxValueTest, SingleValueIsTheMax) {
    EXPECT_EQ(utils::max_value(std::vector<int>{42}), 42);
}

TEST(MaxValueTest, HandlesDuplicates) {
    EXPECT_EQ(utils::max_value(std::vector<int>{3, 9, 9, 1}), 9);
}

TEST(MaxValueTest, ComparesStringsAlphabetically) {
    EXPECT_EQ(utils::max_value(std::vector<std::string>{"pear", "apple", "fig"}),
              "pear");
    // * Uppercase letters come before lowercase ones: "Zoe" < "adam".
    EXPECT_EQ(utils::max_value(std::vector<std::string>{"Zoe", "adam"}), "adam");
}

TEST(MaxValueTest, ThrowsOnEmptyList) {
    // * Each type gets its own compiled copy of the template, so test each one.
    EXPECT_THROW(utils::max_value(std::vector<int>{}), std::invalid_argument);
    EXPECT_THROW(utils::max_value(std::vector<double>{}), std::invalid_argument);
    EXPECT_THROW(utils::max_value(std::vector<std::string>{}), std::invalid_argument);
}

TEST(ConvertTemperatureTest, CelsiusToFahrenheit) {
    EXPECT_DOUBLE_EQ(utils::convert_temperature(100.0, 'C', 'F'), 212.0);
    EXPECT_DOUBLE_EQ(utils::convert_temperature(-40.0, 'C', 'F'), -40.0);
}

TEST(ConvertTemperatureTest, FahrenheitToCelsius) {
    EXPECT_DOUBLE_EQ(utils::convert_temperature(32.0, 'F', 'C'), 0.0);
    EXPECT_DOUBLE_EQ(utils::convert_temperature(212.0, 'F', 'C'), 100.0);
}

TEST(ConvertTemperatureTest, SameUnitReturnsInput) {
    EXPECT_DOUBLE_EQ(utils::convert_temperature(25.0, 'C', 'C'), 25.0);
    EXPECT_DOUBLE_EQ(utils::convert_temperature(77.0, 'F', 'F'), 77.0);
}

TEST(ConvertTemperatureTest, UnknownUnitReturnsInput) {
    EXPECT_DOUBLE_EQ(utils::convert_temperature(10.0, 'K', 'C'), 10.0);
}

TEST(SayHelloTest, GreetsDefaultExample) {
    EXPECT_EQ(SayHello("Alice", 30), "Hello, Alice! You are 30 years old.\n");
}

TEST(SayHelloTest, KeepsSpacesInName) {
    // * Unlike reading with `>>`, a string argument keeps the whole name.
    EXPECT_EQ(SayHello("John Smith", 25), "Hello, John Smith! You are 25 years old.\n");
}

TEST(SayHelloTest, HandlesEmptyName) {
    EXPECT_EQ(SayHello("", 1), "Hello, ! You are 1 years old.\n");
}

TEST(SayHelloTest, HandlesAgeZero) {
    EXPECT_EQ(SayHello("Baby", 0), "Hello, Baby! You are 0 years old.\n");
}

// * Runs print_average() on `numbers` and returns everything it wrote.
std::string PrintAverage(const std::vector<double>& numbers) {
    std::ostringstream out;
    utils::print_average(numbers, out);
    return out.str();
}

// * Use EXPECT_DOUBLE_EQ (not EXPECT_EQ) for doubles: it allows for tiny
// * rounding errors, e.g. 0.1 + 0.2 != 0.3 exactly.

TEST(ComputeAverageTest, AveragesDefaultList) {
    EXPECT_DOUBLE_EQ(utils::compute_average({4.4, 5.5, 6.6, 7.7}), 6.05);
}

TEST(ComputeAverageTest, SingleNumberIsItsOwnAverage) {
    EXPECT_DOUBLE_EQ(utils::compute_average({42.0}), 42.0);
}

TEST(ComputeAverageTest, AveragesWholeNumbersToFraction) {
    // * Would give 1 with integer division; 0.0 start value keeps it a double.
    EXPECT_DOUBLE_EQ(utils::compute_average({1.0, 2.0}), 1.5);
}

TEST(ComputeAverageTest, AveragesNegativeNumbers) {
    EXPECT_DOUBLE_EQ(utils::compute_average({-2.0, -4.0, -6.0}), -4.0);
}

TEST(ComputeAverageTest, MixedSignsCanCancelOut) {
    EXPECT_DOUBLE_EQ(utils::compute_average({-3.5, 3.5}), 0.0);
}

TEST(ComputeAverageTest, AllZerosGiveZero) {
    EXPECT_DOUBLE_EQ(utils::compute_average({0.0, 0.0, 0.0}), 0.0);
}

TEST(ComputeAverageTest, EmptyListGivesNaN) {
    EXPECT_TRUE(std::isnan(utils::compute_average({})));
}

TEST(RandomNumbersTest, ReturnsFourNumbersByDefault) {
    std::mt19937 engine(42);
    EXPECT_EQ(utils::random_numbers(engine).size(), 4U);
}

TEST(RandomNumbersTest, ReturnsRequestedCount) {
    std::mt19937 engine(42);
    EXPECT_EQ(utils::random_numbers(engine, 10).size(), 10U);
    EXPECT_TRUE(utils::random_numbers(engine, 0).empty());
}

TEST(RandomNumbersTest, StaysWithinRange) {
    std::mt19937 engine(42);
    for (double number : utils::random_numbers(engine, 1000, -5.0, 5.0)) {
        EXPECT_GE(number, -5.0);
        EXPECT_LT(number, 5.0);
    }
}

TEST(RandomNumbersTest, SameSeedGivesSameNumbers) {
    std::mt19937 first(123);
    std::mt19937 second(123);
    EXPECT_EQ(utils::random_numbers(first), utils::random_numbers(second));
}

TEST(RandomNumbersTest, AverageIsWithinRange) {
    std::mt19937 engine(7);
    double average = utils::compute_average(utils::random_numbers(engine));
    EXPECT_GE(average, 0.0);
    EXPECT_LT(average, 10.0);
}

TEST(PrintNumbersTest, PrintsEachNumberAfterLabel) {
    std::ostringstream out;
    utils::print_numbers({4.4, 5.5, -1.0}, out);
    EXPECT_EQ(out.str(), "Numbers: 4.4 5.5 -1\n");
}

TEST(PrintNumbersTest, PrintsOnlyLabelForEmptyList) {
    std::ostringstream out;
    utils::print_numbers({}, out);
    EXPECT_EQ(out.str(), "Numbers:\n");
}

TEST(PrintAverageTest, PrintsDefaultList) {
    EXPECT_EQ(PrintAverage({4.4, 5.5, 6.6, 7.7}), "Average in number list: 6.05\n");
}

TEST(PrintAverageTest, PrintsWholeNumberWithoutDecimals) {
    // * `std::cout` uses the default format, so 5.0 prints as "5".
    EXPECT_EQ(PrintAverage({4.0, 6.0}), "Average in number list: 5\n");
}

}  // namespace
