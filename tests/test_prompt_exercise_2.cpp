// * Unit tests for run_prompt() in prompt_exercise_2.hpp.

// * Google Test
#include <gtest/gtest.h>

// * Standard library
#include <sstream>
#include <string>

#include "prompt_exercise_2.hpp"

namespace {

// * Prompts that run_prompt() writes before reading each number.
const std::string kPrompts = "Enter first number: Enter second number: ";

// * Runs run_prompt() with `input` as stdin and returns everything it wrote.
std::string RunWithInput(const std::string& input) {
    std::istringstream in(input);
    std::ostringstream out;
    run_prompt(in, out);
    return out.str();
}

TEST(SumPromptTest, AddsTwoPositiveNumbers) {
    EXPECT_EQ(RunWithInput("2 3\n"),
              kPrompts + "The sum of 2 and 3 is 5.\n");
}

TEST(SumPromptTest, AcceptsNumbersOnSeparateLines) {
    EXPECT_EQ(RunWithInput("10\n32\n"),
              kPrompts + "The sum of 10 and 32 is 42.\n");
}

TEST(SumPromptTest, AddsNegativeNumbers) {
    EXPECT_EQ(RunWithInput("-4 -6\n"),
              kPrompts + "The sum of -4 and -6 is -10.\n");
}

TEST(SumPromptTest, AddsPositiveAndNegativeNumbers) {
    EXPECT_EQ(RunWithInput("7 -10\n"),
              kPrompts + "The sum of 7 and -10 is -3.\n");
}

TEST(SumPromptTest, HandlesZeros) {
    EXPECT_EQ(RunWithInput("0 0\n"),
              kPrompts + "The sum of 0 and 0 is 0.\n");
}

TEST(SumPromptTest, TruncatesDecimalInput) {
    // * `int` extraction stops at '.', so "3.9" reads 3; reading the second
    // * number then fails on ".9" and stores 0.
    EXPECT_EQ(RunWithInput("3.9 1\n"),
              kPrompts + "The sum of 3 and 0 is 3.\n");
}

TEST(SumPromptTest, NonNumericSecondNumberYieldsZero) {
    EXPECT_EQ(RunWithInput("5 abc\n"),
              kPrompts + "The sum of 5 and 0 is 5.\n");
}

TEST(SumPromptTest, NonNumericFirstNumberYieldsZeros) {
    // * Once a read fails, the stream stops reading, so `b` keeps its
    // * initial value too.
    EXPECT_EQ(RunWithInput("abc 5\n"),
              kPrompts + "The sum of 0 and 0 is 0.\n");
}

}  // namespace
