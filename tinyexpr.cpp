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
namespace te_builtins
    {
    [[nodiscard]]
    constexpr static te_type _te_equal(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 == val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_not_equal(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 != val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_less_than(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 < val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_less_than_equal_to(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 <= val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_greater_than(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 > val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_greater_than_equal_to(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 >= val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_and(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 && val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_or(te_type val1, te_type val2) noexcept
        {
        return static_cast<te_type>((val1 || val2) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_not(te_type val1) noexcept
        {
        return !val1;
        }

    [[nodiscard]]
    constexpr static te_type _te_pi() noexcept
        {
        return static_cast<te_type>(3.14159265358979323846); // NOLINT
        }

    [[nodiscard]]
    constexpr static te_type _te_e() noexcept
        {
        return static_cast<te_type>(2.71828182845904523536); // NOLINT
        }

    [[nodiscard]]
    static te_type _te_fac(te_type val) noexcept
        { /* simplest version of factorial */
        if (val < 0.0 || std::isnan(val))
            {
            return te_parser::te_nan;
            }
        if (val > (std::numeric_limits<unsigned int>::max)())
            {
            return std::numeric_limits<te_type>::infinity();
            }
        const auto usignVal = static_cast<size_t>(val);
        uint32_t result{ 1 };
        for (uint32_t i = 1; i <= usignVal; i++)
            {
            if (i > (std::numeric_limits<uint32_t>::max)() / result)
                {
                return std::numeric_limits<te_type>::infinity();
                }
            result *= i;
            }
        return static_cast<te_type>(result);
        }

    [[nodiscard]]
    static te_type _te_absolute_value(te_type val)
        {
        return std::fabs(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_log(te_type val)
        {
        return std::log(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_log10(te_type val)
        {
        return std::log10(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_pow(te_type val1, te_type val2)
        {
        return std::pow(static_cast<te_type>(val1), static_cast<te_type>(val2));
        }

    [[nodiscard]]
    static te_type _te_tan(te_type val)
        {
        return std::tan(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_tanh(te_type val)
        {
        return std::tanh(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_trunc(te_type val)
        {
        return std::trunc(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_sin(te_type val)
        {
        return std::sin(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_sinh(te_type val)
        {
        return std::sinh(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_sqrt(te_type val)
        {
        if (val < 0)
            {
            throw std::runtime_error("Negative value passed to SQRT.");
            }
        return std::sqrt(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_floor(te_type val)
        {
        return std::floor(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_ceil(te_type val)
        {
        return std::ceil(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_exp(te_type val)
        {
        return std::exp(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_cos(te_type val)
        {
        return std::cos(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_cosh(te_type val)
        {
        return std::cosh(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_acos(te_type val)
        {
        return std::acos(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_asin(te_type val)
        {
        if (std::isfinite(val) && (val < -1.0 || val > 1.0))
            {
            throw std::runtime_error("Argument passed to ASIN must be between -1 and 1.");
            }
        return std::asin(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_atan(te_type val)
        {
        return std::atan(static_cast<te_type>(val));
        }

    [[nodiscard]]
    static te_type _te_atan2(te_type val1, te_type val2)
        {
        return std::atan2(static_cast<te_type>(val1), (static_cast<te_type>(val2)));
        }

    [[nodiscard]]
    static te_type _te_tgamma(te_type val)
        {
        return std::tgamma(val);
        }

    [[nodiscard]]
    static te_type _te_random()
        {
        std::random_device rdev;
        std::mt19937 gen(rdev());
        std::uniform_real_distribution<te_type> distr(0, 1);
        return distr(gen);
        }

    [[nodiscard]]
    constexpr static te_type _te_divide(te_type val1, te_type val2)
        {
        if (val2 == 0)
            {
            throw std::runtime_error("Division by zero.");
            }
        return val1 / val2;
        }

    [[nodiscard]]
    static te_type _te_modulus(te_type val1, te_type val2)
        {
        if (val2 == 0)
            {
            throw std::runtime_error("Modulus by zero.");
            }
        return std::fmod(val1, val2);
        }

    [[nodiscard]]
    static te_type _te_sum(te_type val1, te_type val2, te_type val3, te_type val4, te_type val5,
                           te_type val6, te_type val7)
        {
        return (std::isnan(val1) ? 0 : val1) + (std::isnan(val2) ? 0 : val2) +
               (std::isnan(val3) ? 0 : val3) + (std::isnan(val4) ? 0 : val4) +
               (std::isnan(val5) ? 0 : val5) + (std::isnan(val6) ? 0 : val6) +
               (std::isnan(val7) ? 0 : val7);
        }

    [[nodiscard]]
    static te_type _te_average(te_type val1, te_type val2, te_type val3, te_type val4, te_type val5,
                               te_type val6, te_type val7)
        {
        const auto validN = (std::isnan(val1) ? 0 : 1) + (std::isnan(val2) ? 0 : 1) +
                            (std::isnan(val3) ? 0 : 1) + (std::isnan(val4) ? 0 : 1) +
                            (std::isnan(val5) ? 0 : 1) + (std::isnan(val6) ? 0 : 1) +
                            (std::isnan(val7) ? 0 : 1);
        const auto total = _te_sum(val1, val2, val3, val4, val5, val6, val7);
        return _te_divide(total, static_cast<te_type>(validN));
        }

    /// @warning This version of round emulates Excel behavior of supporting
    ///     negative decimal places (e.g., ROUND(21.5, -1) = 20). Be aware
    ///     of that if using this function outside of TinyExpr++.
    [[nodiscard]]
    static te_type _te_round(te_type val, te_type decimalPlaces) // NOLINT
        {
        const bool useNegativeRound{ decimalPlaces < 0 };
        const size_t adjustedDecimalPlaces{ std::isnan(decimalPlaces) ?
                                                0 :
                                                static_cast<size_t>(std::abs(decimalPlaces)) };

        const auto decimalPostition = static_cast<te_type>(std::pow(10, adjustedDecimalPlaces));
        if (!std::isfinite(decimalPostition))
            {
            return te_parser::te_nan;
            }
        constexpr te_type ROUND_EPSILON{ 0.5 }; // NOLINT

        if (!useNegativeRound)
            {
            if (val < 0)
                {
                return (decimalPostition == 0) ?
                           std::ceil(val - ROUND_EPSILON) :
                           std::ceil(static_cast<te_type>(val * decimalPostition) - ROUND_EPSILON) /
                               decimalPostition;
                }
            return (decimalPostition == 0) ?
                        std::floor(val + ROUND_EPSILON) :
                        std::floor(static_cast<te_type>(val * decimalPostition) +
                                    ROUND_EPSILON) /
                            decimalPostition;
            }
        // ROUND(21.5, -1) = 20
        if (val < 0)
            {
            return std::ceil(static_cast<te_type>(val / decimalPostition) - ROUND_EPSILON) *
                    decimalPostition;
            }
        return std::floor(static_cast<te_type>(val / decimalPostition) + ROUND_EPSILON) *
                decimalPostition;
        }

    // Combinations (without repetition)
    [[nodiscard]]
    static te_type _te_ncr(te_type val1, te_type val2) noexcept
        {
        if (val1 < 0.0 || val2 < 0.0 || val1 < val2 || std::isnan(val1) || std::isnan(val2))
            {
            return te_parser::te_nan;
            }
        if (val1 > ((std::numeric_limits<unsigned int>::max)()) ||
            val2 > (std::numeric_limits<unsigned int>::max)())
            {
            return std::numeric_limits<te_type>::infinity();
            }
        const uint32_t usignN{ static_cast<unsigned int>(val1) };
        uint32_t usignR{ static_cast<unsigned int>(val2) };
        uint32_t result{ 1 };
        if (usignR > usignN / 2)
            {
            usignR = usignN - usignR;
            }
        for (decltype(usignR) i = 1; i <= usignR; i++)
            {
            if (result > ((std::numeric_limits<uint32_t>::max)()) / (usignN - usignR + i))
                {
                return std::numeric_limits<te_type>::infinity();
                }
            result *= usignN - usignR + i;
            result /= i;
            }
        return static_cast<te_type>(result);
        }

    // Permutations (without repetition)
    [[nodiscard]]
    static te_type _te_npr(te_type val1, te_type val2) noexcept
        {
        return _te_ncr(val1, val2) * _te_fac(val2);
        }

    [[nodiscard]]
    constexpr static te_type _te_add(te_type val1, te_type val2) noexcept
        {
        return val1 + val2;
        }

    [[nodiscard]]
    constexpr static te_type _te_sub(te_type val1, te_type val2) noexcept
        {
        return val1 - val2;
        }

    [[nodiscard]]
    constexpr static te_type _te_mul(te_type val1, te_type val2) noexcept
        {
        return val1 * val2;
        }

    // Shift operators
    //--------------------------------------------------
    [[nodiscard]]
    static te_type _te_left_shift(te_type val1, te_type val2)
        {
        constexpr int BITNESS_64BIT{ 64 }; // NOLINT

        if (std::floor(val1) != val1)
            {
            throw std::runtime_error("Left side of left shift (<<) operation must be an integer.");
            }
        if (std::floor(val2) != val2)
            {
            throw std::runtime_error(
                "Additive expression of left shift (<<) operation must be an integer.");
            }
        if (val1 < 0)
            {
            throw std::runtime_error("Left side of left shift (<<) operation cannot be negative.");
            }
        // bitness is limited to 64-bit, so ensure shift doesn't go beyond that
        // and cause undefined behavior
        if (val2 < 0 || val2 >= BITNESS_64BIT)
            {
            throw std::runtime_error(
                "Additive expression of left shift (<<) operation must be between 0-63.");
            }

        const auto multipler = (static_cast<uint64_t>(1) << static_cast<uint64_t>(val2));
        const auto maxBaseNumber = (std::numeric_limits<uint64_t>::max() / multipler);
        if (static_cast<uint64_t>(val1) > maxBaseNumber)
            {
            throw std::runtime_error(
                "Overflow in left shift (<<) operation; base number is too large.");
            }
        return static_cast<te_type>(static_cast<uint64_t>(val1) << static_cast<uint64_t>(val2));
        }

    //--------------------------------------------------
    [[nodiscard]]
    static te_type _te_right_shift(te_type val1, te_type val2)
        {
        constexpr int BITNESS_64BIT{ 64 }; // NOLINT

        if (std::floor(val1) != val1)
            {
            throw std::runtime_error("Left side of right shift (>>) operation must be an integer.");
            }
        if (std::floor(val2) != val2)
            {
            throw std::runtime_error(
                "Additive expression of right shift (>>)operation must be an integer.");
            }
        if (val1 < 0)
            {
            throw std::runtime_error("Left side of right shift (<<) operation cannot be negative.");
            }
        if (val2 < 0 || val2 >= BITNESS_64BIT)
            {
            throw std::runtime_error(
                "Additive expression of right shift (>>) operation must be between 0-63.");
            }

        return static_cast<te_type>(static_cast<uint64_t>(val1) >> static_cast<uint64_t>(val2));
        }

    /// @warning This emulates Excel, where a negative shift amount acts as a right shift.\n
    ///     Be aware of this if using this function outside of TinyExpr++.
    //--------------------------------------------------
    [[nodiscard]]
    static te_type _te_left_shift_or_right(te_type val1, te_type val2)
        {
        return (val2 >= 0) ? _te_left_shift(val1, val2) : _te_right_shift(val1, std::abs(val2));
        }

    /// @warning This emulates Excel, where a negative shift amount acts as a right shift.\n
    ///     Be aware of this if using this function outside of TinyExpr++.
    //--------------------------------------------------
    [[nodiscard]]
    static te_type _te_right_shift_or_left(te_type val1, te_type val2)
        {
        return (val2 >= 0) ? _te_right_shift(val1, val2) : _te_left_shift(val1, std::abs(val2));
        }

    [[nodiscard]]
    constexpr static te_type _te_sqr(te_type val) noexcept
        {
        return val * val;
        }

    [[nodiscard]]
    static te_type _te_max_maybe_nan(te_type val1, te_type val2MaybeNan) noexcept
        {
        return (std::max)(val1, std::isnan(val2MaybeNan) ? val1 : val2MaybeNan);
        }

    [[nodiscard]]
    static te_type _te_max(te_type val1, te_type val2, te_type val3, te_type val4, te_type val5,
                           te_type val6, te_type val7) noexcept
        {
        // assumes that at least val1 is a number, rest can be NaN
        // NOLINTBEGIN
        auto maxVal = _te_max_maybe_nan(val1, val2);
        maxVal = _te_max_maybe_nan(maxVal, val3);
        maxVal = _te_max_maybe_nan(maxVal, val4);
        maxVal = _te_max_maybe_nan(maxVal, val5);
        maxVal = _te_max_maybe_nan(maxVal, val6);
        return _te_max_maybe_nan(maxVal, val7);
        // NOLINTEND
        }

    [[nodiscard]]
    static te_type _te_min_maybe_nan(te_type val1, te_type val2MaybeNan) noexcept
        {
        return (std::min)(val1, std::isnan(val2MaybeNan) ? val1 : val2MaybeNan);
        }

    [[nodiscard]]
    static te_type _te_min(te_type val1, te_type val2, te_type val3, te_type val4, te_type val5,
                           te_type val6, te_type val7) noexcept
        {
        // assumes that at least val1 is legit, rest can be NaN
        // NOLINTBEGIN
        auto minVal = _te_min_maybe_nan(val1, val2);
        minVal = _te_min_maybe_nan(minVal, val3);
        minVal = _te_min_maybe_nan(minVal, val4);
        minVal = _te_min_maybe_nan(minVal, val5);
        minVal = _te_min_maybe_nan(minVal, val6);
        return _te_min_maybe_nan(minVal, val7);
        // NOLINTEND
        }

    [[nodiscard]]
    static te_type _te_and_maybe_nan(te_type val1, te_type val2MaybeNan) noexcept
        {
        return std::isnan(val2MaybeNan) ? val1 : (val1 && val2MaybeNan);
        }

    [[nodiscard]]
    static te_type _te_and_variadic(te_type val1, te_type val2, te_type val3, te_type val4,
                                    te_type val5, te_type val6, te_type val7) noexcept
        {
        // assumes that at least val1 is legit, rest can be NaN
        // NOLINTBEGIN
        auto andVal = _te_and_maybe_nan(val1, val2);
        andVal = _te_and_maybe_nan(andVal, val3);
        andVal = _te_and_maybe_nan(andVal, val4);
        andVal = _te_and_maybe_nan(andVal, val5);
        andVal = _te_and_maybe_nan(andVal, val6);
        return _te_and_maybe_nan(andVal, val7);
        // NOLINTEND
        }

    [[nodiscard]]
    static te_type _te_or_maybe_nan(te_type val1, te_type val2MaybeNan) noexcept
        {
        return std::isnan(val2MaybeNan) ? val1 : (val1 || val2MaybeNan);
        }

    [[nodiscard]]
    static te_type _te_or_variadic(te_type val1, te_type val2, te_type val3, te_type val4,
                                   te_type val5, te_type val6, te_type val7) noexcept
        {
        // assumes that at least val1 is legit, rest can be NaN
        // NOLINTBEGIN
        auto orVal = _te_or_maybe_nan(val1, val2);
        orVal = _te_or_maybe_nan(orVal, val3);
        orVal = _te_or_maybe_nan(orVal, val4);
        orVal = _te_or_maybe_nan(orVal, val5);
        orVal = _te_or_maybe_nan(orVal, val6);
        return _te_or_maybe_nan(orVal, val7);
        // NOLINTEND
        }

    [[nodiscard]]
    constexpr static te_type _te_if(te_type val1, te_type val2, te_type val3) noexcept
        {
        return (val1 != 0.0) ? val2 : val3;
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
    static te_type _te_cot(te_type val) noexcept
        {
        if (val == 0.0)
            {
            return te_parser::te_nan;
            }
        return 1 / static_cast<te_type>(std::tan(val));
        }

    [[nodiscard]]
    constexpr static te_type _te_sign(te_type val) noexcept
        {
        return static_cast<te_type>((val < 0.0) ? -1 : (val > 0.0) ? 1 : 0);
        }

    [[nodiscard]]
    constexpr static te_type _te_negate(te_type val) noexcept
        {
        return -val;
        }

    [[nodiscard]]
    constexpr static te_type _comma(
        [[maybe_unused]] te_type unusedVal,te_type val2) noexcept // NOLINT
        {
        return val2;
        }
    } // namespace te_builtins

//--------------------------------------------------
void te_parser::te_free_parameters(te_expr* texp)
    {
    if (texp == nullptr)
        {
        return;
        }
    if (is_closure(texp->m_value))
        {
        // last param is the context object, we don't manage that here
        for (auto param = texp->m_parameters.begin(); param != texp->m_parameters.end() - 1;
             ++param)
            {
            te_free(*param);
            *param = nullptr;
            }
        }
    else if (is_function(texp->m_value))
        {
        for (auto* param : texp->m_parameters)
            {
            te_free(param);
            param = nullptr;
            }
        }
    }

//--------------------------------------------------
const std::set<te_variable> te_parser::m_functions = { // NOLINT
    { "abs", static_cast<te_fun1>(te_builtins::_te_absolute_value), TE_PURE },
    { "acos", static_cast<te_fun1>(te_builtins::_te_acos), TE_PURE },
    // variadic, accepts 1-7 arguments
    { "and", static_cast<te_fun7>(te_builtins::_te_and_variadic),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "asin", static_cast<te_fun1>(te_builtins::_te_asin), TE_PURE },
    { "atan", static_cast<te_fun1>(te_builtins::_te_atan), TE_PURE },
    { "atan2", static_cast<te_fun2>(te_builtins::_te_atan2), TE_PURE },
    { "average", static_cast<te_fun7>(te_builtins::_te_average),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "bitlshift", static_cast<te_fun2>(te_builtins::_te_left_shift_or_right), TE_PURE },
    { "bitrshift", static_cast<te_fun2>(te_builtins::_te_right_shift_or_left), TE_PURE },
    { "ceil", static_cast<te_fun1>(te_builtins::_te_ceil), TE_PURE },
    { "clamp",
      static_cast<te_fun3>(
          [](const te_type num, const te_type start, const te_type end) // NOLINT
          {
              return (start <= end) ? std::clamp<te_type>(num, start, end) :
                                      std::clamp<te_type>(num, end, start);
          }),
      TE_PURE },
    { "combin", static_cast<te_fun2>(te_builtins::_te_ncr), TE_PURE },
    { "cos", static_cast<te_fun1>(te_builtins::_te_cos), TE_PURE },
    { "cosh", static_cast<te_fun1>(te_builtins::_te_cosh), TE_PURE },
    { "cot", static_cast<te_fun1>(te_builtins::_te_cot), TE_PURE },
    { "e", static_cast<te_fun0>(te_builtins::_te_e), TE_PURE },
    { "exp", static_cast<te_fun1>(te_builtins::_te_exp), TE_PURE },
    { "fac", static_cast<te_fun1>(te_builtins::_te_fac), TE_PURE },
    { "fact", static_cast<te_fun1>(te_builtins::_te_fac), TE_PURE },
    { "false", static_cast<te_fun0>(te_builtins::_te_false_value), TE_PURE },
    { "floor", static_cast<te_fun1>(te_builtins::_te_floor), TE_PURE },
    { "if", static_cast<te_fun3>(te_builtins::_te_if), TE_PURE },
    { "ifs", static_cast<te_fun6>(te_builtins::_te_ifs),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "ln", static_cast<te_fun1>(te_builtins::_te_log), TE_PURE },
    { "log10", static_cast<te_fun1>(te_builtins::_te_log10), TE_PURE },
    { "max", static_cast<te_fun7>(te_builtins::_te_max),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "min", static_cast<te_fun7>(te_builtins::_te_min),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "mod", static_cast<te_fun2>(te_builtins::_te_modulus), TE_PURE },
    { "nan", static_cast<te_fun0>(te_builtins::_te_nan_value), TE_PURE },
    { "ncr", static_cast<te_fun2>(te_builtins::_te_ncr), TE_PURE },
    { "not", static_cast<te_fun1>(te_builtins::_te_not), TE_PURE },
    { "npr", static_cast<te_fun2>(te_builtins::_te_npr), TE_PURE },
    { "or", static_cast<te_fun7>(te_builtins::_te_or_variadic),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "permut", static_cast<te_fun2>(te_builtins::_te_npr), TE_PURE },
    { "pi", static_cast<te_fun0>(te_builtins::_te_pi), TE_PURE },
    { "pow", static_cast<te_fun2>(te_builtins::_te_pow), TE_PURE },
    { "power", /* Excel alias*/ static_cast<te_fun2>(te_builtins::_te_pow), TE_PURE },
    { "rand", static_cast<te_fun0>(te_builtins::_te_random), TE_PURE },
    { "round", static_cast<te_fun2>(te_builtins::_te_round),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "sign", static_cast<te_fun1>(te_builtins::_te_sign), TE_PURE },
    { "sin", static_cast<te_fun1>(te_builtins::_te_sin), TE_PURE },
    { "sinh", static_cast<te_fun1>(te_builtins::_te_sinh), TE_PURE },
    { "sqr", static_cast<te_fun1>(te_builtins::_te_sqr), TE_PURE },
    { "sqrt", static_cast<te_fun1>(te_builtins::_te_sqrt), TE_PURE },
    { "sum", static_cast<te_fun7>(te_builtins::_te_sum),
      static_cast<te_variable_flags>(TE_PURE | TE_VARIADIC) },
    { "tan", static_cast<te_fun1>(te_builtins::_te_tan), TE_PURE },
    { "tanh", static_cast<te_fun1>(te_builtins::_te_tanh), TE_PURE },
    { "tgamma", static_cast<te_fun1>(te_builtins::_te_tgamma), TE_PURE },
    { "true", static_cast<te_fun0>(te_builtins::_te_true_value), TE_PURE },
    { "trunc", static_cast<te_fun1>(te_builtins::_te_trunc), TE_PURE }
};

//--------------------------------------------------
void te_parser::next_token(te_parser::state* theState)
    {
    assert(theState);
    if (theState == nullptr)
        {
        return;
        }

    theState->m_type = te_parser::state::token_type::TOK_NULL;

    do // NOLINT
        {
        if (*theState->m_next == 0)
            {
            theState->m_type = te_parser::state::token_type::TOK_END;
            return;
            }

        /* Try reading a number. */
        if (((*theState->m_next >= '0') && (*theState->m_next <= '9')) ||
            (*theState->m_next == get_decimal_separator()))
            {
            char* nEnd{ nullptr };
            theState->m_value = static_cast<te_type>(std::strtod(theState->m_next, &nEnd));
            theState->m_next = nEnd;
            theState->m_type = te_parser::state::token_type::TOK_NUMBER;
            }
        else
            {
            /* Look for a variable or builtin function call. */
            if (is_letter(*theState->m_next) || (*theState->m_next == '_'))
                {
                const char* start = theState->m_next;
                while (is_name_char_valid(*theState->m_next))
                    {
                    std::advance(theState->m_next, 1);
                    }

                m_varFound = false;
                const std::string_view currentVarToken{ start, static_cast<std::string::size_type>(
                                                                   theState->m_next - start) };
                m_currentVar = find_lookup(theState, currentVarToken);
                if (m_currentVar != theState->m_lookup.cend())
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
                                    m_currentVar = find_lookup(theState, currentVarToken);
                                    assert(
                                        m_currentVar != theState->m_lookup.cend() &&
                                        "Internal error in parser using unknown symbol resolver.");
                                    if (m_currentVar != theState->m_lookup.cend())
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
                                    m_currentVar = find_lookup(theState, currentVarToken);
                                    assert(
                                        m_currentVar != theState->m_lookup.cend() &&
                                        "Internal error in parser using unknown symbol resolver.");
                                    if (m_currentVar != theState->m_lookup.cend())
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
                    theState->m_type = te_parser::state::token_type::TOK_ERROR;
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
                        theState->m_type = te_parser::state::token_type::TOK_NUMBER;
                        theState->m_value = m_currentVar->m_value;
                        }
                    else if (is_variable(m_currentVar->m_value))
                        {
                        theState->m_type = te_parser::state::token_type::TOK_VARIABLE;
                        theState->m_value = m_currentVar->m_value;
                        }
                    else if (is_function(m_currentVar->m_value))
                        {
                        theState->m_type = te_parser::state::token_type::TOK_FUNCTION;
                        theState->m_varType = m_currentVar->m_type;
                        theState->m_value = m_currentVar->m_value;
                        }
                    else if (is_closure(m_currentVar->m_value))
                        {
                        theState->context = m_currentVar->m_context;
                        theState->m_type = te_parser::state::token_type::TOK_FUNCTION;
                        theState->m_varType = m_currentVar->m_type;
                        theState->m_value = m_currentVar->m_value;
                        }
                    }
                }
            else
                {
                /* Look for an operator or special character. */
                const auto tok = *theState->m_next;
                std::advance(theState->m_next, 1);
                if (tok == '+')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = te_builtins::_te_add;
                    }
                else if (tok == '-')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = te_builtins::_te_sub;
                    }
                else if (tok == '*' && (*theState->m_next == '*'))
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_pow);
                    std::advance(theState->m_next, 1);
                    }
                else if (tok == '*')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = te_builtins::_te_mul;
                    }
                else if (tok == '/')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = te_builtins::_te_divide;
                    }
                else if (tok == '^')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_pow);
                    }
                else if (tok == '%')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = te_builtins::_te_modulus;
                    }
                else if (tok == '(')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_OPEN;
                    }
                else if (tok == ')')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_CLOSE;
                    }
                else if (tok == get_list_separator())
                    {
                    theState->m_type = te_parser::state::token_type::TOK_SEP;
                    }
                // shift operators
                else if (tok == '<' && (*theState->m_next == '<'))
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_left_shift);
                    std::advance(theState->m_next, 1);
                    }
                else if (tok == '>' && (*theState->m_next == '>'))
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_right_shift);
                    std::advance(theState->m_next, 1);
                    }
                // logical operators
                else if (tok == '=' && (*theState->m_next == '='))
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_equal);
                    std::advance(theState->m_next, 1);
                    }
                else if (tok == '=')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_equal);
                    }
                else if (tok == '!' && (*theState->m_next == '=')) // NOLINT
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_not_equal);
                    std::advance(theState->m_next, 1);
                    }
                else if (tok == '<' && (*theState->m_next == '>'))
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_not_equal);
                    std::advance(theState->m_next, 1);
                    }
                else if (tok == '<' && (*theState->m_next == '='))
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_less_than_equal_to);
                    std::advance(theState->m_next, 1);
                    }
                else if (tok == '<')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_less_than);
                    }
                else if (tok == '>' && (*theState->m_next == '='))
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_greater_than_equal_to);
                    std::advance(theState->m_next, 1);
                    }
                else if (tok == '>')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_greater_than);
                    }
                else if (tok == '&')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_and);
                    }
                else if (tok == '|')
                    {
                    theState->m_type = te_parser::state::token_type::TOK_INFIX;
                    theState->m_value = static_cast<te_fun2>(te_builtins::_te_or);
                    }
                else if (tok == ' ' || tok == '\t' || tok == '\n' || tok == '\r')
                    { /*noop*/
                    }
                else
                    {
                    theState->m_type = te_parser::state::token_type::TOK_ERROR;
                    }
                }
            }
        } while (theState->m_type == te_parser::state::token_type::TOK_NULL);
    }

//--------------------------------------------------
te_expr* te_parser::base(te_parser::state* theState)
    {
    /* <base>      =    <constant> | <variable> | <function-0> {"(" ")"} | <function-1> <power> |
                        <function-X> "(" <expr> {"," <expr>} ")" | "(" <list> ")" */
    te_expr* ret{ nullptr };

    if (theState->m_type == te_parser::state::token_type::TOK_OPEN)
        {
        next_token(theState);
        ret = list(theState);
        if (theState->m_type != te_parser::state::token_type::TOK_CLOSE)
            {
            theState->m_type = te_parser::state::token_type::TOK_ERROR;
            }
        else
            {
            next_token(theState);
            }
        }
    else if (theState->m_type == te_parser::state::token_type::TOK_NUMBER)
        {
        ret = new_expr(TE_DEFAULT, theState->m_value);
        next_token(theState);
        }
    else if (theState->m_type == te_parser::state::token_type::TOK_VARIABLE)
        {
        ret = new_expr(TE_DEFAULT, theState->m_value);
        next_token(theState);
        }
    else if (theState->m_type == te_parser::state::token_type::TOK_NULL ||
             theState->m_type == te_parser::state::token_type::TOK_ERROR ||
             theState->m_type == te_parser::state::token_type::TOK_END ||
             theState->m_type == te_parser::state::token_type::TOK_SEP ||
             theState->m_type == te_parser::state::token_type::TOK_CLOSE ||
             theState->m_type == te_parser::state::token_type::TOK_INFIX)
        {
        ret = new_expr(TE_DEFAULT, te_variant_type{ te_nan });
        theState->m_type = te_parser::state::token_type::TOK_ERROR;
        }
    else if (is_function0(theState->m_value) || is_closure0(theState->m_value))
        {
        ret = new_expr(theState->m_varType, theState->m_value, {});
        if (is_closure(theState->m_value))
            {
            ret->m_parameters[0] = theState->context;
            }
        next_token(theState);
        if (theState->m_type == te_parser::state::token_type::TOK_OPEN)
            {
            next_token(theState);
            if (theState->m_type != te_parser::state::token_type::TOK_CLOSE)
                {
                theState->m_type = te_parser::state::token_type::TOK_ERROR;
                }
            else
                {
                next_token(theState);
                }
            }
        }
    else if (is_function1(theState->m_value) || is_closure1(theState->m_value))
        {
        ret = new_expr(theState->m_varType, theState->m_value);
        if (is_closure(theState->m_value))
            {
            ret->m_parameters[1] = theState->context;
            }
        next_token(theState);
        ret->m_parameters[0] = power(theState);
        }
    else if (is_function2(theState->m_value) || is_closure2(theState->m_value) ||
             is_function3(theState->m_value) || is_closure3(theState->m_value) ||
             is_function4(theState->m_value) || is_closure4(theState->m_value) ||
             is_function5(theState->m_value) || is_closure5(theState->m_value) ||
             is_function6(theState->m_value) || is_closure6(theState->m_value) ||
             is_function7(theState->m_value) || is_closure7(theState->m_value))
        {
        const int arity = get_arity(theState->m_value);

        ret = new_expr(theState->m_varType, theState->m_value);
        if (is_closure(theState->m_value))
            {
            ret->m_parameters[arity] = theState->context;
            }
        next_token(theState);

        if (theState->m_type != te_parser::state::token_type::TOK_OPEN)
            {
            theState->m_type = te_parser::state::token_type::TOK_ERROR;
            }
        else
            {
            // If there are vars or other functions in the parameters, keep track of the original
            // opening function; that is what we will do our variadic check on.
            const bool varValid{ m_varFound };
            const std::set<te_variable>::const_iterator openingVar = m_currentVar;
            // load any parameters
            int i{ 0 }; // NOLINT
            for (i = 0; i < arity; i++)
                {
                next_token(theState);
                ret->m_parameters[i] = expr(theState);
                if (theState->m_type != te_parser::state::token_type::TOK_SEP)
                    {
                    break;
                    }
                }
            if (theState->m_type == te_parser::state::token_type::TOK_CLOSE && (i != arity - 1) &&
                varValid && is_variadic(openingVar->m_type))
                {
                next_token(theState);
                }
            else if (theState->m_type != te_parser::state::token_type::TOK_CLOSE ||
                     (i != arity - 1))
                {
                theState->m_type = te_parser::state::token_type::TOK_ERROR;
                }
            else
                {
                next_token(theState);
                }
            }
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::list(te_parser::state* theState)
    {
    /* <list>      =    <expr> {"," <expr>} */
    te_expr* ret = expr(theState);

    while (theState->m_type == te_parser::state::token_type::TOK_SEP)
        {
        next_token(theState);
        ret = new_expr(TE_PURE, te_variant_type(te_builtins::_comma), { ret, expr(theState) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr(te_parser::state* theState)
    {
    /* <expr>      =    <term> {(logic operations) <term>} */
    // These are the lowest of operator precedence
    // (once we have split tokens into arguments)
    te_expr* ret = expr_level2(theState);

    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == te_builtins::_te_and ||
            get_function2(theState->m_value) == te_builtins::_te_or))
        {
        const te_fun2 func = get_function2(theState->m_value);
        next_token(theState);
        ret = new_expr(TE_PURE, func, { ret, expr_level2(theState) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr_level2(te_parser::state* theState)
    {
    /* <expr>      =    <term> {(comparison operators) <term>} */
    // Second from the lowest of operator precedence
    te_expr* ret = expr_level3(theState);

    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == te_builtins::_te_equal ||
            get_function2(theState->m_value) == te_builtins::_te_not_equal ||
            get_function2(theState->m_value) == te_builtins::_te_less_than ||
            get_function2(theState->m_value) == te_builtins::_te_less_than_equal_to ||
            get_function2(theState->m_value) == te_builtins::_te_greater_than ||
            get_function2(theState->m_value) == te_builtins::_te_greater_than_equal_to))
        {
        const te_fun2 func = get_function2(theState->m_value);
        next_token(theState);
        ret = new_expr(TE_PURE, func, { ret, expr_level3(theState) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr_level3(te_parser::state* theState)
    {
    /* <expr>      =    <term> {("<<" | ">>") <term>} */
    // Third from the lowest level of operator precendence
    te_expr* ret = expr_level4(theState);

    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == te_builtins::_te_left_shift ||
            get_function2(theState->m_value) == te_builtins::_te_right_shift))
        {
        const te_fun2 func = get_function2(theState->m_value);
        next_token(theState);
        ret = new_expr(TE_PURE, func, { ret, expr_level4(theState) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::expr_level4(te_parser::state* theState)
    {
    /* <expr>      =    <term> {("+" | "-") <term>} */
    // Fourth from the lowest level of operator precendence
    te_expr* ret = term(theState);

    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == te_builtins::_te_add ||
            get_function2(theState->m_value) == te_builtins::_te_sub))
        {
        const te_fun2 func = get_function2(theState->m_value);
        next_token(theState);
        ret = new_expr(TE_PURE, func, { ret, term(theState) });
        }

    return ret;
    }

//--------------------------------------------------
te_expr* te_parser::term(te_parser::state* theState)
    {
    /* <term>      =    <factor> {("*" | "/" | "%") <factor>} */
    te_expr* ret = factor(theState);
    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == te_builtins::_te_mul ||
            get_function2(theState->m_value) == te_builtins::_te_divide ||
            get_function2(theState->m_value) == te_builtins::_te_modulus))
        {
        const te_fun2 func = get_function2(theState->m_value);
        next_token(theState);
        ret = new_expr(TE_PURE, func, { ret, factor(theState) });
        }

    return ret;
    }

#ifdef TE_POW_FROM_RIGHT
te_expr* te_parser::factor(te_parser::state* theState)
    {
    /* <factor>    =    <power> {"^" <power>} */
    te_expr* ret = power(theState);

    int neg{ 0 };

    if (ret->m_type == TE_PURE && is_function1(ret->m_value) &&
        get_function1(ret->m_value) == te_builtins::_te_negate)
        {
        te_expr* se = ret->m_parameters[0];
        delete ret;
        ret = se;
        neg = 1;
        }

    te_expr* insertion{ nullptr };
    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == static_cast<te_fun2>(te_builtins::_te_pow)))
        {
        const te_fun2 t = get_function2(theState->m_value);
        next_token(theState);

        if (insertion)
            {
            /* Make exponentiation go right-to-left. */
            te_expr* insert = new_expr(TE_PURE, t,
                                       { insertion->m_parameters[1], power(theState) });
            insertion->m_parameters[1] = insert;
            insertion = insert;
            }
        else
            {
            ret = new_expr(TE_PURE, t, { ret, power(theState) });
            insertion = ret;
            }
        }

    if (neg)
        {
        ret = new_expr(TE_PURE, te_variant_type(te_builtins::_te_negate), { ret });
        }

    return ret;
    }
#else
te_expr* te_parser::factor(te_parser::state* theState)
    {
    /* <factor>    =    <power> {"^" <power>} */
    te_expr* ret = power(theState);
    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == static_cast<te_fun2>(te_builtins::_te_pow)))
        {
        const te_fun2 func = get_function2(theState->m_value);
        next_token(theState);
        ret = new_expr(TE_PURE, func, { ret, power(theState) });
        }

    return ret;
    }
#endif

//--------------------------------------------------
te_expr* te_parser::power(te_parser::state* theState)
    {
    /* <power>     =    {("-" | "+")} <base> */
    int theSign{ 1 };
    while (theState->m_type == te_parser::state::token_type::TOK_INFIX &&
           is_function2(theState->m_value) &&
           (get_function2(theState->m_value) == te_builtins::_te_add ||
            get_function2(theState->m_value) == te_builtins::_te_sub))
        {
        if (get_function2(theState->m_value) == te_builtins::_te_sub)
            {
            theSign = -theSign;
            }
        next_token(theState);
        }

    te_expr* ret{ nullptr };

    if (theSign == 1)
        {
        ret = base(theState);
        }
    else
        {
        ret = new_expr(TE_PURE, te_variant_type(te_builtins::_te_negate), { base(theState) });
        }

    return ret;
    }

//--------------------------------------------------
te_type te_parser::te_eval(const te_expr* texp)
    {
    if (texp == nullptr)
        {
        return te_nan;
        }

    // NOLINTBEGIN
    // cppcheck-suppress unreadVariable
    const auto M = [&texp = std::as_const(texp)](const size_t e)
    { return (e < texp->m_parameters.size()) ? te_eval(texp->m_parameters[e]) : te_nan; };

    switch (texp->m_value.index())
        {
    case 0:
        return get_constant(texp->m_value);
    case 1:
        return *(get_variable(texp->m_value));
    case 2:
        return get_function0(texp->m_value)();
    case 3:
        return get_function1(texp->m_value)(M(0));
    case 4:
        return get_function2(texp->m_value)(M(0), M(1));
    case 5:
        return get_function3(texp->m_value)(M(0), M(1), M(2));
    case 6:
        return get_function4(texp->m_value)(M(0), M(1), M(2), M(3));
    case 7:
        return get_function5(texp->m_value)(M(0), M(1), M(2), M(3), M(4));
    case 8:
        return get_function6(texp->m_value)(M(0), M(1), M(2), M(3), M(4), M(5));
    case 9:
        return get_function7(texp->m_value)(M(0), M(1), M(2), M(3), M(4), M(5), M(6));
    case 10:
        return get_closure0(texp->m_value)(texp->m_parameters[0]);
    case 11:
        return get_closure1(texp->m_value)(texp->m_parameters[1], M(0));
    case 12:
        return get_closure2(texp->m_value)(texp->m_parameters[2], M(0), M(1));
    case 13:
        return get_closure3(texp->m_value)(texp->m_parameters[3], M(0), M(1), M(2));
    case 14:
        return get_closure4(texp->m_value)(texp->m_parameters[4], M(0), M(1), M(2), M(3));
    case 15:
        return get_closure5(texp->m_value)(texp->m_parameters[5], M(0), M(1), M(2), M(3), M(4));
    case 16:
        return get_closure6(texp->m_value)(
            texp->m_parameters[6], M(0), M(1), M(2), M(3), M(4), M(5));
    case 17:
        return get_closure7(texp->m_value)(
            texp->m_parameters[7], M(0), M(1), M(2), M(3), M(4), M(5), M(6));
    default:
        return te_nan;
        };
    // NOLINTEND
    }

//--------------------------------------------------
void te_parser::optimize(te_expr* texp)
    {
    if (texp == nullptr)
        {
        return;
        }
    /* Evaluates as much as possible. */
    if (is_constant(texp->m_value) || is_variable(texp->m_value))
        {
        return;
        }

    /* Only optimize out functions flagged as pure. */
    if (is_pure(texp->m_type))
        {
        const int arity = get_arity(texp->m_value);
        bool known{ true };
        for (int i = 0; i < arity; ++i)
            {
            if (texp->m_parameters[i] == nullptr)
                {
                break;
                }
            optimize(texp->m_parameters[i]);
            if (!is_constant(texp->m_parameters[i]->m_value))
                {
                known = false;
                }
            }
        if (known)
            {
            const auto value = te_eval(texp);
            te_free_parameters(texp);
            texp->m_type = TE_DEFAULT;
            texp->m_value = value;
            }
        }
    }

//--------------------------------------------------
te_expr* te_parser::te_compile(const std::string_view expression, std::set<te_variable>& variables)
    {
    state theState(expression.data(), TE_DEFAULT, variables);

    next_token(&theState);
    te_expr* root = list(&theState);

    if (theState.m_type != te_parser::state::token_type::TOK_END)
        {
        te_free(root);
        m_errorPos = (theState.m_next - theState.m_start);
        if (m_errorPos > 0)
            {
            --m_errorPos;
            }
        return nullptr;
        }

    optimize(root);
    m_errorPos = te_parser::npos;
    return root;
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
    if ((m_expression.length() > 0) && m_expression.front() == '=')
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
                m_errorPos = static_cast<decltype(m_errorPos)>(commentStart);
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
            m_expression.erase(commentStart, commentEnd - commentStart);
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
        m_result = (m_compiledExpression != nullptr) ? te_eval(m_compiledExpression) : te_nan;
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
te_type te_parser::evaluate(const std::string_view expression) // NOLINT(-readability-identifier-naming)
    {
    if (compile(expression))
        {
        return evaluate();
        }
    return te_nan;
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
