CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
LDLIBS   := -lgtest -lgtest_main -pthread

# * All compiled programs go in build/, which .gitignore ignores.
BUILD := build

# * Every <name>.cpp in the project root is an exercise with a matching
# * include/<name>.hpp and tests/test_<name>.cpp.
EXERCISES := $(basename $(wildcard *.cpp))
APPS      := $(addprefix $(BUILD)/,$(EXERCISES))
TESTS     := $(addprefix $(BUILD)/test_,$(EXERCISES))

# * Exercise for `make run`, e.g. make run EX=prompt_exercise_2
EX ?= $(firstword $(EXERCISES))

.PHONY: all run test clean

all: $(APPS) $(TESTS)

# * Build the GoogleTest unit tests for one exercise.
$(BUILD)/test_%: tests/test_%.cpp include/%.hpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< $(LDLIBS) -o $@

# * Build the interactive program for one exercise.
$(BUILD)/%: %.cpp include/%.hpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD):
	mkdir -p $@

run: $(BUILD)/$(EX)
	./$<

# Run every test program and stop at the first failure.
# Pass GoogleTest options with ARGS, e.g. make test ARGS="--gtest_filter=*Sum*"
test: $(TESTS)
	@for t in $(TESTS); do echo "== $$t"; ./$$t $(ARGS) || exit 1; done

clean:
	rm -rf $(BUILD)
