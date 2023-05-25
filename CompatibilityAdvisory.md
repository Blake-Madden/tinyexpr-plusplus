# Compatibility Advisory

`set_variables_and_functions()` now requires a `std::set<te_variable>` argument instead of a
`std::vector<te_variable>`. Prefer calling this function with an initializer list (see [Example 2](Examples.md))
or use `std::set<te_variable>`.

The previously deprecated functions:

- `set_vars()`
- `add_var()`
- `get_vars()`
- `find_variable()`

have been removed. Use the following instead:

- `set_variables_and_functions()`
- `add_variable_or_function()`
- `get_variables_and_functions()`
- `find_variable_or_function()`
