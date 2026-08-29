# Compatibility Advisory

## Function Changes

- `MIN`, `MAX`, `SUM`, `AVERAGE`, `IFS`, `OR`, and `AND` now take up to 24 arguments.
- `set_variables_and_functions()` now requires a `std::set<te_variable>` argument instead of a
  `std::vector<te_variable>`. Prefer calling this function with an initializer list
   (see [Example 2](Examples.md)) or use `std::set<te_variable>`.
- `ROUND` now supports number-of-digits arguments higher than `6`.
- `ROUND` now supports negative number-of-digits arguments, similar to **Excel**.
   For example, `ROUND(-50.55,-2)` will yield `-100`.
- `set_decimal_separator()` now only accepts `.` or `,`; will throw otherwise.
- `set_list_separator()` now only accepts `,` or `;`; will throw otherwise.

## String Literals

Functions bound to the new `te_arg_fun` and `te_arg_confun` types can accept quoted string arguments (e.g., `DBQUERY("/Equipment/Temp")`).
Note the following differences from **Excel**:

- Escaping a double quote by doubling it (**Excel**'s `""`) is **not** supported.
  A literal is opened by a `"` and closed by the very next `"`.
  A literal cannot contain a double quote at all.

Also note that `te_variant_type` now includes `std::string_view` as an alternative.
If you have your own overload set taking both a string type and a `te_variant_type`, calls with a string literal may now be ambiguous.

## Removed Functions

The previously deprecated functions:

- `set_vars()`
- `add_var()`
- `get_vars()`
- `find_variable()`
- `log()`

have been removed. Use the following instead:

- `set_variables_and_functions()`
- `add_variable_or_function()`
- `get_variables_and_functions()`
- `find_variable_or_function()`
- Use `ln()` or `log10()` explicitly

## Renamed Data Types

- `variable_flags` has been renamed to `te_variable_flags`.

## Removed Compile-Time Options

`TE_NAT_LOG` has been removed. Use `ln()` or `log10()` explicitly.
