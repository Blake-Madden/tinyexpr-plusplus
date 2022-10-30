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

class te_expr_array : public te_expr
{
public:
    te_expr_array(const variable_flags type) noexcept : te_expr(type) {}
    std::array<double, 5> m_data = { 5,6,7,8,9 };
};

double cell(const te_expr* context, double a) {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    return c->m_data[(int)a];
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
    tep.set_vars({ {"x", &x}, {"y", &y}, {"te_st", &test} });
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
    tep.set_vars(lookup);

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
    tep.set_vars({ {"x", &x}, {"y", &y} });

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
    tep.set_vars(lookup);

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
        {"cell", cell, TE_DEFAULT, &teArray},
    };

    te_parser tep;
    tep.set_vars(lookup);

    extra = 0;
    double answer{ 6 };
    [[maybe_unused]] auto res = tep.evaluate("c0");
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

    extra = 10;
    res = tep.evaluate();
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

    extra = 0;
    answer = 8;
    res = tep.evaluate("c1 4");
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

    extra = 10;
    res = tep.evaluate();
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

    extra = 0;
    answer = 30;
    res = tep.evaluate("c2 (10, 20)");
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

    extra = 10;
    res = tep.evaluate();
    CHECK(tep.success());
    CHECK(tep.evaluate() == answer + extra);

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