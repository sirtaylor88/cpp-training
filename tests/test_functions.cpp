// * Unit tests for triple_number(), print(), convert_temperature() and
// * say_hello() in functions.hpp.

// * Google Test
#include <gtest/gtest.h>

// * Standard library
#include <sstream>
#include <string>

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

}  // namespace
