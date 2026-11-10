CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
LDLIBS   := -lgtest -lgtest_main -pthread

APP  := prompt_execrcice_1
TEST := test_prompt_execrcice_1

.PHONY: all run test clean

all: $(APP) $(TEST)

# Build the interactive program.
$(APP): prompt_execrcice_1.cpp prompt_execrcice_1.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Build the GoogleTest unit tests.
$(TEST): test_prompt_execrcice_1.cpp prompt_execrcice_1.hpp
	$(CXX) $(CXXFLAGS) $< $(LDLIBS) -o $@

run: $(APP)
	./$(APP)

# Pass GoogleTest options with ARGS, e.g. make test ARGS="--gtest_filter=*Greets*"
test: $(TEST)
	./$(TEST) $(ARGS)

clean:
	rm -f $(APP) $(TEST)
