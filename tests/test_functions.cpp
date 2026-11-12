// * Unit tests for triple_number(), print(), is_close(), are_equal(),
// * convert_temperature() and say_hello() in functions.hpp.

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
