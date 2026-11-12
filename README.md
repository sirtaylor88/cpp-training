# cpp-training

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/17)
[![GCC](https://img.shields.io/badge/GCC-11.4-A42E2B?logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![GoogleTest](https://img.shields.io/badge/tested%20with-GoogleTest-4285F4?logo=google&logoColor=white)](https://github.com/google/googletest)
[![Ubuntu](https://img.shields.io/badge/Ubuntu-22.04-E95420?logo=ubuntu&logoColor=white)](https://releases.ubuntu.com/22.04/)
[![Last commit](https://img.shields.io/github/last-commit/sirtaylor88/cpp-training)](https://github.com/sirtaylor88/cpp-training/commits/main)

Training for C++

## Requirements

Tested on Ubuntu 22.04 (WSL2).

- **g++** (C++17 or later)
- **GoogleTest** for unit tests
- **uv** (optional) to install [pre-commit](#pre-commit-hooks)

```sh
sudo apt update
sudo apt install -y g++ libgtest-dev
curl -LsSf https://astral.sh/uv/install.sh | sh   # optional: uv
```

### VS Code (optional)

Open the folder in VS Code and install the recommended extensions when
prompted (see `.vscode/extensions.json`):

- C/C++ Extension Pack (`ms-vscode.cpptools-extension-pack`)
- Code Runner (`formulahendry.code-runner`)

`.vscode/c_cpp_properties.json` configures IntelliSense to match the build
(`/usr/bin/g++`, C++17, headers in `include/`). If VS Code still reports
`cannot open source file "gtest/gtest.h"` right after installing GoogleTest, run **Developer: Reload Window** from the command
palette (Ctrl+Shift+P).

## Project layout

```text
cpp-training/
├── include/                      # Headers with the exercise logic
│   ├── functions.hpp             # utils:: free functions, templates, comparisons, max, random numbers and average
│   └── prompts.hpp               # greet_prompt(): name and age; sum_prompt(): sum of two numbers
├── tests/                        # GoogleTest unit tests (+ .clang-tidy overrides)
│   ├── test_functions.cpp
│   └── test_prompts.cpp
├── build/                        # Compiled programs (created by make, ignored by git)
├── functions.cpp                 # main() for the functions exercise
├── prompts.cpp                   # main() for the prompts exercise
├── Makefile                      # Build, run, test and coverage shortcuts
├── CLAUDE.md                     # Notes for Claude Code (commands, conventions)
├── .clang-format                 # Code formatting rules (clang-format)
├── .clang-tidy                   # Static analysis checks (clang-tidy)
├── .pre-commit-config.yaml       # Checks run before every commit
├── .github/workflows/ci.yml      # Same checks on GitHub for every push/PR
└── .vscode/                      # Recommended extensions and IntelliSense config
```

## Shortcuts (Makefile)

| Command | Description |
| --- | --- |
| `make` | Build every exercise and its tests |
| `make run` | Build and run the first exercise |
| `make run EX=prompts` | Build and run a specific exercise |
| `make test` | Build and run all tests, stopping at the first failing exercise |
| `make test ARGS="--gtest_filter=*Greets*"` | Pass GoogleTest options to every test program |
| `make coverage` | Run all tests and fail unless every line and branch of `include/` ran |
| `make lint` | Run clang-tidy static analysis (checks in `.clang-tidy`) |
| `make clean` | Delete the `build/` folder |

Compiled programs go in `build/` (ignored by git). `make` only rebuilds a
program when its `.cpp` or `.hpp` file has changed.
The sections below show the underlying `g++` commands.

## Build and run

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Iinclude prompts.cpp -o build/prompts
./build/prompts
```

Example:

```text
What is your name? Alice
What is your age? 30
Hello, Alice! You are 30 years old.
Enter first number: 2
Enter second number: 3
The sum of 2 and 3 is 5.
```

## Run the tests

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Iinclude tests/test_prompts.cpp \
    -lgtest -lgtest_main -pthread -o build/test_prompts
./build/test_prompts
```

Run only some tests (similar to `pytest -k`):

```sh
./build/test_prompts --gtest_filter='GreetPromptTest.Greets*'
```

### Compiler options

| Option | Meaning |
| --- | --- |
| `-std=c++17` | Compile using the C++17 language standard |
| `-Wall` | Enable the common warnings (unused variables, missing `return`, …) |
| `-Wextra` | Enable extra warnings on top of `-Wall` (unused parameters, signed/unsigned comparison, …) |
| `-Iinclude` | Also search `include/` for `#include "..."` headers, so any file can include `prompts.hpp` |
| `-lgtest` | Link the GoogleTest library (`libgtest`), which provides `TEST`, `EXPECT_EQ`, … |
| `-lgtest_main` | Link a ready-made `main()` that runs every `TEST`, so test files need no `main()` |
| `-pthread` | Enable thread support, which GoogleTest uses internally |
| `-o <name>` | Name of the output program (defaults to `a.out`) |

Libraries (`-l...`) must come **after** the source files: the linker reads left
to right and only pulls from a library what earlier files need, otherwise you
get `undefined reference` errors.

#### Why C++17?

The code here would compile with older standards, and GoogleTest 1.11 only
needs C++11, but C++17 is passed explicitly because:

- **Reproducible builds:** compilers have different defaults (g++ 11 uses
  C++17, older versions use C++14), so pinning it gives the same result
  everywhere.
- **Standard C++ only:** without the flag, g++ uses `gnu++17`, which also
  accepts GNU-only extensions; `-std=c++17` keeps the code portable.
- **Future-proof:** newer GoogleTest releases require C++14 (1.13+) and
  C++17 (1.17+).
- **Widely supported:** every current compiler fully supports it, and it adds
  useful features such as `std::optional`, `std::string_view` and structured
  bindings (`auto [a, b] = ...`).

Switch to `-std=c++20` when exercises need C++20 features (concepts, ranges,
`<=>`). Note that `std::format` requires g++ 13 or later.

### Test runner options

| Option | Meaning |
| --- | --- |
| `--gtest_filter='Suite.Test*'` | Run only tests matching the pattern (`*` is a wildcard) |
| `--gtest_list_tests` | List the tests without running them |
| `--gtest_repeat=N` | Run the tests `N` times |
| `--gtest_brief=1` | Print only failing tests |

## Test coverage

`make coverage` rebuilds the tests with `--coverage`, runs them, and uses
`gcov` to check that every line and branch in `include/*.hpp` was executed.
It prints any line (`#####`) or branch (`taken 0%`) that never ran and fails.
The annotated reports are kept in `build/coverage/<exercise>.hpp.gcov`.

- `-fkeep-inline-functions` is needed because every function here is
  `inline`: without it, a function no test calls is never compiled and would
  silently not count as uncovered.
- Code that only runs when the standard library throws (marked `=====` and
  `(throw)` by gcov) is ignored, as it cannot realistically be tested.
- The `main()` files in the project root are not measured: keep them thin and
  put the logic in the headers.

## Pre-commit hooks

[pre-commit](https://pre-commit.com/) runs checks before every `git commit`
(see `.pre-commit-config.yaml`):

- trailing whitespace, end-of-file newline, YAML syntax, merge conflict markers
- `clang-format` on `.cpp`/`.hpp` files, using `.clang-format`
- `clang-tidy` static analysis (`make lint`), using `.clang-tidy` and
  `tests/.clang-tidy`; pre-commit installs clang-tidy itself, no `apt` needed
- `make coverage` when a `.cpp`, `.hpp` or the `Makefile` changed

Install the `pre-commit` command once per machine, then enable the git hook
once per clone:

```sh
uv tool install pre-commit   # once per machine (or: pip install pre-commit)
pre-commit install           # once per clone: adds .git/hooks/pre-commit
pre-commit run --all-files   # optional: check every file now
```

`uv tool install` works like `pipx`: it puts pre-commit in its own virtual
environment (`~/.local/share/uv/tools/`) and the `pre-commit` command in
`~/.local/bin/`, so it is available in every repo and never conflicts with
other Python packages or pyenv versions.

| Command | Description |
| --- | --- |
| `uv tool list` | Show tools installed with uv |
| `uv tool upgrade pre-commit` | Update pre-commit (`--all` updates every tool) |
| `uv tool uninstall pre-commit` | Remove pre-commit and its environment |
| `pre-commit autoupdate` | Update the hook versions (`rev:`) in `.pre-commit-config.yaml` |
| `git commit --no-verify` | Skip the hooks for one commit (CI still runs them) |

If a hook reformats a file, the commit stops: review the change, `git add` it
and commit again. GitHub Actions (`.github/workflows/ci.yml`) runs the same
checks on every push and pull request.

## Code conventions

### `'\n'` instead of `std::endl`

`std::endl` writes `'\n'` **and** flushes the stream, forcing a slow write to
the terminal on every line. clang-tidy (`performance-avoid-endl`) rejects it,
so end lines with `'\n'` (or put it in the string, e.g. `".\n"`):

```cpp
out << "The sum is " << sum << ".\n";   // not: << "." << std::endl;
```

The buffered output still appears when needed:

- before reading input: `std::cin` is tied to `std::cout`, so a prompt such as
  `"What is your name? "` always shows before the program waits;
- when the program exits normally, or when the buffer is full.

Flush on purpose only when output must appear immediately, and write it
explicitly so the reason is visible:

| Situation | Use |
| --- | --- |
| Progress message before a long computation | `out << "Working...\n" << std::flush;` |
| Errors, or messages that must survive a crash | `std::cerr << "error: ...\n";` (unbuffered) |

### No `using namespace std;` in headers

A header is copied into every file that `#include`s it, so a
`using namespace std;` there would apply to all of those files too, without
them asking for it. Names from `std` could then clash with your own (e.g. a
function called `count`, `distance` or `print`). In headers, write the
prefix:

```cpp
// include/functions.hpp
inline void say_hello(const std::string& name, int age, std::ostream& out);
```

It is fine in a `main()` file (`functions.cpp`, ...), because nothing
includes it:

```cpp
// functions.cpp
using namespace std;

int main() {
    utils::say_hello("Alice", 30, cout);
}
```

## Adding a new exercise

1. Put the logic in `include/<exercise>.hpp` as a function that takes streams
   instead of using `std::cin`/`std::cout` directly, so tests can feed input
   and capture output.
2. Add `<exercise>.cpp` with a `main()` that calls it with `std::cin` and
   `std::cout`.
3. Add tests in `tests/test_<exercise>.cpp`:

   ```cpp
   #include <gtest/gtest.h>

   #include <sstream>

   #include "my_exercise.hpp"

   TEST(MyExerciseTest, DoesSomething) {
       std::istringstream in("some input\n");
       std::ostringstream out;

       run_my_exercise(in, out);

       EXPECT_EQ(out.str(), "expected output\n");
   }
   ```

4. Run `make coverage` (or just commit: pre-commit runs it). The `Makefile`
   picks up every `.cpp` in the project root automatically, so no new rules
   are needed. Output goes in `build/`, so nothing needs adding to
   `.gitignore`.

Each exercise is a separate program with its own `main()`. Functions that
live in the same header, like `greet_prompt()` and `sum_prompt()` in
`prompts.hpp`, need different names.
