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
  * Copyright (c) 2020-2022 Blake Madden
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

#include "../tinyexpr.h"
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

namespace TETesting
{
double sum0() {
    return 6;
}
double sum1(double a) {
    return a * 2;
}
double sum2(double a, double b) {
    return a + b;
}
double sum3(double a, double b, double c) {
    return a + b + c;
}
double sum4(double a, double b, double c, double d) {
    return a + b + c + d;
}
double sum5(double a, double b, double c, double d, double e) {
    return a + b + c + d + e;
}
double sum6(double a, double b, double c, double d, double e, double f) {
    return a + b + c + d + e + f;
}
double sum7(double a, double b, double c, double d, double e, double f, double g) {
    return a + b + c + d + e + f + g;
}

double clo0(const te_expr* context) {
    if (context) return *(std::get<const double*>(context->m_value)) + 6;
    return 6;
}
double clo1(const te_expr* context, double a) {
    if (context) return *(std::get<const double*>(context->m_value)) + a * 2;
    return a * 2;
}
double clo2(const te_expr* context, double a, double b) {
    if (context) return *(std::get<const double*>(context->m_value)) + a + b;
    return a + b;
}

double clo3(const te_expr* context, double a, double b, double c) {
    if (context) return *(std::get<const double*>(context->m_value)) + a + b + c;
    return a + b + c;
}

double clo4(const te_expr* context, double a, double b, double c, double d) {
    if (context) return *(std::get<const double*>(context->m_value)) + a + b + c + d;
    return a + b + c + d;
}

double clo5(const te_expr* context, double a, double b, double c, double d, double e) {
    if (context) return *(std::get<const double*>(context->m_value)) + a + b + c + d + e;
    return a + b + c + d + e;
}

double clo6(const te_expr* context, double a, double b, double c, double d, double e, double f) {
    if (context) return *(std::get<const double*>(context->m_value)) + a + b + c + d + e + f;
    return a + b + c + d + e + f;
}

double clo7(const te_expr* context, double a, double b, double c, double d, double e, double f, double g) {
    if (context) return *(std::get<const double*>(context->m_value)) + a + b + c + d + e + f + g;
    return a + b + c + d + e + f + g;
}

inline double AddEm(const double a, const double b){
    return a+b;
}

inline double AddEm3(const double a, const double b, const double c){
    return a+b+c;
}

inline double __value(const double a){
    return a;
}

inline double return5(){
    return 5;
}

inline double __mult(const double a, const double b, const double c, const double d){
    return a*b*c*d;
}

class te_expr_array : public te_expr
{
public:
    te_expr_array(const variable_flags type) noexcept : te_expr(type) {}
    std::array<double, 5> m_data = { 5,6,7,8,9 };
};

double cell(const te_expr* context, double a) {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    return static_cast<double>(c->m_data[a]);
}

double bench_a5(double a) {
    return a+5;
}

double bench_a55(double a) {
    return 5+a+5;
}

double bench_a5abs(double a) {
    return fabs(a+5);
}

double bench_a52(double a) {
    return (a+5)*2;
}

double bench_a10(double a) {
    return a+(5*2);
}

double bench_as(double a) {
    return sqrt(pow(a, 1.5) + pow(a, 2.5));
}

double bench_al(double a) {
    return (1/(a+1)+2/(a+2)+3/(a+3));
}

TEST_CASE("Main tests", "[main]")
    {
    te_parser tep;

    CHECK(tep.evaluate("1") == 1);
    CHECK(tep.evaluate("1 ") == 1);
    CHECK(tep.evaluate("(1)") == 1);

    CHECK_THAT(tep.evaluate("pi"), Catch::Matchers::WithinRel(3.14159, 0.00001));
    CHECK(tep.evaluate("atan(1)*4 - pi") == 0);
    CHECK_THAT(tep.evaluate("e"), Catch::Matchers::WithinRel(2.71828, 0.00001));

    CHECK(tep.evaluate("2+1") == 2 + 1);
    CHECK(tep.evaluate("(((2+(1))))") == 2 + 1);
    CHECK(tep.evaluate("3+2") == 3 + 2);

    CHECK(tep.evaluate("3+2+4") == 3 + 2 + 4);
    CHECK(tep.evaluate("(3+2)+4") == 3 + 2 + 4);
    CHECK(tep.evaluate("3+(2+4)") == 3 + 2 + 4);
    CHECK(tep.evaluate("(3+2+4)") == 3 + 2 + 4);

    CHECK(tep.evaluate("3*2*4") == 3 * 2 * 4);
    CHECK(tep.evaluate("(3*2)*4") == 3 * 2 * 4);
    CHECK(tep.evaluate("3*(2*4)") == 3 * 2 * 4);
    CHECK(tep.evaluate("(3*2*4)") == 3 * 2 * 4);

    CHECK(tep.evaluate("3-2-4") == 3 - 2 - 4);
    CHECK(tep.evaluate("(3-2)-4") == (3 - 2) - 4);
    CHECK(tep.evaluate("3-(2-4)") == 3 - (2 - 4));
    CHECK(tep.evaluate("(3-2-4)") == 3 - 2 - 4);

    CHECK(tep.evaluate("3/2/4") == 3.0 / 2.0 / 4.0);
    CHECK(tep.evaluate("(3/2)/4") == (3.0 / 2.0) / 4.0);
    CHECK(tep.evaluate("3/(2/4)") == 3.0 / (2.0 / 4.0));
    CHECK(tep.evaluate("(3/2/4)") == 3.0 / 2.0 / 4.0);

    CHECK(tep.evaluate("(3*2/4)") == 3.0 * 2.0 / 4.0);
    CHECK(tep.evaluate("(3/2*4)") == 3.0 / 2.0 * 4.0);
    CHECK(tep.evaluate("3*(2/4)") == 3.0 * (2.0 / 4.0));

    CHECK(tep.evaluate("asin sin .5") == 0.5);
    CHECK(tep.evaluate("sin asin .5") == 0.5);
    CHECK(tep.evaluate("ln exp .5") == 0.5);
    CHECK(tep.evaluate("exp ln .5") == 0.5);

    CHECK(tep.evaluate("asin sin-.5") == -0.5);
    CHECK(tep.evaluate("asin sin-0.5") == -0.5);
    CHECK(tep.evaluate("asin sin -0.5") == -0.5);
    CHECK(tep.evaluate("asin (sin -0.5)") == -0.5);
    CHECK(tep.evaluate("asin (sin (-0.5))") == -0.5);
    CHECK(tep.evaluate("asin sin (-0.5)") == -0.5);
    CHECK(tep.evaluate("(asin sin (-0.5))") == -0.5);

    CHECK(tep.evaluate("log10 1000") == 3);
    CHECK(tep.evaluate("log10 1e3") == 3);
    CHECK(tep.evaluate("log10 1000") == 3);
    CHECK(tep.evaluate("log10 1e3") == 3);
    CHECK(tep.evaluate("log10(1000)") == 3);
    CHECK(tep.evaluate("log10(1e3)") == 3);
    CHECK(tep.evaluate("log10 1.0e3") == 3);
    CHECK(tep.evaluate("10^5*5e-5") == 5);

#ifdef TE_NAT_LOG
    CHECK_THAT(tep.evaluate("log 1000"), 6.9078, 0.00001));
    CHECK(tep.evaluate("log e") == 1);
    CHECK(tep.evaluate("log (e^10)") == 10);
#else
    CHECK(tep.evaluate("log 1000") == 3);
#endif

    CHECK(tep.evaluate("ln (e^10)") == 10);
    CHECK(tep.evaluate("100^.5+1") == 11);
    CHECK(tep.evaluate("100 ^.5+1") == 11);
    CHECK(tep.evaluate("100^+.5+1") == 11);
    CHECK(tep.evaluate("100^--.5+1") == 11);
    CHECK(tep.evaluate("100^---+-++---++-+-+-.5+1") == 11);

    CHECK(tep.evaluate("100^-.5+1") == 1.1);
    CHECK(tep.evaluate("100^---.5+1") == 1.1);
    CHECK(tep.evaluate("100^+---.5+1") == 1.1);
    CHECK(tep.evaluate("1e2^+---.5e0+1e0") == 1.1);
    CHECK(tep.evaluate("--(1e2^(+(-(-(-.5e0))))+1e0)") == 1.1);

    CHECK(tep.evaluate("sqrt 100 + 7") == 17);
    CHECK(tep.evaluate("sqrt 100 * 7") == 70);
    CHECK(tep.evaluate("sqrt (100 * 100)") == 100);

    CHECK(tep.evaluate("1,2") == 2);
    CHECK(tep.evaluate("1,2+1") == 3);
    CHECK(tep.evaluate("1+1,2+2,2+1") == 3);
    CHECK(tep.evaluate("1,2,3") == 3);
    CHECK(tep.evaluate("(1,2),3") == 3);
    CHECK(tep.evaluate("1,(2,3)") == 3);
    CHECK(tep.evaluate("-(1,(2,3))") == -3);

    CHECK(tep.evaluate("2^2") == 4);
    CHECK(tep.evaluate("pow(2,2)") == 4);

    CHECK_THAT(tep.evaluate("atan2(1,1)"), Catch::Matchers::WithinRel(0.7854, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(1,2)"), Catch::Matchers::WithinRel(0.46364, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(2,1)"), Catch::Matchers::WithinRel(1.1071, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(3,4)"), Catch::Matchers::WithinRel(0.6435, 0.00001));
    CHECK_THAT(tep.evaluate("atan2(3+3,4*2)"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(3+3,(4*2))"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK_THAT(tep.evaluate("atan2((3+3),4*2)"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK_THAT(tep.evaluate("atan2((3+3),(4*2))"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK(tep.evaluate("max(9, 7)") == 9);
    CHECK(tep.evaluate("min(9, 7)") == 7);
    CHECK(tep.evaluate("mod(12, 10)") == 2);
    CHECK(tep.evaluate("sign(-7.9)") == -1);
    CHECK(tep.evaluate("sign(7.9)") == 1);
    CHECK(tep.evaluate("sign(0)") == 0);
    CHECK(tep.evaluate("trunc(9.57878423)") == 9);
    CHECK(tep.evaluate("trunc(9.3)") == 9);

    SECTION("variadic functions")
        {
        CHECK(tep.evaluate("round(9.57878423, 0)") == 10);
        CHECK(tep.evaluate("round(9.57878423)") == 10);
        CHECK(tep.evaluate("round(pow(2,2))") == 4);
        // non-variadic function inside of variadic
        CHECK(tep.evaluate("round(9.57878423, 1)") == 9.6);
        CHECK(tep.evaluate("round(9.57878423, 2)") == 9.58);
        CHECK(tep.evaluate("round(9.57878423, 3)") == 9.579);
        CHECK(tep.evaluate("sum(9)") == 9);
        CHECK(tep.evaluate("sum(9,9)") == 18);
        CHECK(tep.evaluate("sum(9,9,9)") == 27);
        CHECK(tep.evaluate("sum(9,9,9,9)") == 36);
        CHECK(tep.evaluate("sum(9,9,9,9,9)") == 45);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9)") == 54);
        CHECK(tep.evaluate("sum(pow(3,2),sum(3,3,3),9,pow(3,2),6+3,9,9)") == 63);
        CHECK(tep.evaluate("pow(3,2)+sum(pow(3,2),sum(3,3,3),9,pow(3,2),6+3,9,9)") == 72);
        CHECK(tep.evaluate("pow(2, sum(2,2))") == 16);
        CHECK(tep.evaluate("average(1)") == 1);
        CHECK(tep.evaluate("average(1,2)") == 1.5);
        CHECK(tep.evaluate("average(1,2,3)") == 2);
        CHECK(tep.evaluate("average(1,2,3,4)") == 2.5);
        CHECK(tep.evaluate("average(1,2,3,4,5)") == 3);
        CHECK(tep.evaluate("average(1,2,3,4,5,6)") == 3.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7)") == 4);
        }

    SECTION("logical")
        {
        CHECK(tep.evaluate("if(1, 9, 7)") == 9);
        CHECK(tep.evaluate("if(0, 9, 7)") == 7);
        CHECK(tep.evaluate("and(0.0, 5)") == 0);
        CHECK(tep.evaluate("and(0.0, 0)") == 0);
        CHECK(tep.evaluate("AND(-1, 5)") == 1);
        CHECK(tep.evaluate("AND(1, 1)") == 1);
        CHECK(tep.evaluate("or(-1, 0.0)") == 1);
        CHECK(tep.evaluate("or(0.0, 5)") == 1);
        CHECK(tep.evaluate("or(0.0, 0)") == 0);
        CHECK(tep.evaluate("OR(-1, 5)") == 1);
        CHECK(tep.evaluate("OR(1, 1)") == 1);
        CHECK(tep.evaluate("not(-1)") == 0);
        CHECK(tep.evaluate("not(0.0)") == 1);
        CHECK(tep.evaluate("NOT(0)") == 1);
        CHECK(tep.evaluate("NOT(5)") == 0);
        }

    SECTION("operators")
        {
        CHECK(tep.evaluate("0.0 & 5") == 0);
        CHECK(tep.evaluate("0.0 & 0") == 0);
        CHECK(tep.evaluate("-1 & 5") == 1);
        CHECK(tep.evaluate("1 & 1") == 1);
        CHECK(tep.evaluate("0.0 | 5") == 1);
        CHECK(tep.evaluate("0.0 | 0") == 0);
        CHECK(tep.evaluate("-1 | 5") == 1);
        CHECK(tep.evaluate("1 | 1") == 1);
        CHECK(tep.evaluate("-1 | 0.0") == 1);
        }
    }

TEST_CASE("Optimize", "[optimize]")
    {
    te_parser tep;

    auto res = tep.evaluate("");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 0);

    res = tep.evaluate("1+");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 1);

    res = tep.evaluate("1)");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 1);

    res = tep.evaluate("(1");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 1);

    res = tep.evaluate("1**1");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 2);

    res = tep.evaluate("1*2(+4");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 3);

    res = tep.evaluate("1*2(1+4");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 3);

    res = tep.evaluate("a+5");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 0);

    res = tep.evaluate("A+5");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 0);

    res = tep.evaluate("aA+5");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 1);

    res = tep.evaluate("1^^5");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 2);

    res = tep.evaluate("1**5");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 2);
    
    res = tep.evaluate("sin(cos5");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 7);

    res = tep.evaluate("average()"); // needs at least 1 arg
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 8);

    res = tep.evaluate("sum()"); // needs at least 1 arg
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 4);
    }

TEST_CASE("Combinatorics", "[combinatorics]")
    {
    te_parser tep;

    CHECK(tep.evaluate("fac(0)") == 1);
    CHECK(tep.evaluate("fac(0.2)") == 1);
    CHECK(tep.evaluate("fac(1)") == 1);
    CHECK(tep.evaluate("fac(2)") == 2);
    CHECK(tep.evaluate("fac(3)") == 6);
    CHECK(tep.evaluate("fac(4.8)") == 24);
    CHECK(tep.evaluate("fac(10)") == 3'628'800);

    CHECK(tep.evaluate("ncr(0,0)") == 1);
    CHECK(tep.evaluate("ncr(10,1)") == 10);
    CHECK(tep.evaluate("ncr(10,0)") == 1);
    CHECK(tep.evaluate("ncr(10,10)") == 1);
    CHECK(tep.evaluate("ncr(16,7)") == 11'440);
    CHECK(tep.evaluate("ncr(16,9)") == 11'440);
    CHECK(tep.evaluate("ncr(100,95)") == 75'287'520);

    CHECK(tep.evaluate("npr(0,0)") == 1);
    CHECK(tep.evaluate("npr(10,1)") == 10);
    CHECK(tep.evaluate("npr(10,0)") == 1);
    CHECK(tep.evaluate("npr(10,10)") == 3'628'800);
    CHECK(tep.evaluate("npr(20,5)") == 1'860'480);
    CHECK(tep.evaluate("npr(100,4)") == 94'109'400);
    }

TEST_CASE("Variables", "[variables]")
    {
    double x{ 0 }, y{ 0 }, test{ 0 };

    te_parser tep;
    tep.set_variables_and_functions({ {"x", &x}, {"y", &y}, {"te_st", &test} });
    [[maybe_unused]] auto exprRes = tep.evaluate("cos x + sin y");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == -1);

    exprRes = tep.evaluate("x+x+x-y");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == -1);

    exprRes = tep.evaluate("x*y^3");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == -1);

    exprRes = tep.evaluate("te_st+5");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == -1);

    exprRes = tep.evaluate("xx*y^3");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != -1);

    exprRes = tep.evaluate("tes");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != -1);

    exprRes = tep.evaluate("sinn x");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != -1);

    exprRes = tep.evaluate("si x");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != -1);

    for (y = 2; y < 3; ++y)
        {
        for (x = 0; x < 5; ++x)
            {
            double ev{ 0 };

            ev = tep.evaluate("cos x + sin y");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(cos(x) + sin(y)));

            ev = tep.evaluate("x+x+x-y");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(x+x+x-y));

            ev = tep.evaluate("x*y^3");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(x*y*y*y));

            test = x;
            ev = tep.evaluate("te_st+5");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(x+5));
            }
        }
    }

TEST_CASE("Dynamic", "[dynamic]")
    {
    double x{ 2 }, f{ 5 };
    const std::vector<te_variable> lookup =
        {
        {"x", &x},
        {"f", &f},
        {"sum0", sum0},
        {"sum1", sum1},
        {"sum2", sum2},
        {"sum3", sum3},
        {"sum4", sum4},
        {"sum5", sum5},
        {"sum6", sum6},
        {"sum7", sum7},
        };

    te_parser tep;
    tep.set_variables_and_functions(lookup);

    CHECK(tep.evaluate("x") == 2);
    CHECK(tep.evaluate("f+x") == 7);
    CHECK(tep.evaluate("x+x") == 4);
    CHECK(tep.evaluate("x+f") == 7);
    CHECK(tep.evaluate("f+f") == 10);
    CHECK(tep.evaluate("f+sum0") == 11);
    CHECK(tep.evaluate("sum0+sum0") == 12);
    CHECK(tep.evaluate("sum0()+sum0") == 12);
    CHECK(tep.evaluate("sum0+sum0()") == 12);
    CHECK(tep.evaluate("sum0()+(0)+sum0()") == 12);
    CHECK(tep.evaluate("sum1 sum0") == 12);
    CHECK(tep.evaluate("sum1(sum0)") == 12);
    CHECK(tep.evaluate("sum1 f") == 10);
    CHECK(tep.evaluate("sum1 x") == 4);
    CHECK(tep.evaluate("sum2 (sum0, x)") == 8);
    CHECK(tep.evaluate("sum3 (sum0, x, 2)") == 10);
    CHECK(tep.evaluate("sum2(2,3)") == 5);
    CHECK(tep.evaluate("sum3(2,3,4)") == 9);
    CHECK(tep.evaluate("sum4(2,3,4,5)") == 14);
    CHECK(tep.evaluate("sum5(2,3,4,5,6)") == 20);
    CHECK(tep.evaluate("sum6(2,3,4,5,6,7)") == 27);
    CHECK(tep.evaluate("sum7(2,3,4,5,6,7,8)") == 35);
    }

TEST_CASE("NaN", "[nan]")
    {
    te_parser tep;

    CHECK(std::isinf(tep.evaluate("pow(2,10000000)")));
    CHECK(std::isinf(tep.evaluate("fac(300)")));
    CHECK(std::isinf(tep.evaluate("ncr(300,100)")));
    CHECK(std::isinf(tep.evaluate("ncr(300000,100)")));
    CHECK(std::isinf(tep.evaluate("ncr(300000,100)*8")));
    CHECK(std::isinf(tep.evaluate("npr(3,2)*ncr(300000,100)")));
    CHECK(std::isinf(tep.evaluate("npr(100,90)")));
    CHECK(std::isinf(tep.evaluate("npr(30,25)")));
    CHECK(std::isinf(tep.evaluate("log(0)")));
    }

TEST_CASE("Inf", "[inf]")
    {
    te_parser tep;

    CHECK(std::isnan(tep.evaluate("fac(-1)")));
    CHECK(std::isnan(tep.evaluate("ncr(2, 4)")));
    CHECK(std::isnan(tep.evaluate("ncr(-2, 4)")));
    CHECK(std::isnan(tep.evaluate("ncr(2, -4)")));
    CHECK(std::isnan(tep.evaluate("npr(2, 4)")));
    CHECK(std::isnan(tep.evaluate("npr(-2, 4)")));
    CHECK(std::isnan(tep.evaluate("npr(2, -4)")));
    }

TEST_CASE("Zeros", "[zeros]")
    {
    te_parser tep;

    CHECK_THROWS(tep.evaluate("0/0"));
    CHECK_THROWS(tep.evaluate("1/0"));
    CHECK_THROWS(tep.evaluate("1%0"));
    CHECK_THROWS(tep.evaluate("1%(1%0)"));
    CHECK_THROWS(tep.evaluate("(1%0)%1"));
    }

TEST_CASE("Functions", "[functions]")
    {
    double x{ 0 }, y{ 0 };

    te_parser tep;
    tep.set_variables_and_functions({ {"x", &x}, {"y", &y} });

    for (x = -5; x < 5; x += 0.2)
        {
        CHECK_THAT(tep.evaluate("abs x"), Catch::Matchers::WithinRel(fabs(x)));
        if (!std::isnan(acos(x)))
            CHECK_THAT(tep.evaluate("acos x"), Catch::Matchers::WithinRel(acos(x)));
        else
            CHECK(std::isnan(tep.evaluate("acos x")));
        if (!std::isnan(asin(x)))
            CHECK_THAT(tep.evaluate("asin x"), Catch::Matchers::WithinRel(asin(x)));
        else
            CHECK(std::isnan(tep.evaluate("asin x")));
        CHECK_THAT(tep.evaluate("atan x"), Catch::Matchers::WithinRel(atan(x)));
        CHECK_THAT(tep.evaluate("ceil x"), Catch::Matchers::WithinRel(ceil(x)));
        CHECK_THAT(tep.evaluate("cos x"), Catch::Matchers::WithinRel(cos(x)));
        CHECK_THAT(tep.evaluate("cosh x"), Catch::Matchers::WithinRel(cosh(x)));
        CHECK_THAT(tep.evaluate("exp x"), Catch::Matchers::WithinRel(exp(x)));
        CHECK_THAT(tep.evaluate("floor x"), Catch::Matchers::WithinRel(floor(x)));
        if (!std::isnan(log(x)))
            CHECK_THAT(tep.evaluate("ln x"), Catch::Matchers::WithinRel(log(x)));
        else
            CHECK(std::isnan(tep.evaluate("ln x")));
        if (!std::isnan(log10(x)))
            CHECK_THAT(tep.evaluate("log10 x"), Catch::Matchers::WithinRel(log10(x)));
        else
            CHECK(std::isnan(tep.evaluate("log10 x")));
        CHECK_THAT(tep.evaluate("sin x"), Catch::Matchers::WithinRel(sin(x)));
        CHECK_THAT(tep.evaluate("sinh x"), Catch::Matchers::WithinRel(sinh(x)));
        if (!std::isnan(sqrt(x)))
            CHECK_THAT(tep.evaluate("sqrt x"), Catch::Matchers::WithinRel(sqrt(x)));
        else
            CHECK(std::isnan(tep.evaluate("sqrt x")));
        CHECK_THAT(tep.evaluate("tan x"), Catch::Matchers::WithinRel(tan(x)));
        CHECK_THAT(tep.evaluate("tanh x"), Catch::Matchers::WithinRel(tanh(x)));

        for (y = -2; y < 2; y += 0.2)
            {
            if (fabs(x) < 0.01) break;
            CHECK_THAT(tep.evaluate("atan2(x,y)"), Catch::Matchers::WithinRel(atan2(x, y)));
            if (!std::isnan(pow(x, y)))
                CHECK_THAT(tep.evaluate("pow(x,y)"), Catch::Matchers::WithinRel(pow(x, y)));
            else
                CHECK(std::isnan(tep.evaluate("pow(x,y)")));
            }
        }
    }

TEST_CASE("Power", "[power]")
    {
    const double a{ 2 }, b{ 3 };

    const std::vector<te_variable> lookup = {
        {"a", &a},
        {"b", &b}
    };
    te_parser tep;
    tep.set_variables_and_functions(lookup);

#ifdef TE_POW_FROM_RIGHT
    CHECK(tep.evaluate("2^3^4") == tep.evaluate("2^(3^4)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-2^2") == tep.evaluate("-(2^2)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("--2^2") == tep.evaluate("(2^2)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("---2^2") == tep.evaluate("-(2^2)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-(2*1)^2") == tep.evaluate("-(2^2)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-2^2") == tep.evaluate("-4"));
    CHECK(tep.success());

    CHECK(tep.evaluate("2^1.1^1.2^1.3") == tep.evaluate("2^(1.1^(1.2^1.3))"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-a^b") == tep.evaluate("-(a^b)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-a^-b") == tep.evaluate("-(a^-b)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("1^0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(1)^0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-(2)^2") == tep.evaluate("-(2^2)"));
    CHECK(tep.success());

    /* TODO POW FROM RIGHT IS STILL BUGGY
    {"(-2)^2", "4"},
    {"(-1)^0", "1"},
    {"(-5)^0", "1"},
    {"-2^-3^-4", "-(2^(-(3^-4)))"}*/
#else
    CHECK(tep.evaluate("2^3^4") == tep.evaluate("(2^3)^4"));
    CHECK(tep.success());
    
    CHECK(tep.evaluate("-2^2") == tep.evaluate("(-2)^2"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(-2)^2") == tep.evaluate("4"));
    CHECK(tep.success());

    CHECK(tep.evaluate("--2^2") == tep.evaluate("2^2"));
    CHECK(tep.success());

    CHECK(tep.evaluate("---2^2") == tep.evaluate("(-2)^2"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-2^2") == tep.evaluate("4"));
    CHECK(tep.success());

    CHECK(tep.evaluate("2^1.1^1.2^1.3") == tep.evaluate("((2^1.1)^1.2)^1.3"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-a^b") == tep.evaluate("(-a)^b"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-a^-b") == tep.evaluate("(-a)^(-b)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("1^0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(1)^0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(-1)^0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(-5)^0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-2^-3^-4") == tep.evaluate("((-2)^(-3))^(-4)"));
    CHECK(tep.success());
#endif
    }

TEST_CASE("Syntax Errors", "[syntax]")
    {
    te_parser tep;

    CHECK(tep.evaluate("5+5") == 10);
    CHECK(tep.evaluate("pow(2,2)") == 4);
    CHECK(tep.evaluate("sqrt 100") == 10);
    CHECK_THAT(tep.evaluate("pi * 2"), Catch::Matchers::WithinRel(6.2832, 0.00001));
    }

TEST_CASE("Closure", "[closure]")
    {
    double extra{ 0 };

    te_expr te{ TE_DEFAULT, &extra };
    te_expr_array teArray{ TE_DEFAULT };

    std::vector<te_variable> lookup = {
        {"c0", clo0, TE_DEFAULT, &te},
        {"c1", clo1, TE_DEFAULT, &te},
        {"c2", clo2, TE_DEFAULT, &te},
        {"c3", clo3, TE_DEFAULT, &te},
        {"c4", clo4, TE_DEFAULT, &te},
        {"c5", clo5, TE_DEFAULT, &te},
        {"c6", clo6, TE_DEFAULT, &te},
        {"c7", clo7, TE_DEFAULT, &te},
        {"cell", cell, TE_DEFAULT, &teArray},
    };

    te_parser tep;
    tep.set_variables_and_functions(lookup);

    extra = 0;
    double answer{ 6 };
    [[maybe_unused]] auto res = tep.evaluate("c0");
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

    extra = 10;
    res = tep.evaluate();
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

    SECTION("C1")
        {
        extra = 0;
        answer = 8;
        res = tep.evaluate("c1 4");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C2")
        {
        extra = 0;
        answer = 30;
        res = tep.evaluate("c2 (10, 20)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C3")
        {
        extra = 0;
        answer = 35;
        res = tep.evaluate("c3 (10, 20, 5)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C4")
        {
        extra = 0;
        answer = 37;
        res = tep.evaluate("c4 (10, 20, 5, 2)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C5")
        {
        extra = 0;
        answer = 45;
        res = tep.evaluate("c5 (10, 20, 5, 2, 8)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C6")
        {
        extra = 0;
        answer = 54;
        res = tep.evaluate("c6 (10, 20, 5, 2, 8, 9)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C7")
        {
        extra = 0;
        answer = 58;
        res = tep.evaluate("c7 (10, 20, 5, 2, 8, 9, 4)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    res = tep.evaluate("cell 0");
    CHECK(tep.success());
    CHECK(tep.evaluate() == 5);

    res = tep.evaluate("cell 1");
    CHECK(tep.success());
    CHECK(tep.evaluate() == 6);

    res = tep.evaluate("cell 0 + cell 1");
    CHECK(tep.success());
    CHECK(tep.evaluate() == 11);

    res = tep.evaluate("cell 1 * cell 3 + cell 4");
    CHECK(tep.success());
    CHECK(tep.evaluate() == 57);
    }

TEST_CASE("Constants", "[constants]")
    {
    te_parser tep;
    // could be done via add_var() also
    tep.set_constant("SALARY", 15.25);
    CHECK(tep.evaluate("SALARY") == 15.25);

    tep.set_constant("SALARY", 17.75);
    CHECK(tep.evaluate("SALARY") == 17.75);
    CHECK(tep.get_constant("SALARY") == 17.75);
    }

TEST_CASE("Long names", "[longnames]")
    {
    te_parser p;
    p.set_variables_and_functions(
        {
            { "AddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResult", AddEm }
        });
    p.compile(("AddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResult(1, 2)"));
    CHECK(p.evaluate() == 3.0);
    }

TEST_CASE("Precedence", "[precedence]")
    {
    te_parser p;
    p.compile("5+2-1*31/2-20+21%2*2");
    CHECK_THAT(-26.5, Catch::Matchers::WithinRel(p.evaluate()));
    }

TEST_CASE("Round", "[round]")
    {
    te_parser p;
    p.compile(("round(1.5, 0)"));
    CHECK(2 == p.evaluate());

    p.compile(("round(1.6, 0)"));
    CHECK(2 == p.evaluate());

    p.compile(("round(1.4, 0)"));
    CHECK(1 == p.evaluate());

    p.compile(("rOund(0.0, 0)"));
    CHECK(0 == p.evaluate());

    p.compile(("round(-11.6, 0)"));
    CHECK(-12 == p.evaluate());

    p.compile(("round(-11.5, 0)"));
    CHECK(-12 == p.evaluate());

    p.compile(("round(-11.4, 0)"));
    CHECK(-11 == p.evaluate());

    p.compile(("rouNd(11.6, 0)"));
    CHECK(12 == p.evaluate());

    p.compile(("round(11.5, 0)"));
    CHECK(12 == p.evaluate());

    p.compile(("round(11.4, 0)"));
    CHECK(11 == p.evaluate());
    }

TEST_CASE("Logical operators", "[logic]")
    {
    te_parser p;

    //OR
    p.compile(("0 | 1"));
    CHECK(1 == p.evaluate());
    p.compile(("1 | 1"));
    CHECK(1 == p.evaluate());
    p.compile(("0 | 0"));
    CHECK(0 == p.evaluate());
    //AND
    p.compile(("0 & 1"));
    CHECK(0 == p.evaluate());
    p.compile(("1 | 1"));
    CHECK(1 == p.evaluate());
    p.compile(("0 | 0"));
    CHECK(0 == p.evaluate());
    //equality
    p.compile(("5=5"));
    CHECK(1 == p.evaluate());
    p.compile(("5<>5"));
    CHECK(0 == p.evaluate());
    p.compile(("5.1 <>5"));
    CHECK(1 == p.evaluate());
    //less than
    p.compile(("5.1 < 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5 < 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5.1 < 5.19"));
    CHECK(1 == p.evaluate());
    p.compile(("-6 < 1"));
    CHECK(1 == p.evaluate());
    //less than or equal to
    p.compile(("5.1 <= 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5 <= 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5.1 <= 5.19"));
    CHECK(1 == p.evaluate());
    p.compile(("-6 <= 1"));
    CHECK(1 == p.evaluate());
    //greater than
    p.compile(("5.1 > 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5 > 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5.19 > 5.1"));
    CHECK(1 == p.evaluate());
    p.compile(("1 > -6"));
    CHECK(1 == p.evaluate());
    //greater than or equal to
    p.compile(("5.1 >= 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5 >= 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5.19 >= 5.1"));
    CHECK(1 == p.evaluate());
    p.compile(("1 >= -6"));
    CHECK(1 == p.evaluate());
    }

TEST_CASE("Statistics", "[stats]")
    {
    te_parser p;

    p.compile(("SUM(1, 2, 3, 4)"));
    CHECK(10 == p.evaluate());
    p.compile(("SUM(1.1, 2.7, 3, 4.9)"));
    CHECK_THAT(11.7, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("AVERAGE(1, 2, 3, 4, 5)"));
    CHECK(3 == p.evaluate());
    p.compile(("AVERAGE(1.1, 2.7, 3.2, 4, 5.7)"));
    CHECK_THAT(3.34, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(1.1)"));
    CHECK_THAT(1.1, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(1.1, 1.2)"));
    CHECK_THAT(1.1, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-1, 2)"));
    CHECK_THAT(-1, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-1, 2, 0, -5.8, 9)"));
    CHECK_THAT(-5.8, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-9, 2, 0, -5.8, 9)"));
    CHECK_THAT(-9, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-9, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-9, 2, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-9, 2, 0, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-9, 2, 0, -5.8, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(1.1)"));
    CHECK_THAT(1.1, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(1.1, 1.2)"));
    CHECK_THAT(1.2, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(-1, 2)"));
    CHECK_THAT(2, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(1.1, 1.2, 0, 5.8)"));
    CHECK_THAT(5.8, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(9.1, 1.2, 0, 5.8)"));
    CHECK_THAT(9.1, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(9.1, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(9.1, 1.2, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(9.1, 1.2, 0, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(p.evaluate()));
    }

TEST_CASE("Round higher precision", "[round]")
    {
    te_parser p;

    p.compile(("round(1.55, 1)"));
    CHECK_THAT(1.6, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(-1.55, 1)"));
    CHECK_THAT(-1.6, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(3.1415678, 2)"));
    CHECK_THAT(3.14, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(3.1415678, 3)"));
    CHECK_THAT(3.142, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(3.1415678, 4)"));
    CHECK_THAT(3.1416, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(3.1415678, 5)"));
    CHECK_THAT(3.14157, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(3.1415678, 6)"));
    CHECK_THAT(3.141568, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(3.14156785, 7)"));
    CHECK_THAT(3.141568, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("round(-3.1415678, 6)"));
    CHECK_THAT(-3.141568, Catch::Matchers::WithinRel(p.evaluate()));
    }

TEST_CASE("Math operators", "[math]")
    {
    te_parser p;

    p.compile(("9*3/2+8-2"));
    CHECK_THAT(19.5, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("9*((3/2)+(8-2))"));//change up the order of operations
    CHECK_THAT(67.5, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("9*3^3/2+8-(11%2)"));
    CHECK_THAT(128.5, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("9.2*3.4^3/2+8.7-(11%2)"));
    CHECK_THAT(188.4984, Catch::Matchers::WithinRel(p.evaluate()));
    }

TEST_CASE("Division", "[math]")
    {
    te_parser p;

    p.compile("4/2.2");
    CHECK_THAT(1.81818, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));
    }

TEST_CASE("Modulus", "[math]")
    {
    te_parser p;

    p.compile(("MOD(5,2)"));
    CHECK(1 == p.evaluate());
    CHECK(0 == p.evaluate("MOD(5,2.5)"));
    CHECK(2 == p.evaluate("MOD(5,3)"));
    CHECK(0 == p.evaluate("MOD(5,5)"));
    CHECK(5 == p.evaluate("MOD(5,6)"));
    }

TEST_CASE("Is function used", "[functions]")
    {
    te_parser p;

    p.set_variables_and_functions({
        { "MULT", __mult }
        });
    p.compile(("log(5)+sin(atan(6))-MULT(2,30,4,5)+1"));
    CHECK(p.is_function_used(("MULT")));
    CHECK(p.is_function_used(("Log")));
    CHECK(p.is_function_used(("sin")));
    CHECK(p.is_function_used(("atan")));
    CHECK(p.is_function_used(("MULT")));
    CHECK_FALSE(p.is_function_used(("tan")));
    }

TEST_CASE("Is variable used", "[functions]")
    {
    te_parser p;

    p.set_variables_and_functions({
        {"STRESS_L", 10.1},
        {"P_LEVEL", .5},
        {"z", .75} });
    p.compile(("z + STRESS_L"));
    CHECK(p.is_variable_used(("z")));
    CHECK(p.is_variable_used(("STRESS_L")));
    CHECK_FALSE(p.is_variable_used(("P_LEVEL")));
    }

TEST_CASE("Custom test", "[functions]")
    {
    te_parser p;

    SECTION("Custom test unknown parameters")
        {
        p.set_variables_and_functions({ { "MULT", __mult} });
        p.compile(("MULT(2,30,4,5)+1"));
        CHECK(1201 == p.evaluate());
        }
    SECTION("0 Parameters")
        {
        p.set_variables_and_functions({ {"Return5", return5} });
        p.compile(("Return5()"));
        CHECK_THAT(5, Catch::Matchers::WithinRel(p.evaluate()));
        }
    SECTION("1 Parameter")
        {
        p.set_variables_and_functions({ { "value", __value} });
        p.compile(("value(2.1)"));
        CHECK_THAT(2.1, Catch::Matchers::WithinRel(p.evaluate()));
        }
    SECTION("2 Parameters")
        {
        p.set_variables_and_functions({ { "AddEm", AddEm} });
        p.compile(("ADDEM(2.1, 86.8)"));
        CHECK_THAT(88.9, Catch::Matchers::WithinRel(p.evaluate()));
        }
    SECTION("3 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm3", AddEm3} });
        p.compile(("ADDEM3(2.1, 86.8, 2)"));
        CHECK_THAT(90.9, Catch::Matchers::WithinRel(p.evaluate()));
        }
    SECTION("Custom variables")
        {
        p.set_variables_and_functions({ {"STRESS_L", 10.1},
            {"P_LEVEL", .5} });
        p.compile(("STRESS_L*P_LEVEL"));
        CHECK_THAT(5.05, Catch::Matchers::WithinRel(p.evaluate()));
        p.set_constant("P_LEVEL", .9);
        CHECK_THAT(9.09, Catch::Matchers::WithinRel(p.evaluate()));
        p.compile(("IF(STRESS_L >= P_LEVEL, 1, 0)"));
        CHECK(1 == p.evaluate());
        }
    }

TEST_CASE("Permutation & Combination", "[math]")
    {
    te_parser p;

    // COMB
    p.compile(("COMBIN(15, 3)"));
    CHECK(455 == p.evaluate());
    // PERMUT
    p.compile(("PERMUT(15, 3)"));
    CHECK(2'730 == p.evaluate());
    }

TEST_CASE("Additional math functions", "[math]")
    {
    te_parser p;

    p.compile(("SQR(3)"));
    CHECK_THAT(9, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("SIN(3)"));
    CHECK_THAT(0.141120008, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("COS(7)"));
    CHECK_THAT(.7539, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("TAN(7)"));
    CHECK_THAT(.871447983, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("ATAN(7)"));
    CHECK_THAT(1.42889927, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("SINH(7)"));
    CHECK_THAT(548.316123, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("COSH(1)"));
    CHECK_THAT(1.54308, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("FLOOR(-3.2)"));
    CHECK_THAT(-4, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("FLOOR(3.2)"));
    CHECK_THAT(3, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("CEIL(-3.2)"));
    CHECK_THAT(-3, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("CEIL(3.2)"));
    CHECK_THAT(4, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("TRUNC(-3.2)"));
    CHECK_THAT(-3, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("TRUNC(3.2)"));
    CHECK_THAT(3, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("LOG(10)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("LOG(100)"));
    CHECK_THAT(2, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("LN(10)"));
    CHECK_THAT(2.30258509, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("LN(100)"));
    CHECK_THAT(4.60517019, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("ABS(-2.7)"));
    CHECK_THAT(2.7, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("ABS(68.84)"));
    CHECK_THAT(68.84, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("IF(0, 1, -1)"));
    CHECK_THAT(-1, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("IF(1, 1, -1)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("POW(3, 3)"));
    CHECK_THAT(27, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("POW(3, 0)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("POW(-4, 2)"));
    CHECK_THAT(16, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("SIGN(-85.6)"));
    CHECK_THAT(-1, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("SIGN(89.0)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("SIGN(0)"));
    CHECK_THAT(0, Catch::Matchers::WithinRel(p.evaluate()));

    p.compile(("COT(0.1)"));
    CHECK_THAT(9.9666, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("COT(1.57)"));
    CHECK_THAT(0.0007963, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("EXP(3)"));
    CHECK_THAT(20.085540, Catch::Matchers::WithinRel(p.evaluate(), 0.0001));

    p.compile(("SQRT(9)"));
    CHECK_THAT(3, Catch::Matchers::WithinRel(p.evaluate()));
    p.compile(("SQRT(27.04)"));
    CHECK_THAT(5.2, Catch::Matchers::WithinRel(p.evaluate()));
    }

TEST_CASE("Logical functions", "[logic]")
    {
    te_parser p;

    SECTION("AND")
        {
        p.compile(("AND(1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(1, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(0)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(1, 0)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(0, 1)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(0, 0)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(1, 1, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(1, 1, 1, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(1, 1, 1, 1, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(1, 1, 1, 1, 1, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(1, 1, 1, 1, 1, 1, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("AND(1, 1, 1, 1, 1, 1, 0)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(1, 1, 1, 1, 1, 0, 1)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(1, 1, 1, 1, 0, 1, 1)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(1, 1, 1, 0, 1, 1, 1)"));
        CHECK(0 == p.evaluate());
        p.compile(("AND(1, 1, 0, 1, 1, 1, 1)"));
        CHECK(0 == p.evaluate());
        }

    SECTION("OR")
        {
        p.compile(("OR(1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(1, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0)"));
        CHECK(0 == p.evaluate());
        p.compile(("OR(1, 0)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0, 0)"));
        CHECK(0 == p.evaluate());
        p.compile(("OR(1, 0, 0)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(1, 0, 0, 0)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(1, 0, 0, 0, 0)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(1, 0, 0, 0, 0, 0)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(1, 0, 0, 0, 0, 0, 0)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0, 0, 0, 0, 0, 0, 0)"));
        CHECK(0 == p.evaluate());
        p.compile(("OR(0, 0, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0, 0, 0, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0, 0, 0, 0, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0, 0, 0, 0, 0, 1)"));
        CHECK(1 == p.evaluate());
        p.compile(("OR(0, 0, 0, 0, 0, 0, 1)"));
        CHECK(1 == p.evaluate());
        }
    }

TEST_CASE("Validate variables", "[names]")
    {
    te_parser tep;
    CHECK_THROWS(tep.add_variable_or_function({ "", 5.0 }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "", 5.0 } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Var WithSpace", 5.0 } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Varÿ", 5.0 } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "_Var", 5.0 } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Var$", 5.0 } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Var ", 5.0 } }));

    // should be fine
    CHECK_NOTHROW(tep.set_variables_and_functions({ { "Var_OK74_", 5.0 } }));
    }

TEST_CASE("Clamp", "[clamp]")
    {
    te_parser tep;

    CHECK(tep.evaluate("CLAMP(1, 1, 9)") == 1);
    CHECK(tep.evaluate("CLAMP(0, 1, 9)") == 1);
    CHECK(tep.evaluate("CLAMP(9, 1, 9)") == 9);
    CHECK(tep.evaluate("CLAMP(10, 1, 9)") == 9);
    CHECK(tep.evaluate("CLAMP(4, 1, 9)") == 4);
    CHECK_THROWS(tep.evaluate("CLAMP(4, 10, 9)"));
    }

TEST_CASE("Benchmarks", "[!benchmark]")
    {
    double benchmarkVar{ 9 };
    te_parser tep;
    tep.set_variables_and_functions({ {"a", &benchmarkVar} });

    BENCHMARK("a+5 Compiled")
        { return tep.evaluate("a+5"); };
    BENCHMARK("a+5 Native")
        { return bench_a5(benchmarkVar); };

    BENCHMARK("5+a+5 Compiled")
        { return tep.evaluate("5+a+5"); };
    BENCHMARK("5+a+5 Native")
        { return bench_a55(benchmarkVar); };

    BENCHMARK("abs(a+5) Compiled")
        { return tep.evaluate("abs(a+5)"); };
    BENCHMARK("abs(a+5) Native")
        { return bench_a5abs(benchmarkVar); };

    BENCHMARK("sqrt(a^1.5+a^2.5) Compiled")
        { return tep.evaluate("sqrt(a^1.5+a^2.5)"); };
    BENCHMARK("sqrt(a^1.5+a^2.5) Native")
        { return bench_as(benchmarkVar); };

    BENCHMARK("a+(5*2) Compiled")
        { return tep.evaluate("a+(5*2)"); };
    BENCHMARK("a+(5*2) Native")
        { return bench_a10(benchmarkVar); };

    BENCHMARK("(a+5)*2 Compiled")
        { return tep.evaluate("(a+5)*2"); };
    BENCHMARK("(a+5)*2 Native")
        { return bench_a52(benchmarkVar); };

    BENCHMARK("(1/(a+1)+2/(a+2)+3/(a+3)) Compiled")
        { return tep.evaluate("(1/(a+1)+2/(a+2)+3/(a+3))"); };
    BENCHMARK("(1/(a+1)+2/(a+2)+3/(a+3)) Native")
        { return bench_al(benchmarkVar); };
    }

TEST_CASE("Random", "[random]")
    {
    te_parser tep;
    // can't have reproducible results for rand, so just run it and make
    // sure it doesn't crash
    CHECK_NOTHROW(tep.evaluate("rand()"));
    }
}
