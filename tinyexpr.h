// SPDX-License-Identifier: Zlib
/*
 * TINYEXPR - Tiny recursive descent parser and evaluation engine in C
 *
 * Copyright (c) 2015-2020 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/*
 * TINYEXPR++ - Tiny recursive descent parser and evaluation engine in C++
 * 
 * Copyright (c) 2020-2023 Blake Madden
 * 
 * C++ version of the TinyExpr library.
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __TINYEXPR_PLUS_PLUS_H__
#define __TINYEXPR_PLUS_PLUS_H__

#include <vector>
#include <variant>
#include <string>
#include <limits>
#include <initializer_list>
#include <algorithm>
#include <random>
#include <string_view>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <stdexcept>
#include <cctype>
#include <set>
#include <utility>

class te_expr;

// regular functions
using te_fun0 = double (*)();
using te_fun1 = double (*)(double);
using te_fun2 = double (*)(double, double);
using te_fun3 = double (*)(double, double, double);
using te_fun4 = double (*)(double, double, double, double);
using te_fun5 = double (*)(double, double, double, double, double);
using te_fun6 = double (*)(double, double, double, double, double, double);
using te_fun7 = double (*)(double, double, double, double, double, double, double);
// context functions (where te_variable passes a client's te_expr as the first argument)
using te_confun0 = double (*)(const te_expr*);
using te_confun1 = double (*)(const te_expr*, double);
using te_confun2 = double (*)(const te_expr*, double, double);
using te_confun3 = double (*)(const te_expr*, double, double, double);
using te_confun4 = double (*)(const te_expr*, double, double, double, double);
using te_confun5 = double (*)(const te_expr*, double, double, double, double, double);
using te_confun6 = double (*)(const te_expr*, double, double, double, double, double, double);
using te_confun7 = double (*)(const te_expr*, double, double, double, double, double, double, double);

// do not change the ordering of these, the indices are used to determine the value type of a te_variable
using variant_type = std::variant<double, const double*, // indices 0-1
    // indices 2-9
    te_fun0, te_fun1, te_fun2, te_fun3, te_fun4, te_fun5, te_fun6, te_fun7,
    // indices 10-17
    te_confun0, te_confun1, te_confun2, te_confun3, te_confun4, te_confun5, te_confun6, te_confun7>;

/// @brief A variable's flags, effecting how it is evaluated.
/// @note This is a bitmask, so flags (TE_PURE and TE_VARIADIC) can be OR'ed.
/// @internal Note that because this is a bitmask, don't declare it as an enum class,
///     just a C-style enum.
enum variable_flags
    {
    /// @brief Don't do anything special when evaluating.
    TE_DEFAULT = 0,
    /// @brief Don't update when simple evaluation is ran
    ///     (i.e., only updated when expression is compiled).
    TE_PURE = (1 << 0),
    /// @brief Function that can take 1-7 argument (unused arguments are set to NaN).
    TE_VARIADIC = (1 << 1)
    };

/// @private
class te_string_less
    {
public:
    [[nodiscard]]
    bool operator()(const std::string& lhv, const std::string& rhv) const
        {
        const auto minStrLen = std::min(lhv.length(), rhv.length());
        for (size_t i = 0; i < minStrLen; ++i)
            {
            const auto lhCh = tolower(lhv[i]);
            const auto rhCh = tolower(rhv[i]);
            if (lhCh == rhCh)
                { continue; }
            return (lhCh < rhCh);
            }
        return (lhv.length() < rhv.length());
        }
    // We can assume that we are only dealing with a-z, A-Z, 0-9, and _,
    // so use a simpler and faster tolower.
    [[nodiscard]]
    constexpr static char tolower(const char ch) noexcept
        { return ch + (32 * (ch >= 'A' && ch <= 'Z')); }
    };

/// @brief A compiled expression.
/// @details Can also be an additional object that can be passed to
///     te_confun0-te_confun7 functions via a te_variable.
class te_expr
    {
public:
    te_expr(const variable_flags type, const variant_type& value) noexcept :
        m_type(type), m_value(value) {}
    explicit te_expr(const variable_flags type) noexcept : m_type(type) {}
    /// @private
    te_expr() noexcept {};
    /// @private
    te_expr(const te_expr&) = delete;
    /// @private
    te_expr& operator=(const te_expr&) = delete;
    /// @private
    virtual ~te_expr() {}
    /// @brief The type that m_value represents.
    variable_flags m_type{ TE_DEFAULT };
    /// @brief The double constant, double pointer, or function to bind to.
    variant_type m_value{ 0.0 };
    /// @brief Additional parameters.
    std::vector<te_expr*> m_parameters{ nullptr };
    };

/// @brief Custom variable or function that can be added to a te_parser.
class te_variable
    {
public:
    /// @private
    using name_type = std::string;
    /// @private
    [[nodiscard]]
    bool operator<(const te_variable& that) const
        { return te_string_less{}(m_name, that.m_name); }
    /// @brief The name as it would appear in a formula.
    name_type m_name;
    /// @brief The double constant, double pointer, or function to bind the name to.
    variant_type m_value;
    /// @brief The type that m_value represents.
    variable_flags m_type{ TE_DEFAULT };
    /// If @c m_value is a function pointer of type `te_confun0`-`te_confun7`, then
    /// this is passed to that function when called. This is useful for passing
    /// an object which manages additional data to your functions.
    te_expr* m_context{ nullptr };
    };

/// @brief Math formula parser.
class te_parser
    {
public:
    /// @private
    te_parser() = default;
    /// @private
    te_parser(const te_parser&) = delete;
    /// @private
    te_parser& operator=(const te_parser&) = delete;
    /// @private
    ~te_parser()
        { te_free(m_compiledExpression); }
    static constexpr int64_t npos = -1;
    /** @brief Parses the input @c expression.
        @param expression The formula to compile.
        @returns Whether the expression compiled or not. (This can be checked
            by calling success() afterwards as well.)
        @sa success().
        @note Returns NaN if division or modulus by zero occurs.
        @throws std::runtime_error Throws an exception in the case of arithmetic overflows
            (e.g., `1 << 64` would cause an overflow).*/
    bool compile(const std::string_view expression);
    /** @brief Evaluates expression passed to compile() previously and returns its result.
        @returns The result, or NaN on error.
        @throws std::runtime_error Throws an exception in the case of arithmetic overflows
            (e.g., `1 << 64` would cause an overflow).*/
    [[nodiscard]]
    double evaluate();
    /** @brief Compiles and evaluates an expression and returns its result.
        @param expression The formula to compile and evaluate.
        @returns The result, or NaN on error.
        @note Returns NaN if division or modulus by zero occurs.
        @throws std::runtime_error Throws an exception in the case of arithmetic overflows
            (e.g., `1 << 64` would cause an overflow).*/
    [[nodiscard]]
    double evaluate(const std::string_view expression);
    /// @returns The last call to evaluate()'s result (which will be NaN on error).
    [[nodiscard]]
    double get_result() const noexcept
        { return m_result; }
    /// @private
    [[nodiscard]]
    double get_result() const volatile noexcept
        { return m_result; }
    /// @returns Whether the last call to compile() was successful.
    /// @sa get_last_error_position().
    [[nodiscard]]
    bool success() const noexcept
        { return m_parseSuccess; }
    [[nodiscard]]
    bool success() const volatile noexcept
        { return m_parseSuccess; }

    /// @returns The zero-based index into the last parsed expression where the parse failed,
    ///     or te_parser::npos if no error occurred.
    /// @note Call success() to see if the last parse succeeded or not.
    [[nodiscard]]
    int64_t get_last_error_position() const noexcept
        { return m_errorPos; }
    /// @private
    [[nodiscard]]
    int64_t get_last_error_position() const volatile noexcept
        { return m_errorPos; }

    /// @returns Any error message from the last parse.
    [[nodiscard]]
    const std::string& get_last_error_message() const noexcept
        { return m_lastErrorMessage; }

    /// @brief Sets the list of custom variables and functions.
    /// @param vars The list of variables and functions.
    /// @note Valid variable and function names must begin with a letter from a-z (A-Z),
    ///     followed by additional English letters, numbers, or underscores.
    /// @throws std::runtime_error Throws an exception if an illegal character is found
    ///     in the variable name.
    void set_variables_and_functions(std::set<te_variable> vars)
        {
        for (const auto& var : vars)
            { validate_name(var); }
        m_custom_funcs_and_vars = std::move(vars);
        }
    /// @brief Adds a custom variable or function.
    /// @param var The variable/function to add.
    /// @note Prefer using set_variables_and_functions() as it will be more optimal
    ///     (less sorts will need to be performed).
    /// @throws std::runtime_error Throws an exception if an illegal character is found
    ///     in the variable name.
    void add_variable_or_function(te_variable var)
        {
        validate_name(var);
        m_custom_funcs_and_vars.insert(std::move(var));
        }
    /// @private
    [[nodiscard]]
    const std::set<te_variable>& get_variables_and_functions() const noexcept
        { return m_custom_funcs_and_vars; }
    /// @returns The list of custom variables and functions.
    [[nodiscard]]
    std::set<te_variable>& get_variables_and_functions() noexcept
        { return m_custom_funcs_and_vars; }

    /// @returns The decimal separator used for numbers.
    [[nodiscard]]
    char get_decimal_separator() const noexcept
        { return m_decimalSeparator; }
    /// @private
    [[nodiscard]]
    char get_decimal_separator() const volatile noexcept
        { return m_decimalSeparator; }
    /// @brief Sets the decimal separator used for numbers.
    /// @param sep The decimal separator.
    /// @throws std::runtime_error Throws an exception if an illegal character is used.
    void set_decimal_separator(const char sep)
        {
        if (sep != ',' && sep != '.')
            { throw std::runtime_error("Decimal separator must be either a '.' or ','."); }
        m_decimalSeparator = sep;
        }
    /// @private
    void set_decimal_separator(const char sep) volatile
        {
        if (sep != ',' && sep != '.')
            { throw std::runtime_error("Decimal separator must be either a '.' or ','."); }
        m_decimalSeparator = sep;
        }

    /// @brief Sets a constant variable's value.
    /// @param name The name of the (constant) variable.
    /// @param value The new value to set the constant to.
    /// @note If the constant variable hasn't been added yet (via set_variables_and_functions()),
    ///     then this will add it.\n
    ///     If a variable with the provided name is found but is not a constant,
    ///     then this will be ignored.
    void set_constant(const std::string_view name, const double value)
        {
        auto cvar = find_variable_or_function(name);
        if (cvar == get_variables_and_functions().end())
            {
            add_variable_or_function({ te_variable::name_type{ name}, value });
            }
        else if (is_constant(cvar->m_value))
            {
            auto nh = get_variables_and_functions().extract(cvar);
            nh.value().m_value = value;
            get_variables_and_functions().insert(std::move(nh));
            // if previously compiled, then re-compile since this
            // constant would have been optimized
            if (m_expression.length())
                { compile(m_expression); }
            }
        }
    /// @brief Retrieves a constant variable's value.
    /// @param name The name of the (constant) variable.
    /// @returns The value of the constant variable if found, NaN otherwise.
    [[nodiscard]]
    double get_constant(const std::string_view name) const
        {
        auto cvar = find_variable_or_function(name);
        if (cvar == get_variables_and_functions().cend() || !is_constant(cvar->m_value))
            { return std::numeric_limits<double>::quiet_NaN(); }
        if (const auto val = std::get_if<double>(&cvar->m_value);
            val != nullptr)
            { return *val; }
        else
            { return std::numeric_limits<double>::quiet_NaN(); }
        }

    /// @returns The separator used between function arguments.
    [[nodiscard]]
    char get_list_separator() const noexcept
        { return m_listSeparator; }
    /// @private
    [[nodiscard]]
    char get_list_separator() const volatile noexcept
        { return m_listSeparator; }
    /// @brief Sets the separator used between function arguments.
    /// @param sep The list separator.
    /// @throws std::runtime_error Throws an exception if an illegal character is used.
    void set_list_separator(const char sep)
        {
        if (sep != ',' && sep != ';')
            { throw std::runtime_error("List separator must be either a ',' or ';'."); }
        m_listSeparator = sep;
        }
    /// @private
    void set_list_separator(const char sep) volatile
        {
        if (sep != ',' && sep != ';')
            { throw std::runtime_error("List separator must be either a ',' or ';'."); }
        m_listSeparator = sep;
        }

    /// @returns @c true if @c name is a function that had been used in the last parsed formula.
    /// @param name The name of the function.
    /// @sa compile() and evaluate().
    [[nodiscard]]
    bool is_function_used(const std::string_view name) const
        {
        return m_usedFunctions.find(
            te_variable::name_type{ name }) != m_usedFunctions.cend();
        }
    /// @returns @c true if @c name is a variable that had been used in the last parsed formula.
    /// @param name The name of the variable.
    /// @sa compile() and evaluate().
    [[nodiscard]]
    bool is_variable_used(const std::string_view name) const
        {
        return m_usedVars.find(
            te_variable::name_type{ name }) != m_usedVars.cend();
        }

    /// @returns A report of all available functions and variables.
    [[nodiscard]]
    std::string list_available_functions_and_variables();

    /// @returns The last formula passed to the parser.
    /// @note Comments will be stripped from the original expression.
    [[nodiscard]]
    const std::string& get_expression() const noexcept
        { return m_expression; };
private:
    /// @brief Gets the compiled expression, which will the optimized version
    ///     of the original expression.
    /// @returns The compiled expression.
    [[nodiscard]]
    const te_expr* get_compiled_expression() const noexcept
        { return m_compiledExpression; }
    /// @private
    [[nodiscard]]
    const te_expr* get_compiled_expression() const volatile noexcept
        { return m_compiledExpression; }
    /// @brief Validates that a variable only contains legal characters
    ///     (and has a valid length).
    /// @param var The variable to validate.
    /// @throws std::runtime_error Throws an exception if an illegal character is found.
    void validate_name(const te_variable& var) const
        {
        if (var.m_name.empty())
            { throw std::runtime_error("Variable name is empty."); }
        if (!is_letter(var.m_name[0]))
            {
            throw std::runtime_error(
                std::string("Variable name must begin with an English letter: ") + var.m_name);
            }
        const auto varCharPos = std::find_if(var.m_name.cbegin(), var.m_name.cend(),
            [](const auto ch) noexcept
                {
                return !(is_letter(ch) ||
                    (ch >= '0' && ch <= '9') ||
                    (ch == '_'));
                });
        if (varCharPos != var.m_name.cend())
            {
            throw std::runtime_error(
                std::string("Invalid character in variable name: ") + var.m_name);
            }
        }
    /// @returns An iterator to the custom variable or function with the given @c name,
    ///     or end of get_variables_and_functions() if not found.
    /// @param name The name of the function or variable to search for.
    [[nodiscard]]
    std::set<te_variable>::iterator find_variable_or_function(const std::string_view name)
        {
        if (name.empty())
            { return m_custom_funcs_and_vars.end(); }

        return m_custom_funcs_and_vars.find(
            te_variable{ te_variable::name_type{ name }, 0.0, TE_DEFAULT, nullptr });
        }

    /// @returns An iterator to the custom variable or function with the given @c name,
    ///     or end of get_variables_and_functions() if not found.
    /// @param name The name of the function or variable to search for.
    [[nodiscard]]
    std::set<te_variable>::const_iterator find_variable_or_function(const std::string_view name) const
        {
        if (name.empty())
            { return m_custom_funcs_and_vars.cend(); }

        return m_custom_funcs_and_vars.find(
            te_variable{ te_variable::name_type{ name }, 0.0, TE_DEFAULT, nullptr });
        }

    [[nodiscard]]
    constexpr static auto is_pure(const variable_flags type)
        { return (((type)&TE_PURE) != 0); }
    [[nodiscard]]
    constexpr static auto is_variadic(const variable_flags type)
        { return (((type)&TE_VARIADIC) != 0); }
    /// @returns Number of parameters that a function/variable takes.
    [[nodiscard]]
    inline static auto get_arity(const variant_type& var) noexcept
        {
        return (var.index() == 0 || var.index() == 1) ? 0 :
            (is_function0(var) || is_closure0(var)) ? 0 :
            (is_function1(var) || is_closure1(var)) ? 1 :
            (is_function2(var) || is_closure2(var)) ? 2 :
            (is_function3(var) || is_closure3(var)) ? 3 :
            (is_function4(var) || is_closure4(var)) ? 4 :
            (is_function5(var) || is_closure5(var)) ? 5 :
            (is_function6(var) || is_closure6(var)) ? 6 :
            (is_function7(var) || is_closure7(var)) ? 7 :
            0;
        }
    [[nodiscard]]
    constexpr static bool is_constant(const variant_type& var) noexcept
        { return var.index() == 0; }
    [[nodiscard]]
    constexpr static double get_constant(const variant_type& var)
        {
        assert(std::holds_alternative<double>(var));
        return std::get<0>(var);
        }
    [[nodiscard]]
    constexpr static bool is_variable(const variant_type& var) noexcept
        { return var.index() == 1; }
    [[nodiscard]]
    constexpr static const double* get_variable(const variant_type& var)
        {
        assert(std::holds_alternative<const double*>(var));
        return std::get<1>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function(const variant_type& var) noexcept
        { return (var.index() >= 2 && var.index() <= 9); }
    [[nodiscard]]
    constexpr static bool is_function0(const variant_type& var) noexcept
        { return var.index() == 2; }
    [[nodiscard]]
    constexpr static te_fun0 get_function0(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun0>(var));
        return std::get<2>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function1(const variant_type& var) noexcept
        { return var.index() == 3; }
    [[nodiscard]]
    constexpr static te_fun1 get_function1(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun1>(var));
        return std::get<3>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function2(const variant_type& var) noexcept
        { return var.index() == 4; }
    [[nodiscard]]
    constexpr static te_fun2 get_function2(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun2>(var));
        return std::get<4>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function3(const variant_type& var) noexcept
        { return var.index() == 5; }
    [[nodiscard]]
    constexpr static te_fun3 get_function3(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun3>(var));
        return std::get<5>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function4(const variant_type& var) noexcept
        { return var.index() == 6; }
    [[nodiscard]]
    constexpr static te_fun4 get_function4(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun4>(var));
        return std::get<6>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function5(const variant_type& var) noexcept
        { return var.index() == 7; }
    [[nodiscard]]
    constexpr static te_fun5 get_function5(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun5>(var));
        return std::get<7>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function6(const variant_type& var) noexcept
        { return var.index() == 8; }
    [[nodiscard]]
    constexpr static te_fun6 get_function6(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun6>(var));
        return std::get<8>(var);
        }
    [[nodiscard]]
    constexpr static bool is_function7(const variant_type& var) noexcept
        { return var.index() == 9; }
    [[nodiscard]]
    constexpr static te_fun7 get_function7(const variant_type& var)
        {
        assert(std::holds_alternative<te_fun7>(var));
        return std::get<9>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure(const variant_type& var) noexcept
        { return (var.index() >= 10 && var.index() <= 17); }
    [[nodiscard]]
    constexpr static bool is_closure0(const variant_type& var) noexcept
        { return var.index() == 10; }
    [[nodiscard]]
    constexpr static te_confun0 get_closure0(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun0>(var));
        return std::get<10>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure1(const variant_type& var) noexcept
        { return var.index() == 11; }
    [[nodiscard]]
    constexpr static te_confun1 get_closure1(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun1>(var));
        return std::get<11>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure2(const variant_type& var) noexcept
        { return var.index() == 12; }
    [[nodiscard]]
    constexpr static te_confun2 get_closure2(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun2>(var));
        return std::get<12>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure3(const variant_type& var) noexcept
        { return var.index() == 13; }
    [[nodiscard]]
    constexpr static te_confun3 get_closure3(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun3>(var));
        return std::get<13>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure4(const variant_type& var) noexcept
        { return var.index() == 14; }
    [[nodiscard]]
    constexpr static te_confun4 get_closure4(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun4>(var));
        return std::get<14>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure5(const variant_type& var) noexcept
        { return var.index() == 15; }
    [[nodiscard]]
    constexpr static te_confun5 get_closure5(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun5>(var));
        return std::get<15>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure6(const variant_type& var) noexcept
        { return var.index() == 16; }
    [[nodiscard]]
    constexpr static te_confun6 get_closure6(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun6>(var));
        return std::get<16>(var);
        }
    [[nodiscard]]
    constexpr static bool is_closure7(const variant_type& var) noexcept
        { return var.index() == 17; }
    [[nodiscard]]
    constexpr static te_confun7 get_closure7(const variant_type& var)
        {
        assert(std::holds_alternative<te_confun7>(var));
        return std::get<17>(var);
        }

    struct state
        {
        enum class token_type
            {
            TOK_NULL, TOK_ERROR, TOK_END, TOK_SEP, TOK_OPEN,
            TOK_CLOSE, TOK_NUMBER, TOK_VARIABLE, TOK_FUNCTION, TOK_INFIX
            };
        state(const char* expression, variable_flags varType,
            std::set<te_variable>& vars) :
            m_start(expression), m_next(expression),
            m_varType(varType), m_lookup(vars)
            {}
        const char* m_start{ nullptr };
        const char* m_next{ nullptr };
        token_type m_type{ token_type::TOK_NULL };
        variable_flags m_varType{ TE_DEFAULT };
        variant_type m_value;
        te_expr* context{ nullptr };

        std::set<te_variable>& m_lookup;
        };
    [[nodiscard]]
    static inline te_expr* new_expr(const variable_flags type,
        variant_type value, const std::initializer_list<te_expr*>& parameters)
        {
        te_expr* ret = new te_expr{ type, std::move(value) };
        ret->m_parameters.resize(
            std::max<size_t>(
                std::max<size_t>(parameters.size(), get_arity(ret->m_value)) +
                    (is_closure(ret->m_value) ? 1 : 0),
                0)
            );
        if (parameters.size())
            { std::copy(parameters.begin(), parameters.end(), ret->m_parameters.begin()); }
        return ret;
        }
    [[nodiscard]]
    static inline te_expr* new_expr(const variable_flags type, variant_type value)
        {
        te_expr* ret = new te_expr{ type, std::move(value) };
        ret->m_parameters.resize(static_cast<size_t>(get_arity(ret->m_value)) +
            (is_closure(ret->m_value) ? 1 : 0));
        return ret;
        }
    [[nodiscard]]
    static constexpr bool is_letter(const char c) noexcept
        { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
    /** @brief Parses the input expression and binds variables.
        @param expression The formula to parse.
        @param variables The collection of custom functions and
            variables to add to the parser.
        @returns null on error.*/
    [[nodiscard]]
    te_expr* te_compile(const std::string_view expression,
                        std::set<te_variable>& variables);
    /* Evaluates the expression. */
    [[nodiscard]]
    static double te_eval(const te_expr* n);
    /* Frees the expression. */
    /* This is safe to call on null pointers. */
    static inline void te_free(te_expr* n)
        {
        if (!n) return;
        te_free_parameters(n);
        delete n;
        }
    static void te_free_parameters(te_expr* n);
    static void optimize(te_expr* n);
    [[nodiscard]]
    static auto find_builtin(const std::string_view name)
        {
        return m_functions.find(
            te_variable{ te_variable::name_type{ name }, 0.0, TE_DEFAULT, nullptr });
        }

    [[nodiscard]]
    static auto find_lookup(state* s, const std::string_view name)
        {
        return s->m_lookup.find(
            te_variable{ te_variable::name_type{ name }, 0.0, TE_DEFAULT, nullptr });
        }

    void next_token(state* s);
    [[nodiscard]]
    te_expr* base(state* s);
    [[nodiscard]]
    te_expr* power(state* s);
    [[nodiscard]]
    te_expr* factor(state* s);
    [[nodiscard]]
    te_expr* term(state* s);
    [[nodiscard]]
    te_expr* expr(state* s);
    [[nodiscard]]
    te_expr* expr_level2(state* s);
    [[nodiscard]]
    te_expr* expr_level3(state* s);
    [[nodiscard]]
    te_expr* expr_level4(state* s);
    [[nodiscard]]
    te_expr* list(state* s);

    std::string m_expression;
    te_expr* m_compiledExpression{ nullptr };

    std::set<te_variable>::const_iterator m_currentVar;
    bool m_varFound{ false };
    std::set<te_variable::name_type, te_string_less> m_usedFunctions;
    std::set<te_variable::name_type, te_string_less> m_usedVars;

    static const std::set<te_variable> m_functions;
    std::set<te_variable> m_custom_funcs_and_vars;

    // just keeps track of built-in operators
    static const std::set<std::string> m_operators;

    bool m_parseSuccess{ false };
    int64_t m_errorPos{ 0 };
    std::string m_lastErrorMessage;
    double m_result{ std::numeric_limits<double>::quiet_NaN() };
    char m_decimalSeparator{ '.' };
    char m_listSeparator{ ',' };
    };

#endif // __TINYEXPR_PLUS_PLUS_H__
