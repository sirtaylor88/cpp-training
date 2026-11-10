// * Unit tests for run_prompt() in prompt_exercise_1.hpp.

// * Google TEst
#include <gtest/gtest.h>

// * Standard library
#include <sstream>
#include <string>

#include "prompt_exercise_1.hpp"

// * Anonymous namespace to avoid polluting the global namespace with test
// * helpers and constants.
// * Private functions and variables in an anonymous namespace
// * have internal linkage, so they are not visible outside this translation unit.
namespace {

// * Prompts that run_prompt() writes before reading each input.
// * The prefix "k" indicates that this is a constant variable.
const std::string kPrompts = "What is your name? What is your age? ";

// * Runs run_prompt() with `input` as stdin and returns everything it wrote.
std::string RunWithInput(const std::string& input) {
    // * Use string streams to simulate stdin and stdout.
    std::istringstream in(input);
    std::ostringstream out;

    // * Call the function being tested.
    run_prompt(in, out);

    // * Return everything that was written to the output stream.
    return out.str();
}

TEST(RunPromptTest, GreetsUserWithNameAndAge) {
    EXPECT_EQ(RunWithInput("Alice 30\n"),
              kPrompts + "Hello, Alice! You are 30 years old.\n");
}

TEST(RunPromptTest, AcceptsInputsOnSeparateLines) {
    EXPECT_EQ(RunWithInput("Bob\n42\n"),
              kPrompts + "Hello, Bob! You are 42 years old.\n");
}

TEST(RunPromptTest, HandlesAgeZero) {
    EXPECT_EQ(RunWithInput("Baby 0\n"),
              kPrompts + "Hello, Baby! You are 0 years old.\n");
}

TEST(RunPromptTest, ReadsOnlyFirstWordOfName) {
    EXPECT_EQ(RunWithInput("John Smith 25\n"),
              kPrompts + "Hello, John! You are 0 years old.\n");
}

TEST(RunPromptTest, NonNumericAgeYieldsZero) {
    EXPECT_EQ(RunWithInput("Carol abc\n"),
              kPrompts + "Hello, Carol! You are 0 years old.\n");
}

}  // namespace
