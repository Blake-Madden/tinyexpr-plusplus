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

#include "tinyexpr.h"

// builtin functions
[[nodiscard]]
constexpr static te_type _te_equal(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a == b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_not_equal(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a != b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_less_than(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a < b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_less_than_equal_to(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a <= b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_greater_than(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a > b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_greater_than_equal_to(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a >= b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_and(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a && b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_or(te_type a, te_type b) noexcept
    {
    return static_cast<te_type>((a || b) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_not(te_type a) noexcept
    {
    return !a;
    }

[[nodiscard]]
constexpr static te_type _te_pi() noexcept
    {
    return static_cast<te_type>(3.14159265358979323846);
    }

[[nodiscard]]
constexpr static te_type _te_e() noexcept
    {
    return static_cast<te_type>(2.71828182845904523536);
    }

[[nodiscard]]
static te_type _te_fac(te_type a) noexcept
    { /* simplest version of factorial */
    if (a < 0.0 || std::isnan(a))
        {
        return te_parser::te_nan;
        }
    if (a > (std::numeric_limits<unsigned int>::max)())
        {
        return std::numeric_limits<te_type>::infinity();
        }
    const auto ua = static_cast<size_t>(a);
    unsigned long int result{ 1 }, i{ 1 };
    for (i = 1; i <= ua; i++)
        {
        if (i > (std::numeric_limits<unsigned long>::max)() / result)
            {
            return std::numeric_limits<te_type>::infinity();
            }
        result *= i;
        }
    return static_cast<te_type>(result);
    }

[[nodiscard]]
static te_type _te_absolute_value(te_type n)
    {
    return std::fabs(static_cast<te_type>(n));
    }

[[nodiscard]]
static te_type _te_log(te_type x)
    {
    return std::log(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_log10(te_type x)
    {
    return std::log10(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_pow(te_type x, te_type y)
    {
    return std::pow(static_cast<te_type>(x), static_cast<te_type>(y));
    }

[[nodiscard]]
static te_type _te_tan(te_type x)
    {
    return std::tan(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_tanh(te_type x)
    {
    return std::tanh(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_trunc(te_type x)
    {
    return std::trunc(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_sin(te_type x)
    {
    return std::sin(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_sinh(te_type x)
    {
    return std::sinh(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_sqrt(te_type x)
    {
    if (x < 0)
        {
        throw std::runtime_error("Negative value passed to SQRT.");
        }
    return std::sqrt(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_floor(te_type x)
    {
    return std::floor(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_ceil(te_type x)
    {
    return std::ceil(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_exp(te_type x)
    {
    return std::exp(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_cos(te_type x)
    {
    return std::cos(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_cosh(te_type x)
    {
    return std::cosh(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_acos(te_type x)
    {
    return std::acos(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_asin(te_type x)
    {
    if (std::isfinite(x) && (x < -1.0 || x > 1.0))
        {
        throw std::runtime_error("Argument passed to ASIN must be between -1 and 1.");
        }
    return std::asin(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_atan(te_type x)
    {
    return std::atan(static_cast<te_type>(x));
    }

[[nodiscard]]
static te_type _te_atan2(te_type y, te_type x)
    {
    return std::atan2(static_cast<te_type>(y), (static_cast<te_type>(x)));
    }

[[nodiscard]]
static te_type _te_tgamma(te_type y)
    {
    return std::tgamma(y);
    }

[[nodiscard]]
static te_type _te_random()
    {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<te_type> distr(0, 1);
    return distr(gen);
    }

[[nodiscard]]
constexpr static te_type _te_divide(te_type a, te_type b)
    {
    if (b == 0)
        {
        throw std::runtime_error("Division by zero.");
        }
    return a / b;
    }

[[nodiscard]]
static te_type _te_modulus(te_type a, te_type b)
    {
    if (b == 0)
        {
        throw std::runtime_error("Modulus by zero.");
        }
    return std::fmod(a, b);
    }

[[nodiscard]]
static te_type _te_sum(te_type v1, te_type v2, te_type v3, te_type v4, te_type v5, te_type v6,
                       te_type v7)
    {
    return (std::isnan(v1) ? 0 : v1) + (std::isnan(v2) ? 0 : v2) + (std::isnan(v3) ? 0 : v3) +
           (std::isnan(v4) ? 0 : v4) + (std::isnan(v5) ? 0 : v5) + (std::isnan(v6) ? 0 : v6) +
           (std::isnan(v7) ? 0 : v7);
    }

[[nodiscard]]
static te_type _te_average(te_type v1, te_type v2, te_type v3, te_type v4, te_type v5, te_type v6,
                           te_type v7)
    {
    const auto validN = (std::isnan(v1) ? 0 : 1) + (std::isnan(v2) ? 0 : 1) +
                        (std::isnan(v3) ? 0 : 1) + (std::isnan(v4) ? 0 : 1) +
                        (std::isnan(v5) ? 0 : 1) + (std::isnan(v6) ? 0 : 1) +
                        (std::isnan(v7) ? 0 : 1);
    const auto total = _te_sum(v1, v2, v3, v4, v5, v6, v7);
    return _te_divide(total, static_cast<te_type>(validN));
    }

/// @warning This version of round emulates Excel behavior of supporting
///     negative decimal places (e.g., ROUND(21.5, -1) = 20). Be aware
///     of that if using this function outside of TinyExpr++.
[[nodiscard]]
static te_type _te_round(te_type val, te_type decimal_places)
    {
    const bool useNegativeRound{ decimal_places < 0 };
    const size_t adjustedDecimalPlaces{ std::isnan(decimal_places) ?
                                            0 :
                                            static_cast<size_t>(std::abs(decimal_places)) };

    const te_type decimalPostition = static_cast<te_type>(std::pow(10, adjustedDecimalPlaces));
    if (!std::isfinite(decimalPostition))
        {
        return te_parser::te_nan;
        }
    constexpr te_type roundEpsilon{ 0.5 };

    if (!useNegativeRound)
        {
        if (val < 0)
            {
            return (decimalPostition == 0) ?
                       std::ceil(val - roundEpsilon) :
                       std::ceil(static_cast<te_type>(val * decimalPostition) -
                                 roundEpsilon) /
                           decimalPostition;
            }
        else
            {
            return (decimalPostition == 0) ?
                       std::floor(val + roundEpsilon) :
                       std::floor(static_cast<te_type>(val * decimalPostition) +
                                  roundEpsilon) /
                           decimalPostition;
            }
        }
    else
        {
        // ROUND(21.5, -1) = 20
        if (val < 0)
            {
            return std::ceil(static_cast<te_type>(val / decimalPostition) -
                             roundEpsilon) *
                   decimalPostition;
            }
        else
            {
            return std::floor(static_cast<te_type>(val / decimalPostition) +
                              roundEpsilon) *
                   decimalPostition;
            }
        }
    }

// Combinations (without repetition)
[[nodiscard]]
static te_type _te_ncr(te_type n, te_type r) noexcept
    {
    if (n < 0.0 || r < 0.0 || n < r || std::isnan(n) || std::isnan(r))
        {
        return te_parser::te_nan;
        }
    if (n > ((std::numeric_limits<unsigned int>::max)()) ||
        r > (std::numeric_limits<unsigned int>::max)())
        {
        return std::numeric_limits<te_type>::infinity();
        }
    const unsigned long int un{ static_cast<unsigned int>(n) };
    unsigned long int ur{ static_cast<unsigned int>(r) };
    unsigned long int result{ 1 };
    if (ur > un / 2)
        {
        ur = un - ur;
        }
    for (decltype(ur) i = 1; i <= ur; i++)
        {
        if (result > ((std::numeric_limits<unsigned long>::max)()) / (un - ur + i))
            {
            return std::numeric_limits<te_type>::infinity();
            }
        result *= un - ur + i;
        result /= i;
        }
    return static_cast<te_type>(result);
    }

// Permutations (without repetition)
[[nodiscard]]
static te_type _te_npr(te_type n, te_type r) noexcept
    {
    return _te_ncr(n, r) * _te_fac(r);
    }

[[nodiscard]]
constexpr static te_type _te_add(te_type a, te_type b) noexcept
    {
    return a + b;
    }

[[nodiscard]]
constexpr static te_type _te_sub(te_type a, te_type b) noexcept
    {
    return a - b;
    }

[[nodiscard]]
constexpr static te_type _te_mul(te_type a, te_type b) noexcept
    {
    return a * b;
    }

// Shift operators
//--------------------------------------------------
[[nodiscard]]
static te_type _te_left_shift(te_type a, te_type b)
    {
    if (std::floor(a) != a)
        {
        throw std::runtime_error("Left side of left shift (<<) operation must be an integer.");
        }
    else if (std::floor(b) != b)
        {
        throw std::runtime_error(
            "Additive expression of left shift (<<) operation must be an integer.");
        }
    else if (a < 0)
        {
        throw std::runtime_error("Left side of left shift (<<) operation cannot be negative.");
        }
    // bitness is limited to 64-bit, so ensure shift doesn't go beyond that
    // and cause undefined behavior
    else if (b < 0 || b >= 64)
        {
        throw std::runtime_error(
            "Additive expression of left shift (<<) operation must be between 0-63.");
        }
    const auto multipler = (static_cast<uint64_t>(1) << static_cast<uint64_t>(b));
    const auto maxBaseNumber = (std::numeric_limits<uint64_t>::max() / multipler);
    if (static_cast<uint64_t>(a) > maxBaseNumber)
        {
        throw std::runtime_error(
            "Overflow in left shift (<<) operation; base number is too large.");
        }
    return static_cast<te_type>(static_cast<uint64_t>(a) << static_cast<uint64_t>(b));
    }

//--------------------------------------------------
[[nodiscard]]
static te_type _te_right_shift(te_type a, te_type b)
    {
    if (std::floor(a) != a)
        {
        throw std::runtime_error("Left side of right shift (>>) operation must be an integer.");
        }
    else if (std::floor(b) != b)
        {
        throw std::runtime_error(
            "Additive expression of right shift (>>)operation must be an integer.");
        }
    else if (a < 0)
        {
        throw std::runtime_error("Left side of right shift (<<) operation cannot be negative.");
        }
    else if (b < 0 || b >= 64)
        {
        throw std::runtime_error(
            "Additive expression of right shift (>>) operation must be between 0-63.");
        }
    return static_cast<te_type>(static_cast<uint64_t>(a) >> static_cast<uint64_t>(b));
    }

/// @warning This emulates Excel, where a negative shift amount acts as a right shift.\n
///     Be aware of this if using this function outside of TinyExpr++.
//--------------------------------------------------
[[nodiscard]]
static te_type _te_left_shift_or_right(te_type a, te_type b)
    {
    return (b >= 0) ? _te_left_shift(a, b) : _te_right_shift(a, std::abs(b));
    }

/// @warning This emulates Excel, where a negative shift amount acts as a right shift.\n
///     Be aware of this if using this function outside of TinyExpr++.
//--------------------------------------------------
[[nodiscard]]
static te_type _te_right_shift_or_left(te_type a, te_type b)
    {
    return (b >= 0) ? _te_right_shift(a, b) : _te_left_shift(a, std::abs(b));
    }

[[nodiscard]]
constexpr static te_type _te_sqr(te_type a) noexcept
    {
    return a * a;
    }

[[nodiscard]]
static te_type _te_max_maybe_nan(te_type v1, te_type v2_maybe_nan) noexcept
    {
    return (std::max)(v1, std::isnan(v2_maybe_nan) ? v1 : v2_maybe_nan);
    }

[[nodiscard]]
static te_type _te_max(te_type v1, te_type v2, te_type v3, te_type v4, te_type v5, te_type v6,
                       te_type v7) noexcept
    {
    // assumes that at least v1 is a number, rest can be NaN
    auto maxVal = _te_max_maybe_nan(v1, v2);
    maxVal = _te_max_maybe_nan(maxVal, v3);
    maxVal = _te_max_maybe_nan(maxVal, v4);
    maxVal = _te_max_maybe_nan(maxVal, v5);
    maxVal = _te_max_maybe_nan(maxVal, v6);
    return _te_max_maybe_nan(maxVal, v7);
    }

[[nodiscard]]
static te_type _te_min_maybe_nan(te_type v1, te_type v2_maybe_nan) noexcept
    {
    return (std::min)(v1, std::isnan(v2_maybe_nan) ? v1 : v2_maybe_nan);
    }

[[nodiscard]]
static te_type _te_min(te_type v1, te_type v2, te_type v3, te_type v4, te_type v5, te_type v6,
                       te_type v7) noexcept
    {
    // assumes that at least v1 is legit, rest can be NaN
    auto minVal = _te_min_maybe_nan(v1, v2);
    minVal = _te_min_maybe_nan(minVal, v3);
    minVal = _te_min_maybe_nan(minVal, v4);
    minVal = _te_min_maybe_nan(minVal, v5);
    minVal = _te_min_maybe_nan(minVal, v6);
    return _te_min_maybe_nan(minVal, v7);
    }

[[nodiscard]]
static te_type _te_and_maybe_nan(te_type v1, te_type v2_maybe_nan) noexcept
    {
    return std::isnan(v2_maybe_nan) ? v1 : (v1 && v2_maybe_nan);
    }

[[nodiscard]]
static te_type _te_and_variadic(te_type v1, te_type v2, te_type v3, te_type v4, te_type v5,
                                te_type v6, te_type v7) noexcept
    {
    // assumes that at least v1 is legit, rest can be NaN
    auto andVal = _te_and_maybe_nan(v1, v2);
    andVal = _te_and_maybe_nan(andVal, v3);
    andVal = _te_and_maybe_nan(andVal, v4);
    andVal = _te_and_maybe_nan(andVal, v5);
    andVal = _te_and_maybe_nan(andVal, v6);
    return _te_and_maybe_nan(andVal, v7);
    }

[[nodiscard]]
static te_type _te_or_maybe_nan(te_type v1, te_type v2_maybe_nan) noexcept
    {
    return std::isnan(v2_maybe_nan) ? v1 : (v1 || v2_maybe_nan);
    }

[[nodiscard]]
static te_type _te_or_variadic(te_type v1, te_type v2, te_type v3, te_type v4, te_type v5,
                               te_type v6, te_type v7) noexcept
    {
    // assumes that at least v1 is legit, rest can be NaN
    auto orVal = _te_or_maybe_nan(v1, v2);
    orVal = _te_or_maybe_nan(orVal, v3);
    orVal = _te_or_maybe_nan(orVal, v4);
    orVal = _te_or_maybe_nan(orVal, v5);
    orVal = _te_or_maybe_nan(orVal, v6);
    return _te_or_maybe_nan(orVal, v7);
    }

[[nodiscard]]
constexpr static te_type _te_if(te_type a, te_type b, te_type c) noexcept
    {
    return (a != 0.0) ? b : c;
    }

[[nodiscard]]
constexpr static te_type _te_ifs(te_type if1, te_type if1True, te_type if2, te_type if2True,
                                 te_type if3, te_type if3True) noexcept
    {
    return (!std::isnan(if1) && if1 != 0.0) ? if1True :
           (!std::isnan(if2) && if2 != 0.0) ? if2True :
           (!std::isnan(if3) && if3 != 0.0) ? if3True :
                                              te_parser::te_nan;
    }

[[nodiscard]]
constexpr static te_type _te_false_value() noexcept
    {
    return 0;
    }

[[nodiscard]]
constexpr static te_type _te_true_value() noexcept
    {
    return 1;
    }

[[nodiscard]]
constexpr static te_type _te_nan_value() noexcept
    {
    return te_parser::te_nan;
    }

// cotangent
[[nodiscard]]
static te_type _te_cot(te_type a) noexcept
    {
    if (a == 0.0)
        {
        return te_parser::te_nan;
        }
    return 1 / static_cast<te_type>(std::tan(a));
    }

[[nodiscard]]
constexpr static te_type _te_sign(te_type a) noexcept
    {
    return static_cast<te_type>((a < 0.0) ? -1 : (a > 0.0) ? 1 : 0);
    }

[[nodiscard]]
constexpr static te_type _te_negate(te_type a) noexcept
    {
    return -a;
    }

[[nodiscard]]
constexpr static te_type _comma([[maybe_unused]] te_type a, te_type b) noexcept
    {
    return b;
    }

//--------------------------------------------------
void te_parser::te_free_parameters(te_expr* n)
    {
    if (!n)
        {
        return;
        }
    if (is_closure(n->m_value))
        {
        // last param is the context object, we don't manage that here
        for (auto param = n->m_parameters.begin(); param != n->m_parameters.end() - 1; ++param)
            {
            te_free(*param);
            *param = nullptr;
            }
        }
    else if (is_function(n->m_value))
        {
        for (auto* param : n->m_parameters)
            {
            te_free(param);
            param = nullptr;
            }
        }
    }

//--------------------------------------------------
const std::set<te_variable> te_parser::m_functions = {
    { "abs", static_cast<te_fun1>(_te_absolute_value), TE_PURE },
    { "acos", static_cast<te_fun1>(_te_acos), TE_PURE },
    // variadic, accepts 1-7 arguments
    { "and", static_cast<te_fun7>(_te_and_variadic),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "asin", static_cast<te_fun1>(_te_asin), TE_PURE },
    { "atan", static_cast<te_fun1>(_te_atan), TE_PURE },
    { "atan2", static_cast<te_fun2>(_te_atan2), TE_PURE },
    { "average", static_cast<te_fun7>(_te_average),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "bitlshift", static_cast<te_fun2>(_te_left_shift_or_right), TE_PURE },
    { "bitrshift", static_cast<te_fun2>(_te_right_shift_or_left), TE_PURE },
    { "ceil", static_cast<te_fun1>(_te_ceil), TE_PURE },
    { "clamp",
      static_cast<te_fun3>(
          [](const te_type num, const te_type start, const te_type end)
          {
              return (start <= end) ? std::clamp<te_type>(num, start, end) :
                                      std::clamp<te_type>(num, end, start);
          }),
      TE_PURE },
    { "combin", static_cast<te_fun2>(_te_ncr), TE_PURE },
    { "cos", static_cast<te_fun1>(_te_cos), TE_PURE },
    { "cosh", static_cast<te_fun1>(_te_cosh), TE_PURE },
    { "cot", static_cast<te_fun1>(_te_cot), TE_PURE },
    { "e", static_cast<te_fun0>(_te_e), TE_PURE },
    { "exp", static_cast<te_fun1>(_te_exp), TE_PURE },
    { "fac", static_cast<te_fun1>(_te_fac), TE_PURE },
    { "fact", static_cast<te_fun1>(_te_fac), TE_PURE },
    { "false", static_cast<te_fun0>(_te_false_value), TE_PURE },
    { "floor", static_cast<te_fun1>(_te_floor), TE_PURE },
    { "if", static_cast<te_fun3>(_te_if), TE_PURE },
    { "ifs", static_cast<te_fun6>(_te_ifs), static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "ln", static_cast<te_fun1>(_te_log), TE_PURE },
    { "log10", static_cast<te_fun1>(_te_log10), TE_PURE },
    { "max", static_cast<te_fun7>(_te_max), static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "min", static_cast<te_fun7>(_te_min), static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "mod", static_cast<te_fun2>(_te_modulus), TE_PURE },
    { "nan", static_cast<te_fun0>(_te_nan_value), TE_PURE },
    { "ncr", static_cast<te_fun2>(_te_ncr), TE_PURE },
    { "not", static_cast<te_fun1>(_te_not), TE_PURE },
    { "npr", static_cast<te_fun2>(_te_npr), TE_PURE },
    { "or", static_cast<te_fun7>(_te_or_variadic),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "permut", static_cast<te_fun2>(_te_npr), TE_PURE },
    { "pi", static_cast<te_fun0>(_te_pi), TE_PURE },
    { "pow", static_cast<te_fun2>(_te_pow), TE_PURE },
    { "power", /* Excel alias*/ static_cast<te_fun2>(_te_pow), TE_PURE },
    { "rand", static_cast<te_fun0>(_te_random), TE_PURE },
    { "round", static_cast<te_fun2>(_te_round),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "sign", static_cast<te_fun1>(_te_sign), TE_PURE },
    { "sin", static_cast<te_fun1>(_te_sin), TE_PURE },
    { "sinh", static_cast<te_fun1>(_te_sinh), TE_PURE },
    { "sqr", static_cast<te_fun1>(_te_sqr), TE_PURE },
    { "sqrt", static_cast<te_fun1>(_te_sqrt), TE_PURE },
    { "sum", static_cast<te_fun7>(_te_sum), static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "tan", static_cast<te_fun1>(_te_tan), TE_PURE },
    { "tanh", static_cast<te_fun1>(_te_tanh), TE_PURE },
    { "tgamma", static_cast<te_fun1>(_te_tgamma), TE_PURE },
    { "true", static_cast<te_fun0>(_te_true_value), TE_PURE },
    { "trunc", static_cast<te_fun1>(_te_trunc), TE_PURE }
};

//--------------------------------------------------
void te_parser::next_token(te_parser::state* s)
    {
    assert(s);
    if (!s)
        {
        return;
        }

    s->m_type = te_parser::state::token_type::TOK_NULL;

    do
        {
        if (!*s->m_next)
            {
            s->m_type = te_parser::state::token_type::TOK_END;
            return;
            }

        /* Try reading a number. */
        if ((s->m_next[0] >= '0' && s->m_next[0] <= '9') || s->m_next[0] == get_decimal_separator())
            {
            char* nEnd{ nullptr };
            s->m_value = static_cast<te_type>(std::strtod(s->m_next, &nEnd));
            s->m_next = nEnd;
            s->m_type = te_parser::state::token_type::TOK_NUMBER;
            }
        else
            {
            /* Look for a variable or builtin function call. */
            if (is_letter(s->m_next[0]) || s->m_next[0] == '_')
                {
                const char* start = s->m_next;
                while (is_name_char_valid(s->m_next[0]))
                    {
                    s->m_next++;
                    }

                m_varFound = false;
                const std::string_view currentVarToken{ start, static_cast<std::string::size_type>(
                                                                   s->m_next - start) };
                m_currentVar = find_lookup(s, currentVarToken);
                if (m_currentVar != s->m_lookup.cend())
                    {
                    m_varFound = true;
                    }
                else
                    {
                    m_currentVar = find_builtin(currentVarToken);
                    if (m_currentVar != m_functions.cend())
                        {
                        m_varFound = true;
                        }
                    // if unknown symbol resolve is not a no-op, then try using it
                    // to see what this variable is
                    else if (m_unknownSymbolResolve.index() != 0)
                        {
                        try
                            {
                            // "te_type usr(string_view)" resolver
                            if (m_unknownSymbolResolve.index() == 1)
                                {
                                const auto retUsrVal =
                                    std::get<1>(m_unknownSymbolResolve)(currentVarToken);
                                if (!std::isnan(retUsrVal))
                                    {
                                    add_variable_or_function(
                                        { te_variable::name_type{ currentVarToken }, retUsrVal });
                                    m_currentVar = find_lookup(s, currentVarToken);
                                    assert(
                                        m_currentVar != s->m_lookup.cend() &&
                                        "Internal error in parser using unknown symbol resolver.");
                                    if (m_currentVar != s->m_lookup.cend())
                                        {
                                        m_resolvedVariables.insert(
                                            te_variable::name_type{ currentVarToken });
                                        m_varFound = true;
                                        }
                                    }
                                }
                            // "te_type usr(string_view, string&)" resolver
                            else if (m_unknownSymbolResolve.index() == 2)
                                {
                                const auto retUsrVal = std::get<2>(m_unknownSymbolResolve)(
                                    currentVarToken, m_lastErrorMessage);
                                if (!std::isnan(retUsrVal))
                                    {
                                    add_variable_or_function(
                                        { te_variable::name_type{ currentVarToken }, retUsrVal });
                                    m_currentVar = find_lookup(s, currentVarToken);
                                    assert(
                                        m_currentVar != s->m_lookup.cend() &&
                                        "Internal error in parser using unknown symbol resolver.");
                                    if (m_currentVar != s->m_lookup.cend())
                                        {
                                        m_resolvedVariables.insert(
                                            te_variable::name_type{ currentVarToken });
                                        m_varFound = true;
                                        }
                                    }
                                }
                            }
                        catch (const std::exception& exp)
                            {
                            m_lastErrorMessage = exp.what();
                            }
                        }
                    }

                if (!m_varFound)
                    {
                    s->m_type = te_parser::state::token_type::TOK_ERROR;
                    }
                else
                    {
#ifndef TE_NO_BOOKKEEPING
                    // keep track of what's been used in the formula
                    if (is_function(m_currentVar->m_value) || is_closure(m_currentVar->m_value))
                        {
                        m_usedFunctions.insert(m_currentVar->m_name);
                        }
                    else
                        {
                        m_usedVars.insert(m_currentVar->m_name);
                        }
#endif

                    if (is_constant(m_currentVar->m_value))
                        {
                        s->m_type = te_parser::state::token_type::TOK_NUMBER;
                        s->m_value = m_currentVar->m_value;
                        }
                    else if (is_variable(m_currentVar->m_value))
                        {
                        s->m_type = te_parser::state::token_type::TOK_VARIABLE;
                        s->m_value = m_currentVar->m_value;
                        }
                    else if (is_function(m_currentVar->m_value))
                        {
                        s->m_type = te_parser::state::token_type::TOK_FUNCTION;
                        s->m_varType = m_currentVar->m_type;
                        s->m_value = m_currentVar->m_value;
                        }
                    else if (is_closure(m_currentVar->m_value))
                        {
                        s->context = m_currentVar->m_context;
                        s->m_type = te_parser::state::token_type::TOK_FUNCTION;
                        s->m_varType = m_currentVar->m_type;
                        s->m_value = m_currentVar->m_value;
                        }
                    }
                }
            else
                {
                /* Look for an operator or special character. */
                const auto tok = s->m_next++[0];
                if (tok == '+')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = _te_add;
                    }
                else if (tok == '-')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = _te_sub;
                    }
                else if (tok == '*' && s->m_next[0] == '*')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_pow);
                    ++s->m_next;
                    }
                else if (tok == '*')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = _te_mul;
                    }
                else if (tok == '/')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = _te_divide;
                    }
                else if (tok == '^')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_pow);
                    }
                else if (tok == '%')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = _te_modulus;
                    }
                else if (tok == '(')
                    {
                    s->m_type = te_parser::state::token_type::TOK_OPEN;
                    }
                else if (tok == ')')
                    {
                    s->m_type = te_parser::state::token_type::TOK_CLOSE;
                    }
                else if (tok == get_list_separator())
                    {
                    s->m_type = te_parser::state::token_type::TOK_SEP;
                    }
                // shift operators
                else if (tok == '<' && s->m_next[0] == '<')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_left_shift);
                    ++s->m_next;
                    }
                else if (tok == '>' && s->m_next[0] == '>')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_right_shift);
                    ++s->m_next;
                    }
                // logical operators
                else if (tok == '=' && s->m_next[0] == '=')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_equal);
                    ++s->m_next;
                    }
                else if (tok == '=')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_equal);
                    }
                else if (tok == '!' && s->m_next[0] == '=')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_not_equal);
                    ++s->m_next;
                    }
                else if (tok == '<' && s->m_next[0] == '>')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_not_equal);
                    ++s->m_next;
                    }
                else if (tok == '<' && s->m_next[0] == '=')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_less_than_equal_to);
                    ++s->m_next;
                    }
                else if (tok == '<')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_less_than);
                    }
                else if (tok == '>' && s->m_next[0] == '=')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_greater_than_equal_to);
                    ++s->m_next;
                    }
                else if (tok == '>')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_greater_than);
                    }
                else if (tok == '&')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_and);
                    }
                else if (tok == '|')
                    {
                    s->m_type = te_parser::state::token_type::TOK_INFIX;
                    s->m_value = static_cast<te_fun2>(_te_or);
                    }
                else if (tok == ' ' || tok == '\t' || tok == '\n' || tok == '\r')
                    { /*noop*/
                    }
                else
                    {
                    s->m_type = te_parser::state::token_type::TOK_ERROR;
                    }
                }
            }
        } while (s->m_type == te_parser::state::token_type::TOK_NULL);
    }

//--------------------------------------------------
te_expr* te_parser::base(te_parser::state* s)
    {
    /* <base>      =    <constant> | <variable> | <function-0> {"(" ")"} | <function-1> <power> |
                        <function-X> "(" <expr> {"," <expr>} ")" | "(" <list> ")" */
    te_expr* ret{ nullptr };

    if (s->m_type == te_parser::state::token_type::TOK_OPEN)
        {
        next_token(s);
        ret = list(s);
        if (s->m_type != te_parser::state::token_type::TOK_CLOSE)
            {
            s->m_type = te_parser::state::token_type::TOK_ERROR;
            }
        else
            {
            next_token(s);
            }
        }
    else if (s->m_type == te_parser::state::token_type::TOK_NUMBER)
        {
        ret = new_expr(TE_DEFAULT, s->m_value);
        next_token(s);
        }
    else if (s->m_type == te_parser::state::token_type::TOK_VARIABLE)
        {
        ret = new_expr(TE_DEFAULT, s->m_value);
        next_token(s);
        }
    else if (s->m_type == te_parser::state::token_type::TOK_NULL ||
             s->m_type == te_parser::state::token_type::TOK_ERROR ||
             s->m_type == te_parser::state::token_type::TOK_END ||
             s->m_type == te_parser::state::token_type::TOK_SEP ||
             s->m_type == te_parser::state::token_type::TOK_CLOSE ||
             s->m_type == te_parser::state::token_type::TOK_INFIX)
        {
        ret = new_expr(TE_DEFAULT, te_variant_type{ te_nan });
        s->m_type = te_parser::state::token_type::TOK_ERROR;
        }
    else if (is_function0(s->m_value) || is_closure0(s->m_value))
        {
        ret = new_expr(s->m_varType, s->m_value, {});
        if (is_closure(s->m_value))
            {
            ret->m_parameters[0] = s->context;
            }
        next_token(s);
        if (s->m_type == te_parser::state::token_type::TOK_OPEN)
            {
            next_token(s);
            if (s->m_type != te_parser::state::token_type::TOK_CLOSE)
                {
                s->m_type = te_parser::state::token_type::TOK_ERROR;
                }
            else
                {
                next_token(s);
                }
            }
        }
    else if (is_function1(s->m_value) || is_closure1(s->m_value))
        {
        ret = new_expr(s->m_varType, s->m_value);
        if (is_closure(s->m_value))
            {
            ret->m_parameters[1] = s->context;
            }
        next_token(s);
        ret->m_parameters[0] = power(s);
        }
    else if (is_function2(s->m_value) || is_closure2(s->m_value) || is_function3(s->m_value) ||
             is_closure3(s->m_value) || is_function4(s->m_value) || is_closure4(s->m_value) ||
             is_function5(s->m_value) || is_closure5(s->m_value) || is_function6(s->m_value) ||
             is_closure6(s->m_value) || is_function7(s->m_value) || is_closure7(s->m_value))
        {
        const int arity = get_arity(s->m_value);

        ret = new_expr(s->m_varType, s->m_value);
        if (is_closure(s->m_value))
            {
            ret->m_parameters[arity] = s->context;
            }
        next_token(s);

        if (s->m_type != te_parser::state::token_type::TOK_OPEN)
            {
            s->m_type = te_parser::state::token_type::TOK_ERROR;
            }
        else
            {
            int i{ 0 };
            // If there are vars or other functions in the parameters, keep track of the original
            // opening function; that is what we will do our variadic check on.
            const bool varValid{ m_varFound };
            const auto openingVar = m_currentVar;
            // load any parameters
            for (i = 0; i < arity; i++)
                {
                next_token(s);
                ret->m_parameters[i] = expr(s);
                if (s->m_type != te_parser::state::token_type::TOK_SEP)
                    {
                    break;
                    }
                }
            if (s->m_type == te_parser::state::token_type::TOK_CLOSE && i != arity - 1 &&
                varValid && is_variadic(openingVar->m_type))
                {
                next_token(s);
                }
            else if (s->m_type != te_parser::state::token_type::TOK_CLOSE || i != arity - 1)
                {
                s->m_type = te_parser::state::token_type::TOK_ERROR;
                }
            else
                {
                next_token(s);
                }
            }
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::list(te_parser::state* s)
    {
    /* <list>      =    <expr> {"," <expr>} */
    te_expr* ret = expr(s);

    while (s->m_type == te_parser::state::token_type::TOK_SEP)
        {
        next_token(s);
        ret = new_expr(TE_PURE, te_variant_type(_comma), { ret, expr(s) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr(te_parser::state* s)
    {
    /* <expr>      =    <term> {(logic operations) <term>} */
    // These are the lowest of operator precedence
    // (once we have split tokens into arguments)
    te_expr* ret = expr_level2(s);

    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == _te_and || get_function2(s->m_value) == _te_or))
        {
        const te_fun2 t = get_function2(s->m_value);
        next_token(s);
        ret = new_expr(TE_PURE, t, { ret, expr_level2(s) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr_level2(te_parser::state* s)
    {
    /* <expr>      =    <term> {(comparison operators) <term>} */
    // Second from the lowest of operator precedence
    te_expr* ret = expr_level3(s);

    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == _te_equal || get_function2(s->m_value) == _te_not_equal ||
            get_function2(s->m_value) == _te_less_than ||
            get_function2(s->m_value) == _te_less_than_equal_to ||
            get_function2(s->m_value) == _te_greater_than ||
            get_function2(s->m_value) == _te_greater_than_equal_to))
        {
        const te_fun2 t = get_function2(s->m_value);
        next_token(s);
        ret = new_expr(TE_PURE, t, { ret, expr_level3(s) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr_level3(te_parser::state* s)
    {
    /* <expr>      =    <term> {("<<" | ">>") <term>} */
    // Third from the lowest level of operator precendence
    te_expr* ret = expr_level4(s);

    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == _te_left_shift ||
            get_function2(s->m_value) == _te_right_shift))
        {
        const te_fun2 t = get_function2(s->m_value);
        next_token(s);
        ret = new_expr(TE_PURE, t, { ret, expr_level4(s) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr_level4(te_parser::state* s)
    {
    /* <expr>      =    <term> {("+" | "-") <term>} */
    // Fourth from the lowest level of operator precendence
    te_expr* ret = term(s);

    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == _te_add || get_function2(s->m_value) == _te_sub))
        {
        const te_fun2 t = get_function2(s->m_value);
        next_token(s);
        ret = new_expr(TE_PURE, t, { ret, term(s) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::term(te_parser::state* s)
    {
    /* <term>      =    <factor> {("*" | "/" | "%") <factor>} */
    te_expr* ret = factor(s);
    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == _te_mul || get_function2(s->m_value) == _te_divide ||
            get_function2(s->m_value) == _te_modulus))
        {
        const te_fun2 t = get_function2(s->m_value);
        next_token(s);
        ret = new_expr(TE_PURE, t, { ret, factor(s) });
        }

    return ret;
    }

#ifdef TE_POW_FROM_RIGHT
te_expr* te_parser::factor(te_parser::state* s)
    {
    /* <factor>    =    <power> {"^" <power>} */
    te_expr* ret = power(s);

    int neg{ 0 };

    if (ret->m_type == TE_PURE && is_function1(ret->m_value) &&
        get_function1(ret->m_value) == _te_negate)
        {
        te_expr* se = ret->m_parameters[0];
        delete ret;
        ret = se;
        neg = 1;
        }

    te_expr* insertion{ nullptr };
    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == static_cast<te_fun2>(_te_pow)))
        {
        const te_fun2 t = get_function2(s->m_value);
        next_token(s);

        if (insertion)
            {
            /* Make exponentiation go right-to-left. */
            te_expr* insert = new_expr(TE_PURE, t, { insertion->m_parameters[1], power(s) });
            insertion->m_parameters[1] = insert;
            insertion = insert;
            }
        else
            {
            ret = new_expr(TE_PURE, t, { ret, power(s) });
            insertion = ret;
            }
        }

    if (neg)
        {
        ret = new_expr(TE_PURE, te_variant_type(_te_negate), { ret });
        }

    return ret;
    }
#else
te_expr* te_parser::factor(te_parser::state* s)
    {
    /* <factor>    =    <power> {"^" <power>} */
    te_expr* ret = power(s);
    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == static_cast<te_fun2>(_te_pow)))
        {
        const te_fun2 t = get_function2(s->m_value);
        next_token(s);
        ret = new_expr(TE_PURE, t, { ret, power(s) });
        }

    return ret;
    }
#endif

//--------------------------------------------------
te_expr* te_parser::power(te_parser::state* s)
    {
    /* <power>     =    {("-" | "+")} <base> */
    int Sign{ 1 };
    while (s->m_type == te_parser::state::token_type::TOK_INFIX && is_function2(s->m_value) &&
           (get_function2(s->m_value) == _te_add || get_function2(s->m_value) == _te_sub))
        {
        if (get_function2(s->m_value) == _te_sub)
            {
            Sign = -Sign;
            }
        next_token(s);
        }

    te_expr* ret{ nullptr };

    if (Sign == 1)
        {
        ret = base(s);
        }
    else
        {
        ret = new_expr(TE_PURE, te_variant_type(_te_negate), { base(s) });
        }

    return ret;
    }

//--------------------------------------------------
te_type te_parser::te_eval(const te_expr* n)
    {
    if (!n)
        {
        return te_nan;
        }

    // cppcheck-suppress unreadVariable
    const auto M = [&n = std::as_const(n)](const size_t e)
    { return (e < n->m_parameters.size()) ? te_eval(n->m_parameters[e]) : te_nan; };

    switch (n->m_value.index())
        {
    case 0:
        return get_constant(n->m_value);
    case 1:
        return *(get_variable(n->m_value));
    case 2:
        return get_function0(n->m_value)();
    case 3:
        return get_function1(n->m_value)(M(0));
    case 4:
        return get_function2(n->m_value)(M(0), M(1));
    case 5:
        return get_function3(n->m_value)(M(0), M(1), M(2));
    case 6:
        return get_function4(n->m_value)(M(0), M(1), M(2), M(3));
    case 7:
        return get_function5(n->m_value)(M(0), M(1), M(2), M(3), M(4));
    case 8:
        return get_function6(n->m_value)(M(0), M(1), M(2), M(3), M(4), M(5));
    case 9:
        return get_function7(n->m_value)(M(0), M(1), M(2), M(3), M(4), M(5), M(6));
    case 10:
        return get_closure0(n->m_value)(n->m_parameters[0]);
    case 11:
        return get_closure1(n->m_value)(n->m_parameters[1], M(0));
    case 12:
        return get_closure2(n->m_value)(n->m_parameters[2], M(0), M(1));
    case 13:
        return get_closure3(n->m_value)(n->m_parameters[3], M(0), M(1), M(2));
    case 14:
        return get_closure4(n->m_value)(n->m_parameters[4], M(0), M(1), M(2), M(3));
    case 15:
        return get_closure5(n->m_value)(n->m_parameters[5], M(0), M(1), M(2), M(3), M(4));
    case 16:
        return get_closure6(n->m_value)(n->m_parameters[6], M(0), M(1), M(2), M(3), M(4), M(5));
    case 17:
        return get_closure7(n->m_value)(n->m_parameters[7], M(0), M(1), M(2), M(3), M(4), M(5),
                                        M(6));
    default:
        return te_nan;
        };
    }

//--------------------------------------------------
void te_parser::optimize(te_expr* n)
    {
    if (!n)
        {
        return;
        }
    /* Evaluates as much as possible. */
    if (is_constant(n->m_value) || is_variable(n->m_value))
        {
        return;
        }

    /* Only optimize out functions flagged as pure. */
    if (is_pure(n->m_type))
        {
        const int arity = get_arity(n->m_value);
        bool known{ true };
        for (int i = 0; i < arity; ++i)
            {
            if (!n->m_parameters[i])
                {
                break;
                }
            optimize(n->m_parameters[i]);
            if (!is_constant(n->m_parameters[i]->m_value))
                {
                known = false;
                }
            }
        if (known)
            {
            const auto value = te_eval(n);
            te_free_parameters(n);
            n->m_type = TE_DEFAULT;
            n->m_value = value;
            }
        }
    }

//--------------------------------------------------
te_expr* te_parser::te_compile(const std::string_view expression, std::set<te_variable>& variables)
    {
    state s(expression.data(), TE_DEFAULT, variables);

    next_token(&s);
    te_expr* root = list(&s);

    if (s.m_type != te_parser::state::token_type::TOK_END)
        {
        te_free(root);
        m_errorPos = (s.m_next - s.m_start);
        if (m_errorPos > 0)
            {
            --m_errorPos;
            }
        return nullptr;
        }
    else
        {
        optimize(root);
        m_errorPos = te_parser::npos;
        return root;
        }
    }

//--------------------------------------------------
bool te_parser::compile(const std::string_view expression)
    {
    // reset everything from previous call
    m_errorPos = te_parser::npos;
    m_lastErrorMessage.clear();
    m_result = te_nan;
    m_parseSuccess = false;
    te_free(m_compiledExpression);
    m_compiledExpression = nullptr;
    m_currentVar = m_functions.cend();
    m_varFound = false;
#ifndef TE_NO_BOOKKEEPING
    m_usedFunctions.clear();
    m_usedVars.clear();
#endif
    m_resolvedVariables.clear();
    if (get_list_separator() == get_decimal_separator())
        {
        throw std::runtime_error("List and decimal separators cannot be the same");
        }
    if (expression.empty())
        {
        m_expression.clear();
        m_errorPos = 0;
        return false;
        }
    m_expression.assign(expression);

    // In case the expression was a spreadsheet formula like "=SUM(...)",
    // remove the '=' in front.
    if (m_expression.length() && m_expression.front() == '=')
        {
        m_expression.erase(0, 1);
        }

    size_t commentStart{ 0 };
    while (commentStart != std::string::npos)
        {
        commentStart = m_expression.find('/', commentStart);
        if (commentStart == std::string::npos || commentStart == m_expression.length() - 1)
            {
            break;
            }
        // remove multi-line comments
        if (m_expression[commentStart + 1] == '*')
            {
            auto commentEnd = m_expression.find("*/", commentStart);
            if (commentEnd == std::string::npos)
                {
                m_errorPos = commentStart;
                m_parseSuccess = false;
                m_result = te_nan;
                return false;
                }
            m_expression.erase(commentStart, (commentEnd + 2) - commentStart);
            }
        // remove single-line comments
        else if (m_expression[commentStart + 1] == '/')
            {
            auto commentEnd = m_expression.find_first_of("\n\r", commentStart);
            if (commentEnd == std::string::npos)
                {
                m_expression.erase(commentStart);
                break;
                }
            else
                {
                m_expression.erase(commentStart, commentEnd - commentStart);
                }
            }
        else
            {
            ++commentStart;
            }
        }

    try
        {
        m_compiledExpression = te_compile(m_expression, get_variables_and_functions());
        m_parseSuccess = (m_compiledExpression != nullptr);
        }
    catch (const std::exception& expt)
        {
        m_parseSuccess = false;
        m_result = te_nan;
        m_lastErrorMessage = expt.what();
        }

    reset_usr_resolved_if_necessary();

    return m_parseSuccess;
    }

//--------------------------------------------------
te_type te_parser::evaluate()
    {
    try
        {
        m_result = (m_compiledExpression) ? te_eval(m_compiledExpression) : te_nan;
        }
    catch (const std::exception& expt)
        {
        m_parseSuccess = false;
        m_result = te_nan;
        m_lastErrorMessage = expt.what();
        }

    reset_usr_resolved_if_necessary();

    return m_result;
    }

//--------------------------------------------------
te_type te_parser::evaluate(const std::string_view expression)
    {
    if (compile(expression))
        {
        return evaluate();
        }
    else
        {
        return te_nan;
        }
    }

//--------------------------------------------------
// cppcheck-suppress unusedFunction
std::string te_parser::list_available_functions_and_variables()
    {
    std::string report = "Built-in Functions:\n";
    for (const auto& func : m_functions)
        {
        report.append(func.m_name).append("\n");
        }
    report.append("\nCustom Functions & Variables:\n");
    for (const auto& func : get_variables_and_functions())
        {
        report.append(func.m_name).append("\n");
        }
    return report;
    }
