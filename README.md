<img alt="TinyExpr logo" src="https://codeplea.com/public/content/tinyexpr_logo.png" align="right"/>

# TinyExpr++

TinyExpr++ is a C++ version of the TinyExpr library.

TinyExpr++ is a very small recursive descent parser and evaluation engine for
math expressions. It's handy when you want to add the ability to evaluation
math expressions at runtime without adding a bunch of cruft to you project.

In addition to the standard math operators and precedence, TinyExpr++ also supports
the standard C math functions and runtime binding of variables.

## Features

- **C++17 with no dependencies**.
- Single source file and header file.
- Simple and fast.
- Implements standard operators precedence.
- Exposes standard C math functions (sin, sqrt, ln, etc.).
- Can add custom functions and variables easily.
- Can bind variables at eval-time.
- Can support non-US formulas (e.g., "pow(2,2; 2)" instead of "pow(2.2, 2)").
- Released under the zlib license - free for nearly any use.
- Easy to use and integrate with your code
- Thread-safe, parser is in a self-contained object.

## Building

TinyExpr++ is self-contained in two files: `tinyexpr.cpp` and `tinyexpr.h`. To use
TinyExpr++, simply add those two files to your project.

## Short Example

Here is a minimal example to evaluate an expression at runtime.

```cpp
    #include "tinyexpr.h"
    te_parser tep;
    const char* c = "sqrt(5^2+7^2+11^2+(8-2)^2)";
    const double r = tep.interpret("sqrt(5^2+7^2+11^2+(8-2)^2)");
    printf("The expression:\n\t%s\nevaluates to:\n\t%f\n", c, r);
    // prints 15.198684
```


## Usage

TinyExpr++'s te_parser class defines these functions:

```cpp
    double interpret(const char* expression);
    double get_result();
    bool success();
    int get_last_error_position();
    set_vars(const std::vector<te_variable>& vars);
    std::vector<te_variable>& get_vars();
    get_decimal_separator();
    get_list_separator();
```

`interpret()` takes an expression and immediately returns the result of it. If there
is a parse error, it returns NaN.

`get_result()` can be called anytime afterwards to retrieve the result from `interpret()`.

`success()` can be called to see if the previous call `interpret()` succeeded or not.

If the parse failed, calling `get_last_error_position()` will return the 0-based index of where in the expression the parse failed.

**example usage:**

```cpp
    te_parser tep;

    double a = tep.interpret("(5+5)"); /* Returns 10. */
    double b = tep.interpret("(5+5)"); /* Returns 10, error is set to -1 (i.e., no error). */
    double c = tep.interpret("(5+5");  /* Returns NaN, error is set to 3. */
```

Give `set_vars()` a list of constants, bound variables, and function pointers.

`interpret()` will then evaluate expressions using these variables and functions.


**example usage:**

```cpp
    #include "tinyexpr.h"
    #include <stdio.h>

    double x{0}, y{0};
    // Store variable names and pointers.
    te_parser tep;
    tep.set_vars({{"x", &x}, {"y", &y}});

    // Compile the expression with variables.
    auot result = tep.interpret("sqrt(x^2+y^2)");

    if (tep.success()) {
        x = 3; y = 4;
        const double h1 = tep.interpret(); /*Will use the previously used expression, returns 5. */

        x = 5; y = 12;
        const double h2 = tep.interpret(); /* Returns 13. */
    } else {
        printf("Parse error at %d\n", tep.get_last_error_position());
    }
```

## Longer Example

Here is a complete example that will evaluate an expression passed in from the command
line. It also does error checking and binds the variables `x` and `y` to *3* and *4*, respectively.

```cpp
    #include "tinyexpr.h"
    #include <stdio.h>

    int main(int argc, char *argv[])
    {
        if (argc < 2) {
            printf("Usage: example2 \"expression\"\n");
            return 0;
        }

        const char *expression = argv[1];
        printf("Evaluating:\n\t%s\n", expression);

        /* This shows an example where the variables
         * x and y are bound at eval-time. */
        double x{0}, y{0};
        // Store variable names and pointers.
        te_parser tep;
        tep.set_vars({{"x", &x}, {"y", &y}});

        /* This will compile the expression and check for errors. */
        auto result = tep.interpret(expression);

        if (tep.success()) {
            /* The variables can be changed here, and eval can be called as many
             * times as you like. This is fairly efficient because the parsing has
             * already been done. */
            x = 3; y = 4;
            const double r = tep.interpret();
            printf("Result:\n\t%f\n", r);
        } else {
            /* Show the user where the error is at. */
            printf("\t%*s^\nError near here",  tep.get_last_error_position(), "");
        }

        return 0;
    }
```


This produces the output:

    $ example2 "sqrt(x^2+y2)"
        Evaluating:
                sqrt(x^2+y2)
                          ^
        Error near here


    $ example2 "sqrt(x^2+y^2)"
        Evaluating:
                sqrt(x^2+y^2)
        Result:
                5.000000


## Binding to Custom Functions

TinyExpr++ can also call to custom functions implemented in C. Here is a short example:

```cpp
double my_sum(double a, double b) {
    /* Example C function that adds two numbers together. */
    return a + b;
}

te_parser tep;
tep.set_vars({
    {"mysum", my_sum, TE_FUNCTION2} /* TE_FUNCTION2 used because my_sum takes two arguments. */
};)

const double r = tep.interpret("mysum(5, 6)");
```

## Non-US Formatted Formulas

TinyExpr++ supports other locales and non-US formatted formulas. Here is an example:

```cpp
#include "tinyexpr.h"
#include <cstdio>
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
    printf("Evaluating:\n\t%s\n", expression);

    te_parser tep;
    tep.set_decimal_separator(',');
    tep.set_list_separator(';');

    /* This will compile the expression and check for errors. */
    auto r = tep.interpret(expression);

    if (tep.success()) {
        const double r = tep.interpret(expression); printf("Result:\n\t%f\n", r);
    } else {
        /* Show the user where the error is at. */
        printf("\t%*s^\nError near here", tep.get_last_error_position(), "");
    }

    return 0;
}
```

This produces the output:

    $ example4
      Evaluating:
        pow(2,2; 2)
      Result:
        4,840000


## How it works

`te_parser::interpret()` uses a simple recursive descent parser to compile your
expression into a syntax tree. For example, the expression `"sin x + 1/4"`
parses as:

![example syntax tree](doc/e1.png?raw=true)

`te_parser::interpret()` also automatically prunes constant branches. In this example,
the compiled expression returned by `te_compile()` would become:

![example syntax tree](doc/e2.png?raw=true)


## Speed

TinyExpr++ is fairly fast compared to C when the expression is short, when the
expression does hard calculations (e.g. exponentiation), and when some of the
work can be simplified by `interpret()`. TinyExpr++ is slow compared to C when the
expression is long and involves only basic arithmetic.

Here is some example performance numbers taken from the included
**benchmark.cpp** program:

| Expression | interpret time | native C time | slowdown  |
| :------------- |-------------:| -----:|----:|
| sqrt(a^1.5+a^2.5) | 16,363 ms | 13,193 ms | 24.03% slower |
| a+5 | 3,051 ms | 1,255 ms | 143.11% slower |
| a+(5*2) | 1,754 ms | 524 ms | 234.73% slower |
| (a+5)*2 | 3,225 ms | 518 ms | 522.59% slower |
| (1/(a+1)+2/(a+2)+3/(a+3)) | 12,754 ms | 680 ms | 1,775.59%  slower |

Note that TinyExpr++ is slower compared to TinyExpr because of additional type safety checks.


## Grammar

TinyExpr++ parses the following grammar:

    <list>      =    <expr> {"," <expr>}
    <expr>      =    <term> {("+" | "-") <term>}
    <term>      =    <factor> {("*" | "/" | "%") <factor>}
    <factor>    =    <power> {"^" <power>}
    <power>     =    {("-" | "+")} <base>
    <base>      =    <constant>
                   | <variable>
                   | <function-0> {"(" ")"}
                   | <function-1> <power>
                   | <function-X> "(" <expr> {"," <expr>} ")"
                   | "(" <list> ")"

In addition, whitespace between tokens is ignored.

Valid variable names consist of a lower case letter followed by any combination
of: lower case letters *a* through *z*, the digits *0* through *9*, and
underscore. Constants can be integers, decimal numbers, or in scientific
notation (e.g.  *1e3* for *1000*). A leading zero is not required (e.g. *.5*
for *0.5*)


## Functions supported

TinyExpr++ supports addition (+), subtraction/negation (-), multiplication (\*),
division (/), exponentiation (^) and modulus (%) with the normal operator
precedence (the one exception being that exponentiation is evaluated
left-to-right, but this can be changed - see below).

The following C math functions are also supported:

- abs (calls to *fabs*), acos, asin, atan, atan2, ceil, cos, cosh, exp, floor, ln (calls to *log*), log (calls to *log10* by default, see below), log10, pow, sin, sinh, sqrt, tan, tanh

The following functions are also built-in and provided by TinyExpr:

- fac (factorials e.g. `fac 5` == 120)
- ncr (combinations e.g. `ncr(6,2)` == 15)
- npr (permutations e.g. `npr(6,2)` == 30)

Also, the following constants are available:

- `pi`, `e`


## Compile-time options


By default, TinyExpr++ does exponentiation from left to right. For example:

`a^b^c == (a^b)^c` and `-a^b == (-a)^b`

This is by design. It's the way that spreadsheets do it (e.g. Excel, Google Sheets).


If you would rather have exponentiation work from right to left, you need to
define `TE_POW_FROM_RIGHT` when compiling `tinyexpr.c`. There is a
commented-out define near the top of that file. With this option enabled, the
behaviour is:

`a^b^c == a^(b^c)` and `-a^b == -(a^b)`

That will match how many scripting languages do it (e.g. Python, Ruby).

Also, if you'd like `log` to default to the natural log instead of `log10`,
then you can define `TE_NAT_LOG`.

## Hints

- To allow constant optimization, surround constant expressions in parentheses.
  For example "x+(1+5)" will evaluate the "(1+5)" expression at compile time and
  compile the entire expression as "x+6", saving a runtime calculation. The
  parentheses are important, because TinyExpr will not change the order of
  evaluation. If you instead compiled "x+1+5" TinyExpr will insist that "1" is
  added to "x" first, and "5" is added the result second.
