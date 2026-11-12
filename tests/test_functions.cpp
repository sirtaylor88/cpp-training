// * Unit tests for triple_number(), print_triple_number() and say_hello()
// * in functions.hpp.

// * Google Test
#include <gtest/gtest.h>

// * Standard library
#include <sstream>
#include <string>

#include "functions.hpp"

namespace {

// * Runs print_triple_number() on `n` and returns everything it wrote.
std::string PrintTriple(int n) {
    std::ostringstream out;
    utils::print_triple_number(n, out);
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

TEST(PrintTripleNumberTest, PrintsDefaultExample) {
    EXPECT_EQ(PrintTriple(5), "The triple of 5 is 15.\n");
}

TEST(PrintTripleNumberTest, PrintsNegativeNumber) {
    EXPECT_EQ(PrintTriple(-2), "The triple of -2 is -6.\n");
}

TEST(PrintTripleNumberTest, PrintsZero) {
    EXPECT_EQ(PrintTriple(0), "The triple of 0 is 0.\n");
}

TEST(SayHelloTest, GreetsDefaultExample) {
    EXPECT_EQ(SayHello("Alice", 30), "Hello, Alice! You are 30 years old.\n");
}

TEST(SayHelloTest, KeepsSpacesInName) {
    // * Unlike reading with `>>`, a string argument keeps the whole name.
    EXPECT_EQ(SayHello("John Smith", 25),
              "Hello, John Smith! You are 25 years old.\n");
}

TEST(SayHelloTest, HandlesEmptyName) {
    EXPECT_EQ(SayHello("", 1), "Hello, ! You are 1 years old.\n");
}

TEST(SayHelloTest, HandlesAgeZero) {
    EXPECT_EQ(SayHello("Baby", 0), "Hello, Baby! You are 0 years old.\n");
}

}  // namespace
