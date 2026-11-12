# CLAUDE.md

C++17 training exercises, tested with GoogleTest. See `README.md` for the full
setup; this file lists what matters when changing code.

## Commands

```sh
make test                          # build + run every test program
make test ARGS="--gtest_filter=*Sum*"
make coverage                      # tests + must reach 100% line/branch coverage of include/
make lint                          # clang-tidy (.clang-tidy, tests/.clang-tidy)
make run EX=prompts                # run one interactive exercise
pre-commit run --all-files         # everything CI runs: format, lint, coverage
```

Every change must pass `pre-commit run --all-files` (CI runs the same thing).

## Layout

Each exercise `<name>` is three files, picked up automatically by the
`Makefile` (no rules to add):

- `include/<name>.hpp`: all the logic, as `inline` functions (header-only).
- `<name>.cpp`: a thin `main()` that calls the header with `std::cin`/`std::cout`.
  Not measured by coverage, so keep logic out of it.
- `tests/test_<name>.cpp`: GoogleTest tests for the header.

## Conventions

- Functions take `std::istream&` / `std::ostream&` instead of using
  `std::cin` / `std::cout` directly, so tests can use string streams.
- End lines with `'\n'` (or inside the string, `".\n"`), never `std::endl`
  (clang-tidy `performance-avoid-endl`). Use `std::flush` only on purpose.
- No `using namespace std;` in headers (allowed in the `main()` files).
- One-line guard clauses are fine: `if (x) return y;` (braces check disabled).
- Formatting: clang-format, Google style, 4-space indent, 88 columns,
  one parameter per line when a signature doesn't fit. Don't hand-format;
  let the hook do it.
- Comments use Better Comments markers: `// *` for explanations,
  `// !` for warnings. Every function in a header gets a `// *` comment.
- Tests: `TEST(<Function>Test, <Behavior>)`, inside an anonymous namespace,
  with small helpers that capture output from a stream. Cover every branch.
- Includes in groups separated by a comment: GoogleTest, standard library,
  project header.

## Gotchas

- Coverage uses `-fkeep-inline-functions`: without it, an inline function that
  no test calls is never compiled and silently missing from the report.
  This does **not** help for templates: an uncalled template is still
  invisible, so test every template with each kind of type it should accept.
- `make coverage` ignores gcov's `=====` lines and `(throw)` branches (only
  reachable when the standard library throws).
- `.clang-format` is for clang-format 23 (`BinPackParameters: OnePerLine`); the
  pre-commit hook pins the version, so use the hook rather than an older
  system `clang-format`.
- The shell is zsh: unmatched globs are errors, so quote GoogleTest filters
  (`--gtest_filter='*Foo*'`).

## Commits

Gitmoji-style subject, sentence ending with a period, e.g.
`✨ Add ...`, `🐛 Fix ...`, `♻  Refactor ...`, `✅ Add tests ...`,
`📝 Update README.`, `🔧 Update config ...`.
