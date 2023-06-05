<img alt="TinyExpr logo" src="doc/tinyexpr_logo.png" align="right"/>

# TinyExpr++

TinyExpr++ is the C++ version of the [TinyExpr](https://github.com/codeplea/tinyexpr) library, which is a small
recursive-descent parser and evaluation engine for math expressions.

In addition to math operators and precedence, TinyExpr++ also supports
the standard C math functions and runtime binding of variables and user-defined functions.

[![unit-tests](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/unit-tests.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/unit-tests.yml)
[![macOS Build & Unit Tests](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/macos-unit-tests.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/macos-unit-tests.yml)
[![Windows Build & Unit Tests](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/msw-unit-tests.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/msw-unit-tests.yml)

[![cppcheck](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/cppcheck.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/cppcheck.yml)
[![Microsoft C++ Code Analysis](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/msvc.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/msvc.yml)
[![CodeQL](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/codeql.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/codeql.yml)

[![doxygen](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/doxygen.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/doxygen.yml)
[![i18n-check](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/i18n-check.yml/badge.svg)](https://github.com/Blake-Madden/tinyexpr-plusplus/actions/workflows/i18n-check.yml)
[![Spell Check](https://github.com/Blake-Madden/i18n-check/actions/workflows/spell-check.yml/badge.svg)](https://github.com/Blake-Madden/i18n-check/actions/workflows/spell-check.yml)

## Compatibility Advisory

Note: for current users of TinyExpr++, please see the [compatibility advisory](CompatibilityAdvisory.md) for recent changes.

## Embedded Programming

For notes on embedded programming, please refer to the [embedded programming](Embedded.md) overview.

## Features

- **C++17 with no dependencies**.
- Single source file and header file.
- Simple and fast.
- Implements standard operator precedence.
- Implements logical and comparison operators.
- Exposes standard C math functions (`sin`, `sqrt`, `ln`, etc.), as well as some Excel-like functions (e.g., `AVERAGE()` and `IF()`).
- Can add custom functions and variables easily.
- Can bind constants at eval-time.
- Supports variadic functions (taking between 1-7 arguments).
- Case insensitive.
- Supports non-US formulas (e.g., `pow(2,2; 2)` instead of `pow(2.2, 2)`).
- Supports C and C++ style comments.
- Released under the zlib license - free for nearly any use.
- Easy to use and integrate with your code.
- Thread-safe; parser is in a self-contained object.

## Changes from TinyExpr

The following are changes from the original TinyExpr C library:

- Compiles as C++17 code.
- `te_*` functions are now wrapped in a `te_parser` class.
- `te_interp()`, `te_compile()`, and `te_eval()` have been replaced with `te_parser::compile()`, `te_parser::evaluate()`, and `te_parser::set_variables_and_functions()`.
    `set_variables_and_functions()` sets your list of custom functions and variables. `compile()` compiles and optimizes an expression.
    Finally, `evaluate()` will use the already compiled expression and return its result.
    `evaluate()` also has an overload that compiles and evaluates an expression in one call.
- Variable/function types (e.g., `TE_FUNCTION0`) have been removed; types are now deduced by the compiler. The available flags
  for variables and functions are now just combinations of `TE_DEFAULT`, `TE_PURE`, and `TE_VARIADIC`.
- Formula parsing is now case insensitive.
- Added support for variadic functions (can accept 1-7 arguments); enabled through the `TE_VARIADIC` flag.
  (Refer to the `AVERAGE()` function in `tinyexp.cpp` for an example.)
- Added support for parsing formulas in non-US format (e.g., `pow(2,2; 2)` instead of `pow(2.2, 2)`). Useful for when the program's locale is non-English.
  (Refer to [Example 4](Examples.md) for a demonstration.)
- `te_expr` is now a derivable base class. This means that you can derive from `te_expr`, add new fields to that derived class (e.g., arrays, strings, even other classes)
  and then use a custom class as an argument to the various function types that accept a `te_expr*` parameter. The function that you connect can then `dynamic_cast<>`
  this argument and use its custom fields, thus greatly enhancing the functionality for these types of functions.
  (See below for example.)
- Added exception support, where exceptions are thrown for situations like providing invalid separators. Calls to `compile` and `evaluate` should be wrapped in `try`...`catch` blocks.
- Memory management is handled by the `te_parser` class (you no longer need to call `te_free`). Also, replaced `malloc/free` with `new/delete`.
- Stricter type safety; uses `std::variant` (instead of unions) that support `double`, `const double*`,
  and 16 specific function signatures (that will work with lambdas or function pointers).
  Also uses `std::initializer` lists (instead of various pointer operations).
- Separate enums are now used between `te_expr` and `state`'s types and are more strongly typed.
- Added support for C and C++ style comments (`//` and `/**/`).
- `compile()` and `evaluate()` now accept `std::string_view`s, meaning that these functions can accept either `char*` and `std::string` arguments.
- Added support for `volatile` (refer to [embedded programming](Embedded.md) for details).
- Added new built-in functions:
  - `and`: returns true (i.e., non-zero) if all conditions are true (accepts 1-7 arguments).
  - `average`: returns the mean for a range of values (accepts 1-7 arguments).
  - `bitlshift`: left shift operator.\n
     Negative shift amount arguments (similar to **Excel**) is supported.
  - `bitrshift`: right shift operator.\n
     Negative shift amount arguments (similar to **Excel**) is supported.
  - `cot`: returns the cotangent of an angle.
  - `combin`: alias for `ncr()`, like the **Excel** function.
  - `clamp`: constrains a value to a range.
  - `fact`: alias for `fac()`, like the **Excel** function.
  - `false`: returns `false` (i.e., `0`) in a boolean expression.
  - `if`: if a value is true (i.e., non-zero), then returns the second argument; otherwise, returns the third argument.
  - `max`: returns the maximum of a range of values (accepts 1-7 arguments).
  - `min`: returns the minimum of a range of values (accepts 1-7 arguments).
  - `mod`: returns remainder from a division.
  - `nan`: returns `NaN` (i.e., Not-a-Number) in a boolean expression.
  - `or`: returns true (i.e., non-zero) if any condition is true (accepts 1-7 arguments).
  - `not`: returns logical negation of value.
  - `permut`: alias for `npr()`, like the **Excel** function.
  - `power`: alias for `pow()`, like the **Excel** function.
  - `rand`: returns random number between `0` and `1`.\n
     Note that this implementation uses the Mersenne Twister (`mt19937`) to generate random numbers.
  - `round`: returns a number, rounded to a given decimal point.
     (Decimal point is optional and defaults to `0`.)\n
     Negative number-of-digits arguments (similar to **Excel**) is supported.
  - `sign`: returns the sign of a number: `1` if positive, `-1` if negative, `0` if zero.
  - `sum`: returns the sum of a list of values (accepts 1-7 arguments).
  - `sqr`: returns a number squared.
  - `tgamma`: returns gamma function of a specified value.
  - `trunc`: returns the integer part of a number.
  - `true`: returns `true` (i.e., `1`) in a boolean expression.
- Added new operators:
  - `&`    logical AND.
  - `|`    logical OR.
  - `=`    equal to.
  - `==`   equal to.
  - `<>`   not equal to.
  - `!=`   not equal to.
  - `<`    less than.
  - `<=`   less than or equal to.
  - `>`    greater than.
  - `>=`   greater than or equal to.
  - `<<`   left shift operator.
  - `>>`   right shift operator.
  - `**`   exponentiation (alias for `^`).
- `round` now supports negative number of digit arguments, similar to **Excel**.
  For example, `ROUND(-50.55,-2)` will yield `-100`.
- Custom variables and functions are now stored in a `std::set`
  (which can be easily accessed and updated via the new `get_variables_and_functions()/set_variables_and_functions()` functions).
- Added `is_function_used()` and `is_variable_used()` functions to see if a specific function or variable was used in the last parsed formula.
- Added `set_constant()` function to find and update the value of a constant (custom) variable by name.
  (In this context, a constant is a variable mapped to a double value in the parser, rather than mapped to a runtime variable.)
- Added `get_constant()` function to return the value of a constant (custom) variable by name.
- Binary search (i.e., `std::set`) is now used to look up custom variables and functions (small optimization).
- You no longer need to specify the number of arguments for custom functions; it will deduce that for you.
- The position of an error when evaluating an expression is now managed by the `te_parser` class and accessible via `get_last_error_position()`.
- Some parsing errors can provide error messages available via `get_last_error_message()`.
- The position of aforementioned error is now 0-indexed (not 1-indexed); `te_parser::npos` indicates that there was no error.
- Added `success()` function to indicate if the last parse succeeded or not.
- Added `get_result()` function to get result from the last call to `evaluate` or `compile`.
- Now uses `std::numeric_limits` for math constants (instead of macro constants).
- Replaced C-style casts with `static_cast<>`.
- Replaced all macros with `constexpr`s and lambdas.
- Replaced custom binary search used for built-in function searching; `std::set` is used now.
- Now uses `nullptr` (instead of `0`).
- All data fields are now initialized.
- Added [Doxygen](https://github.com/doxygen/doxygen) comments.
- Removed `te_print()` debug function.
- Added `list_available_functions_and_variables()` function to display all available built-in and custom
  functions and variables.
- Added `get_expression()` function to get the last formula used.
- Added `[[nodiscard]]` attributes to improve compile-time warnings.
- Added `constexpr` and `noexcept` for C++ optimization.

## Building

TinyExpr++ is self-contained in two files: `tinyexpr.cpp` and `tinyexpr.h`. To use
TinyExpr++, simply add those two files to your project.

The documentation can be built using the following:

```
doxygen doc/Doxyfile
```

## Short Example

Here is a minimal example to evaluate an expression at runtime.

```cpp
#include "tinyexpr.h"
#include <iostream>
#include <iomanip>
#include <string>

te_parser tep;

const double r = tep.evaluate("sqrt(5^2+7^2+11^2+(8-2)^2)");
std::cout << std::setprecision(8) << "The expression:\n\t" <<
    tep.get_expression() << "\nevaluates to:\n\t" <<
    r << "\n";
// prints 15.198684
```

## Usage

TinyExpr++'s `te_parser` class defines these functions:

```cpp
double evaluate(const std::string_view expression);
double get_result();
bool success();
int64_t get_last_error_position();
std::string get_last_error_message();
set_variables_and_functions(const std::set<te_variable>& vars);
std::set<te_variable>& get_variables_and_functions();
add_variable_or_function(const te_variable& var);
get_decimal_separator();
set_decimal_separator();
get_list_separator();
set_list_separator();
```

`evaluate()` takes an expression and immediately returns the result of it. If there
is a parse error, then it returns NaN (which can be verified by using `std::isnan()`).

`get_result()` can be called anytime afterwards to retrieve the result from `evaluate()`.

`success()` can be called to see if the previous call `evaluate()` succeeded or not.

If the parse failed, calling `get_last_error_position()` will return the 0-based index of where in the
expression the parse failed. For some errors, `get_last_error_message()` will return a more detailed message.

`set_variables_and_functions()`, `get_variables_and_functions()`, and `add_variable_or_function()` are used
to add custom variables and functions to the parser.

`get_decimal_separator()`/`set_decimal_separator()` and
`get_list_separator()`/`set_list_separator()` can be used to parse non-US formatted formulas.

Example usage:

```cpp
te_parser tep;

// Returns 10, error position is set to te_parser::npos (i.e., no error).
double result = tep.evaluate("(5+5)");
// Returns NaN, error position is set to 3.
double result2 = tep.evaluate("(5+5");
```

Give `set_variables_and_functions()` a list of constants, bound variables, and function pointers/lambdas.

`evaluate()` will then evaluate expressions using these variables and functions.

**example usage:**

```cpp
#include "tinyexpr.h"
#include <iostream>

double x{ 0 }, y{ 0 };
// Store variable names and pointers.
te_parser tep;
tep.set_variables_and_functions({{"x", &x}, {"y", &y}});

// Compile the expression with variables.
auto result = tep.evaluate("sqrt(x^2+y^2)");

if (tep.success())
    {
    x = 3; y = 4;
    // Will use the previously used expression, returns 5.
    const double h1 = tep.evaluate();

    x = 5; y = 12;
    // Returns 13.
    const double h2 = tep.evaluate();
    }
else
    {
    std::cout << "Parse error at " <<
        std::to_string(tep.get_last_error_position()) << "\n";
    }
```

## Longer Example

Here is a complete example that will evaluate an expression passed in from the command
line. It also does error checking and binds the variables `x` and `y` to `3` and `4`, respectively.

```cpp
#include "tinyexpr.h"
#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
    {
    if (argc < 2)
        {
        std::cout << "Usage: example \"expression\"\n";
        return EXIT_FAILURE;
        }

    const char *expression = argv[1];
    std::cout << "Evaluating:\n\t" << expression << "\n";

    /* This shows an example where the variables
       x and y are bound at eval-time. */
    double x{ 0 }, y{ 0 };
    // Store variable names and pointers.
    te_parser tep;
    tep.set_variables_and_functions({{"x", &x}, {"y", &y}});

    /* This will compile the expression and check for errors. */
    auto result = tep.evaluate(expression);

    if (tep.success())
        {
        /* The variables can be changed here, and eval can be called as many
           times as you like. This is fairly efficient because the parsing has
           already been done. */
        x = 3; y = 4;
        const double r = tep.evaluate();
        std::cout << "Result:\n\t" << r << "\n";
        }
    else
        {
        /* Show the user where the error is at. */
        std::cout << "\t " << std::setfill(' ') <<
            std::setw(tep.get_last_error_position()) << '^' <<
            "\tError near here\n";
        }

    return EXIT_SUCCESS;
    }
```

This produces the output:

    $ "sqrt(x^2+y2)"
       Evaluating:
            sqrt(x^2+y2)
                      ^
       Error near here

    $ "sqrt(x^2+y^2)"
      Evaluating:
            sqrt(x^2+y^2)
      Result:
            5.000000

## Binding to Custom Functions

TinyExpr++ can also call custom functions. Here is a short example:

```cpp
double my_sum(double a, double b)
    {
    /* Example function that adds two numbers together. */
    return a + b;
    }

te_parser tep;
tep.set_variables_and_functions(
{
    { "mysum", my_sum } // function pointer
});

const double r = tep.evaluate("mysum(5, 6)");
// will be 11
```

Here is an example of using a lambda:

```cpp
te_parser tep;
tep.set_variables_and_functions({
    { "mysum",
        [](double a, double b) noexcept
            { return a + b; } }
    });

const double r = tep.evaluate("mysum(5, 6)");
// will be 11
```

## Binding to Custom Classes

A class derived from `te_expr` can be bound to custom functions. This enables you to
have full access to an object (via these functions) when parsing an expression.

The following demonstrates creating a `te_expr`-derived class which contains an array of values:

```cpp
class te_expr_array : public te_expr
    {
public:
    explicit te_expr_array(const variable_flags type) noexcept :
        te_expr(type) {}
    std::array<double, 5> m_data = { 5, 6, 7, 8, 9 };
    };
```

Next, create two functions that can accept this object and perform
actions on it. (Note that proper error handling is not included for brevity.):

```cpp
// Returns the value of a cell from the object's data.
double cell(const te_expr* context, double a)
    {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    return static_cast<double>(c->m_data[static_cast<size_t>(a)]);
    }

// Returns the max value of the object's data.
double cell_max(const te_expr* context)
    {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    return static_cast<double>(
        *std::max_element(c->m_data.cbegin(), c->m_data.cend()));
    }
```

Finally, create an instance of the class and connect the custom functions to it,
while also adding them to the parser:

```cpp
te_expr_array teArray{ TE_DEFAULT };

te_parser tep;
tep.set_variables_and_functions(
    {
        {"cell", cell, TE_DEFAULT, &teArray},
        {"cellmax", cell_max, TE_DEFAULT, &teArray}
    });

// change the object's data and evaluate their summation
// (will be 30)
teArray.m_data = { 6, 7, 8, 5, 4 };
auto result = tep.evaluate("SUM(CELL 0, CELL 1, CELL 2, CELL 3, CELL 4)");

// call the other function, getting the object's max value
// (will be 8)
res = tep.evaluate("CellMax()");
```

## Non-US Formatted Formulas

TinyExpr++ supports other locales and non-US formatted formulas. Here is an example:

```cpp
#include "tinyexpr.h"
#include <iostream>
#include <iomanip>
#include <locale>
#include <clocale>

int main(int argc, char *argv[])
    {
    /* Set locale to German.
       This string is platform dependent. The following works on Windows,
       consult your platform's documentation for more details.*/
    setlocale(LC_ALL, "de-DE");
    std::locale::global(std::locale("de-DE"));

    /* After setting your locale to German, functions like strtod() will fail
       with values like "3.14" because it expects "3,14" instead.
       To fix this, we will tell the parser to use "," as the decimal separator
       and ";" as list argument separator.*/

    const char *expression = "pow(2,2; 2)"; // instead of "pow(2.2, 2)"
    std::cout << "Evaluating:\n\t" << expression << "\n";

    te_parser tep;
    tep.set_decimal_separator(',');
    tep.set_list_separator(';');

    /* This will compile the expression and check for errors. */
    auto r = tep.evaluate(expression);

    if (tep.success())
        {
        const double r = tep.evaluate(expression);
        std::cout << "Result:\n\t" << r << "\n";
        }
    else
        {
        /* Show the user where the error is at. */
        std::cout << "\t " << std::setfill(' ') <<
            std::setw(tep.get_last_error_position()) << '^' <<
            "\tError near here\n";
        }

    return EXIT_SUCCESS;
    }
```

This produces the output:

    $ Evaluating:
        pow(2,2; 2)
      Result:
        4,840000

Refer to [Examples](Examples.md) for more examples.

## How it Works

`te_parser::evaluate()` uses a simple recursive descent parser to compile your
expression into a syntax tree. For example, the expression `"sin x + 1/4"`
parses as:

![example syntax tree](doc/e1.png)

`te_parser::evaluate()` also automatically prunes constant branches. In this example,
the compiled expression returned by `te_compile()` would become:

![example syntax tree](doc/e2.png)

## Performance

TinyExpr++ is fairly fast compared to compiled C when the expression is short, when the
expression does hard calculations (e.g., exponentiation), and when some of the
work can be simplified by `evaluate()`. TinyExpr++ is slow compared to C when the
expression is long and involves only basic arithmetic.

Here are some example benchmarks:

| Expression | TinyExpr++ | Native C | Comparison  |
| :------------- |-------------:| -----:|----:|
| sqrt(a^1.5+a^2.5) | 1,707 ns | 58.25 ns | 29% slower |
| a+5 | 535 ns | 0.67 ns | 798% slower |
| a+(5*2) | 0.73 ns | 969 ns | 1,327% slower |
| (a+5)*2 | 0.66 ns | 980 ns | 1,484% slower |
| (1/(a+1)+2/(a+2)+3/(a+3)) | 3,388 ns | 3.941 ns | 859%  slower |

Note that TinyExpr++ is slower compared to TinyExpr because of additional type safety checks.

## Grammar

TinyExpr++ parses the following grammar (from lowest-to-highest operator precedence):

    <list>      =    <expr> {(",", ";" [dependent on locale]) <expr>}
    <expr>      =    <term> {("&" | "|") <term>}
    <expr>      =    <term> {("<>" | "!=" | "=" | "<") | "<=") | ">" | ">=") <term>}
    <expr>      =    <term> {("<<" | ">>") <term>}
    <expr>      =    <term> {("+" | "-") <term>}
    <term>      =    <factor> {("*" | "/" | "%") <factor>}
    <factor>    =    <power> {("^" | "**") <power>}
    <power>     =    {("-" | "+")} <base>
    <base>      =    <constant>
                   | <variable>
                   | <function-0> {"(" ")"}
                   | <function-1> <power>
                   | <function-X> "(" <expr> {"," <expr>} ")"
                   | "(" <list> ")"

In addition, whitespace between tokens is ignored.

Valid variable names consist of a letter followed by any combination
of: letters `a` through `z` or `A` through `Z`, the digits `0` through `9`, and
underscore. Constants can be integers, decimal numbers, or in scientific
notation (e.g., `1e3` for `1000`). A leading zero is not required (e.g., `.5`
for `0.5`).

## Supported Functions

TinyExpr++ supports addition (`+`), subtraction/negation (`-`), multiplication (`*`),
division (`/`), exponentiation (`^`), modulus (`%`), and left/right shift (`<<`, `>>`)
with the normal operator precedence (the one exception being that exponentiation is evaluated
left-to-right, but this can be changed - see below).

Please refer to the [TinyExpr++ Reference Manual](doc/manual/_book/TinyExpr++-Reference-Manual.pdf)
for a full list of available functions.

## Compile-time Options

By default, TinyExpr++ does exponentiation from left to right. For example:

`a^b^c == (a^b)^c` and `-a^b == (-a)^b`

This is by design; it's the way that spreadsheets do it
(e.g., LibreOffice Calc, Excel, Google Sheets).

If you would rather have exponentiation work from right to left, you need to
define `TE_POW_FROM_RIGHT` when compiling. With `TE_POW_FROM_RIGHT` defined, the
behavior is:

`a^b^c == a^(b^c)` and `-a^b == -(a^b)`

That will match how many scripting languages do it (e.g., Python, Ruby).

Also, if you'd like `log` to default to the natural log instead of `log10`,
then define `TE_NAT_LOG`.

Note that symbols can be defined by passing them to your compiler's
command line (or in a Cmake configuration) as such: `-DTE_POW_FROM_RIGHT`

## Hints

- To allow constant optimization, surround constant expressions in parentheses.
  For example, `x+(1+5)` will evaluate the `(1+5)` expression at compile time and
  compile the entire expression as `x+6`, saving a runtime calculation. The
  parentheses are important, because TinyExpr++ will not change the order of
  evaluation. If you instead compiled `x+1+5`, TinyExpr++ will insist that `1` is
  added to `x` first, and `5` is added to the result second.
