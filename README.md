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

```sh
sudo apt update
sudo apt install -y g++ libgtest-dev
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
│   ├── compute_avg.hpp           # random_numbers() + compute_average(): mean of a random list
│   ├── functions.hpp             # say_hello() and number_utils::triple_number(): free functions and namespaces
│   ├── prompt_exercise_1.hpp     # run_prompt(): asks for a name and age, then greets
│   └── prompt_exercise_2.hpp     # run_prompt(): asks for two numbers, then prints the sum
├── tests/                        # GoogleTest unit tests
│   ├── test_compute_avg.cpp
│   ├── test_functions.cpp
│   ├── test_prompt_exercise_1.cpp
│   └── test_prompt_exercise_2.cpp
├── build/                        # Compiled programs (created by make, ignored by git)
├── compute_avg.cpp               # main() for the average exercise
├── functions.cpp                 # main() for the functions/namespaces exercise
├── prompt_exercise_1.cpp         # main() for exercise 1
├── prompt_exercise_2.cpp         # main() for exercise 2
├── Makefile                      # Build, run and test shortcuts
└── .vscode/                      # Recommended extensions and IntelliSense config
```

## Shortcuts (Makefile)

| Command | Description |
| --- | --- |
| `make` | Build every exercise and its tests |
| `make run` | Build and run the first exercise |
| `make run EX=prompt_exercise_2` | Build and run a specific exercise |
| `make test` | Build and run all tests, stopping at the first failing exercise |
| `make test ARGS="--gtest_filter=*Greets*"` | Pass GoogleTest options to every test program |
| `make clean` | Delete the `build/` folder |

Compiled programs go in `build/` (ignored by git). `make` only rebuilds a
program when its `.cpp` or `.hpp` file has changed.
The sections below show the underlying `g++` commands.

## Build and run

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Iinclude prompt_exercise_1.cpp -o build/prompt_exercise_1
./build/prompt_exercise_1
```

Example:

```text
What is your name? Alice
What is your age? 30
Hello, Alice! You are 30 years old.
```

## Run the tests

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Iinclude tests/test_prompt_exercise_1.cpp \
    -lgtest -lgtest_main -pthread -o build/test_prompt_exercise_1
./build/test_prompt_exercise_1
```

Run only some tests (similar to `pytest -k`):

```sh
./build/test_prompt_exercise_1 --gtest_filter='RunPromptTest.Greets*'
```

### Compiler options

| Option | Meaning |
| --- | --- |
| `-std=c++17` | Compile using the C++17 language standard |
| `-Wall` | Enable the common warnings (unused variables, missing `return`, …) |
| `-Wextra` | Enable extra warnings on top of `-Wall` (unused parameters, signed/unsigned comparison, …) |
| `-Iinclude` | Also search `include/` for `#include "..."` headers, so any file can include `prompt_exercise_1.hpp` |
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

4. Run `make test`. The `Makefile` picks up every `.cpp` in the project root
   automatically, so no new rules are needed. Output goes in `build/`, so
   nothing needs adding to `.gitignore`.

Each exercise is a separate program, so every header can use the same
function name (`run_prompt`) without clashing.
