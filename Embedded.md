# Embedded Programming

## Volatility

If needing to use a `te_parser` object as `volatile`
(e.g., accessing it in a system interrupt), then you will need
to do the following.

First, declare your `te_parser` as a non-`volatile` object outside
of the interrupt function (e.g., globally):

```cpp
te_parser tep;
```
Then, in your interrupt function, create a `volatile` reference to it:

```cpp
void OnInterrupt()
    {
    volatile te_parser& vTep = tep;
    }
```
Functions in `te_parser` which have `volatile` overloads can then be
called directly:

```cpp
void OnInterrupt()
    {
    volatile te_parser& vTep = tep;
    vTep.set_list_separator(',');
    vTep.set_decimal_separator('.');
    }
```
The following functions in the `te_parser` class have `volatile` overloads:

- `get_result()`
- `success()`
- `get_last_error_position()`
- `get_decimal_separator()`
- `set_decimal_separator()`
- `get_list_separator()`
- `set_list_separator()`

For any other functions, use `const_cast<>` to remove the parser
reference's volatility:

```cpp
void OnInterrupt()
    {
    volatile te_parser& vTep = tep;

    // Use 'const_cast<te_parser&>(vTep)' to access
    // non-volatile functions.
    const_cast<te_parser&>(vTep).set_variables_and_functions(
         { {"STRESS_L", 10.1},
           {"P_LEVEL", .5} });
    const_cast<te_parser&>(vTep).compile(("STRESS_L*P_LEVEL"));

    if (vTep.success())
        {
        auto res = vTep.get_result();
        // Do something else...
        }
    }
```

Note that it is required to make the initial declaration of your
`te_parser` non-`volatile`; otherwise, the `const_cast<>` to the
`volatile` reference will cause undefined behavior.

## Exception Handling

TinyExpr++ requires exception handling, although it does attempt to
minimize the use of exceptions (e.g., `noexcept` is used extensively).
Syntax errors will be reported without the use of exceptions;
issues such as division by zero or arithmetic overflows, however,
will internally use exceptions. The parser will trap these
exceptions and return NaN (not a number) as the result.

Exceptions can also be thrown when defining custom functions or variables
which do not follow the proper naming convention.
(Function and variable names must only contain the characters
`a`-`z`, `A`-`Z`, `0`-`9`, and `_`, and must begin with a letter.)

Finally, specifying an illegal character for a list or decimal separator
can also throw.

The following functions in `te_parser` can throw and should be wrapped
in `try`/`catch` blocks:

- `compile()`
- `evaluate()`
- `set_variables_and_functions()`
- `add_variable_or_function()`
- `set_decimal_separator()`
- `set_list_separator()`

The caught `std::runtime_error` exception will provide a description
of the error in its `what()` method.

## Virtual Functions

TinyExpr++ does not use virtual functions or derived classes,
unless you create a custom class derived from `te_expr` yourself
(refer to [Example 5](Examples.md)).
(`te_expr` defines a virtual destructor that may be implicitly optimized to
`final` if no derived classes are defined.)
