// * Unit tests for greet_prompt() and sum_prompt() in prompts.hpp.

// * Google Test
#include <gtest/gtest.h>

// * Standard library
#include <sstream>
#include <string>

#include "prompts.hpp"

// * Anonymous namespace to avoid polluting the global namespace with test
// * helpers and constants.
// * Private functions and variables in an anonymous namespace
// * have internal linkage, so they are not visible outside this translation unit.
namespace {

// * Prompts that each function writes before reading each input.
// * The prefix "k" indicates that this is a constant variable.
const std::string kGreetPrompts = "What is your name? What is your age? ";
const std::string kSumPrompts = "Enter first number: Enter second number: ";

// * Signature shared by greet_prompt() and sum_prompt(): a pointer to a
// * function taking (std::istream&, std::ostream&) and returning nothing.
using PromptFunction = void (*)(std::istream&, std::ostream&);

// * Runs `prompt` with `input` as stdin and returns everything it wrote.
std::string RunWithInput(PromptFunction prompt, const std::string& input) {
    // * Use string streams to simulate stdin and stdout.
    std::istringstream in(input);
    std::ostringstream out;

    // * Call the function being tested.
    prompt(in, out);

    // * Return everything that was written to the output stream.
    return out.str();
}

TEST(GreetPromptTest, GreetsUserWithNameAndAge) {
    EXPECT_EQ(RunWithInput(greet_prompt, "Alice 30\n"),
              kGreetPrompts + "Hello, Alice! You are 30 years old.\n");
}

TEST(GreetPromptTest, AcceptsInputsOnSeparateLines) {
    EXPECT_EQ(RunWithInput(greet_prompt, "Bob\n42\n"),
              kGreetPrompts + "Hello, Bob! You are 42 years old.\n");
}

TEST(GreetPromptTest, HandlesAgeZero) {
    EXPECT_EQ(RunWithInput(greet_prompt, "Baby 0\n"),
              kGreetPrompts + "Hello, Baby! You are 0 years old.\n");
}

TEST(GreetPromptTest, ReadsOnlyFirstWordOfName) {
    EXPECT_EQ(RunWithInput(greet_prompt, "John Smith 25\n"),
              kGreetPrompts + "Hello, John! You are 0 years old.\n");
}

TEST(GreetPromptTest, NonNumericAgeYieldsZero) {
    EXPECT_EQ(RunWithInput(greet_prompt, "Carol abc\n"),
              kGreetPrompts + "Hello, Carol! You are 0 years old.\n");
}

TEST(SumPromptTest, AddsTwoPositiveNumbers) {
    EXPECT_EQ(RunWithInput(sum_prompt, "2 3\n"),
              kSumPrompts + "The sum of 2 and 3 is 5.\n");
}

TEST(SumPromptTest, AcceptsNumbersOnSeparateLines) {
    EXPECT_EQ(RunWithInput(sum_prompt, "10\n32\n"),
              kSumPrompts + "The sum of 10 and 32 is 42.\n");
}

TEST(SumPromptTest, AddsNegativeNumbers) {
    EXPECT_EQ(RunWithInput(sum_prompt, "-4 -6\n"),
              kSumPrompts + "The sum of -4 and -6 is -10.\n");
}

TEST(SumPromptTest, AddsPositiveAndNegativeNumbers) {
    EXPECT_EQ(RunWithInput(sum_prompt, "7 -10\n"),
              kSumPrompts + "The sum of 7 and -10 is -3.\n");
}

TEST(SumPromptTest, HandlesZeros) {
    EXPECT_EQ(RunWithInput(sum_prompt, "0 0\n"),
              kSumPrompts + "The sum of 0 and 0 is 0.\n");
}

TEST(SumPromptTest, TruncatesDecimalInput) {
    // * `int` extraction stops at '.', so "3.9" reads 3; reading the second
    // * number then fails on ".9" and stores 0.
    EXPECT_EQ(RunWithInput(sum_prompt, "3.9 1\n"),
              kSumPrompts + "The sum of 3 and 0 is 3.\n");
}

TEST(SumPromptTest, NonNumericSecondNumberYieldsZero) {
    EXPECT_EQ(RunWithInput(sum_prompt, "5 abc\n"),
              kSumPrompts + "The sum of 5 and 0 is 5.\n");
}

TEST(SumPromptTest, NonNumericFirstNumberYieldsZeros) {
    // * Once a read fails, the stream stops reading, so `b` keeps its
    // * initial value too.
    EXPECT_EQ(RunWithInput(sum_prompt, "abc 5\n"),
              kSumPrompts + "The sum of 0 and 0 is 0.\n");
}

}  // namespace
