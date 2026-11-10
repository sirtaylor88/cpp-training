CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
LDLIBS   := -lgtest -lgtest_main -pthread

# All compiled programs go in build/, which .gitignore ignores.
BUILD := build
APP   := $(BUILD)/prompt_execrcice_1
TEST  := $(BUILD)/test_prompt_execrcice_1

.PHONY: all run test clean

all: $(APP) $(TEST)

# Build the interactive program.
$(APP): prompt_execrcice_1.cpp include/prompt_execrcice_1.hpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

# Build the GoogleTest unit tests.
$(TEST): tests/test_prompt_execrcice_1.cpp include/prompt_execrcice_1.hpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< $(LDLIBS) -o $@

$(BUILD):
	mkdir -p $@

run: $(APP)
	./$(APP)

# Pass GoogleTest options with ARGS, e.g. make test ARGS="--gtest_filter=*Greets*"
test: $(TEST)
	./$(TEST) $(ARGS)

clean:
	rm -rf $(BUILD)
