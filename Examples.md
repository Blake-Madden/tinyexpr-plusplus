# Examples

The following are full-program examples.

## Example 1

```cpp
include "tinyexpr.h"
#include <cstdio>

int main(int argc, char *argv[])
{
    te_parser tep;
    const char *c = "sqrt(5^2+7^2+11^2+(8-2)^2)";
    double r = tep.evaluate(c);
    printf("The expression:\n\t%s\nevaluates to:\n\t%f\n", c, r);
    return 0;
}
```

## Example 2

```cpp
#include "tinyexpr.h"
#include <cstdio>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: example2 \"expression\"\n");
        return 0;
    }

    const char* expression = argv[1];
    printf("Evaluating:\n\t%s\n", expression);

    /* This shows an example where the variables
     * x and y are bound at eval-time. */
    double x{ 0 }, y{ 0 };
    // Store variable names and pointers.
    te_parser tep;
    tep.set_variables_and_functions({ {"x", &x}, {"y", &y} });

    /* This will compile the expression and check for errors. */
    if (tep.compile(expression)) {
        /* The variables can be changed here, and eval can be called as many
         * times as you like. This is fairly efficient because the parsing has
         * already been done. */
        x = 3; y = 4;
        const double r = tep.evaluate();
        printf("Result:\n\t%f\n", r);
    }
    else {
        /* Show the user where the error is at. */
        printf("\t%*s^\nError near here", tep.get_last_error_position(), "");
    }

    return 0;
}
```

## Example 3

```cpp
#include "tinyexpr.h"
#include <cstdio>


/* An example of calling a C function. */
double my_sum(double a, double b) {
    printf("Called C function with %f and %f.\n", a, b);
    return a + b;
}


int main(int argc, char *argv[])
{
    const char *expression = "mysum(5, 6)";
    printf("Evaluating:\n\t%s\n", expression);

    te_parser tep;
    tep.set_variables_and_functions({{"mysum", my_sum}});

    if (tep.compile(expression)) {
        const double r = tep.evaluate();
        printf("Result:\n\t%f\n", r);
    } else {
        /* Show the user where the error is at. */
        printf("\t%*s^\nError near here", tep.get_last_error_position(), "");
    }


    return 0;
}
```

## Example 4

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

    if (tep.compile(expression)) {
        const double r = tep.evaluate(); printf("Result:\n\t%f\n", r);
    } else {
        /* Show the user where the error is at. */
        printf("\t%*s^\nError near here", tep.get_last_error_position(), "");
    }

    return 0;
}
```