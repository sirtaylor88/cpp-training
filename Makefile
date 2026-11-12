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

.PHONY: all run test coverage lint clean

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

# * Build every test with gcov instrumentation, run it, and fail unless every
# * line and branch of include/<name>.hpp ran.
# * -fkeep-inline-functions: header functions are `inline`, so without it an
# * untested function is never compiled and silently missing from the report.
# * Ignored on purpose: `=====` lines and `(throw)` branches, which only run
# * when the standard library throws (e.g. out of memory).
COVERAGE := $(BUILD)/coverage
COVFLAGS := -O0 --coverage -fkeep-inline-functions

coverage:
	@rm -rf $(COVERAGE) && mkdir -p $(COVERAGE)
	@for ex in $(EXERCISES); do \
	    $(CXX) $(CXXFLAGS) $(COVFLAGS) tests/test_$$ex.cpp $(LDLIBS) \
	        -o $(COVERAGE)/test_$$ex || exit 1; \
	    ./$(COVERAGE)/test_$$ex --gtest_brief=1 || exit 1; \
	    gcov -t -b -o $(COVERAGE) $(COVERAGE)/test_$$ex.gcda 2>/dev/null \
	        | awk -v f=include/$$ex.hpp '/:Source:/ { p = index($$0, f) > 0 } p' \
	        > $(COVERAGE)/$$ex.hpp.gcov; \
	done
	@if grep -nE '#####|branch +[0-9]+ (never executed|taken 0%)$$' \
	        $(COVERAGE)/*.hpp.gcov; then \
	    echo "FAIL: coverage below 100% (lines/branches listed above never ran)"; \
	    exit 1; \
	fi
	@echo "OK: 100% line and branch coverage of include/"

# * Static analysis with clang-tidy (checks listed in .clang-tidy). Every .cpp
# * is analyzed, and the headers it includes from include/ along with it.
# * Run a specific binary with e.g. make lint CLANG_TIDY=clang-tidy-19
CLANG_TIDY ?= clang-tidy

lint:
	$(CLANG_TIDY) --quiet $(wildcard *.cpp) $(wildcard tests/*.cpp) -- \
	    -std=c++17 -Iinclude

clean:
	rm -rf $(BUILD)
