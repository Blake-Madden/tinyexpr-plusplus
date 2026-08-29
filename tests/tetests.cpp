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
 * Copyright (c) 2020-2026 Blake Madden
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
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <clocale>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <memory>
#include <regex>
#include <string>
#include <vector>

// clang-format off
// NOLINTBEGIN
#ifdef TE_LONG_DOUBLE
    #define WITHIN_TYPE_CAST(x) (double)((x))
    #define WITHIN_TYPE double
#else
    #define WITHIN_TYPE_CAST(x) (te_type)((x))
    #define WITHIN_TYPE te_type
#endif
namespace TETesting
{
te_type sum0() {
    return 6;
}
te_type sum1(te_type a) {
    return a * 2;
}
te_type sum2(te_type a, te_type b) {
    return a + b;
}
te_type sum3(te_type a, te_type b, te_type c) {
    return a + b + c;
}
te_type sum4(te_type a, te_type b, te_type c, te_type d) {
    return a + b + c + d;
}
te_type sum5(te_type a, te_type b, te_type c, te_type d, te_type e) {
    return a + b + c + d + e;
}
te_type sum6(te_type a, te_type b, te_type c, te_type d, te_type e, te_type f) {
    return a + b + c + d + e + f;
}
te_type sum7(te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g) {
    return a + b + c + d + e + f + g;
}

te_type clo0(const te_expr* context) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + 6;
    return 6;
}
te_type clo1(const te_expr* context, te_type a) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a * 2;
    return a * 2;
}
te_type clo2(const te_expr* context, te_type a, te_type b) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b;
    return a + b;
}

te_type clo3(const te_expr* context, te_type a, te_type b, te_type c) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c;
    return a + b + c;
}

te_type clo4(const te_expr* context, te_type a, te_type b, te_type c, te_type d) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d;
    return a + b + c + d;
}

te_type clo5(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e;
    return a + b + c + d + e;
}

te_type clo6(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f;
    return a + b + c + d + e + f;
}

te_type clo7(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g;
    return a + b + c + d + e + f + g;
}

te_type clo8(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
             te_type h) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h;
    return a + b + c + d + e + f + g + h;
}

te_type clo9(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
             te_type h, te_type i) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i;
    return a + b + c + d + e + f + g + h + i;
}

te_type clo10(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j;
    return a + b + c + d + e + f + g + h + i + j;
}

te_type clo11(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k;
    return a + b + c + d + e + f + g + h + i + j + k;
}

te_type clo12(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l;
    return a + b + c + d + e + f + g + h + i + j + k + l;
}

te_type clo13(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l + m;
    return a + b + c + d + e + f + g + h + i + j + k + l + m;
}

te_type clo14(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l + m + n;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n;
}

te_type clo15(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o;
}

te_type clo16(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o, te_type p) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p;
}

te_type clo17(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o, te_type p,
              te_type q) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q;
}

te_type clo18(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o, te_type p,
              te_type q, te_type r) {
    if (context) return *(std::get<const te_type*>(context->m_value)) +
                     a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r;
}

te_type clo19(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o, te_type p,
              te_type q, te_type r, te_type s) {
    if (context) return *(std::get<const te_type*>(context->m_value)) +
                     a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s;
}

te_type clo20(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o, te_type p,
              te_type q, te_type r, te_type s, te_type t) {
    if (context) return *(std::get<const te_type*>(context->m_value)) +
                     a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t;
}

te_type clo21(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o, te_type p,
              te_type q, te_type r, te_type s, te_type t, te_type u) {
    if (context) return *(std::get<const te_type*>(context->m_value)) +
                     a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u;
}

te_type clo22(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
              te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n, te_type o, te_type p,
              te_type q, te_type r, te_type s, te_type t, te_type u, te_type v) {
    if (context) return *(std::get<const te_type*>(context->m_value)) +
                     a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v;
}

te_type clo23(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
             te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n,
             te_type o, te_type p, te_type q, te_type r, te_type s, te_type t, te_type u,
             te_type v, te_type w) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w;
}


te_type clo24(const te_expr* context, te_type a, te_type b, te_type c, te_type d, te_type e, te_type f, te_type g,
             te_type h, te_type i, te_type j, te_type k, te_type l, te_type m, te_type n,
             te_type o, te_type p, te_type q, te_type r, te_type s, te_type t, te_type u,
             te_type v, te_type w, te_type x ) {
    if (context) return *(std::get<const te_type*>(context->m_value)) + a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x;
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x;
}

inline te_type AddEm(const te_type a, const te_type b){
    return a+b;
}

inline te_type AddEm3(const te_type a, const te_type b, const te_type c){
    return a+b+c;
}

inline te_type AddEm4(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4){
    return v1 + v2 +
    v3 + v4;
}

inline te_type AddEm5(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5){
    return v1 + v2 +
    v3 + v4 + v5;
}

inline te_type AddEm6(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6){
    return v1 + v2 +
    v3 + v4 + v5 + v6;
}

inline te_type AddEm7(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7;
}

inline te_type AddEm8(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8;
}

inline te_type AddEm9(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9;
}

inline te_type AddEm10(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10;
}


inline te_type AddEm11(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11;
}

inline te_type AddEm12(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12;
}

inline te_type AddEm13(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13;
}

inline te_type AddEm14(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14;
}

inline te_type AddEm15(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15;
}

inline te_type AddEm16(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16;
}

inline te_type AddEm17(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17;
}

inline te_type AddEm18(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17, const te_type v18){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17 + v18;
}

inline te_type AddEm19(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17, const te_type v18, const te_type v19){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17 + v18 + v19;
}

inline te_type AddEm20(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17, const te_type v18, const te_type v19, const te_type v20){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17 + v18 + v19 + v20;
}

inline te_type AddEm21(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17, const te_type v18, const te_type v19, const te_type v20, const te_type v21){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17 + v18 + v19 + v20 + v21;
}

inline te_type AddEm22(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17, const te_type v18, const te_type v19, const te_type v20, const te_type v21, const te_type v22){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17 +v18 + v19 + v20 + v21 + v22;
}

inline te_type AddEm23(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17, const te_type v18, const te_type v19, const te_type v20, const te_type v21, const te_type v22, const te_type v23){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17 +v18 + v19 + v20 + v21 + v22 + v23;
}

inline te_type AddEm24(const te_type v1, const te_type v2,
    const te_type v3, const te_type v4, const te_type v5, const te_type v6, const te_type v7, const te_type v8, const te_type v9, const te_type v10,
    const te_type v11, const te_type v12, const te_type v13, const te_type v14, const te_type v15, const te_type v16, const te_type v17, const te_type v18, const te_type v19, const te_type v20, const te_type v21, const te_type v22, const te_type v23, const te_type v24){
    return v1 + v2 +
    v3 + v4 + v5 + v6 + v7 + v8 + v9 + v10 + v11 + v12 + v13 + v14 + v15 + v16 + v17 +v18 + v19 + v20 + v21 +  v22 + v23 + v24;
}

inline te_type __value(const te_type a){
    return a;
}

inline te_type return5(){
    return 5;
}

inline te_type __mult(const te_type a, const te_type b, const te_type c, const te_type d){
    return a*b*c*d;
}

class te_expr_array : public te_expr
    {
public:
    explicit te_expr_array(const te_variable_flags type) noexcept :
        te_expr(type) {}
    std::array<te_type, 5> m_data = { 5, 6, 7, 8, 9 };
    };

// Returns the value of a cell from the object's data.
te_type cell(const te_expr* context, te_type a)
    {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    return static_cast<te_type>(c->m_data[static_cast<size_t>(a)]);
    }

// Returns the max value object's data.
te_type cell_max(const te_expr* context)
    {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    return static_cast<te_type>(
        *std::max_element(c->m_data.cbegin(), c->m_data.cend()));
    }

// Records what the last te_arg_fun call actually received.
std::vector<te_arg> lastArgs;

// Length of the first argument if it's a string, plus any numeric arguments.
te_type str_len_plus(std::span<const te_arg> args)
    {
    lastArgs.assign(args.begin(), args.end());
    if (args.empty() || !std::holds_alternative<std::string_view>(args[0]))
        { return te_parser::te_nan; }
    te_type result = static_cast<te_type>(std::get<std::string_view>(args[0]).length());
    for (size_t i = 1; i < args.size(); ++i)
        {
        if (!std::holds_alternative<te_type>(args[i]))
            { return te_parser::te_nan; }
        result += std::get<te_type>(args[i]);
        }
    return result;
    }

// Requires exactly two arguments, so wrong arity is observable.
te_type str_pair(std::span<const te_arg> args)
    {
    if (args.size() != 2 ||
        !std::holds_alternative<std::string_view>(args[0]) ||
        !std::holds_alternative<te_type>(args[1]))
        { return te_parser::te_nan; }
    return static_cast<te_type>(std::get<std::string_view>(args[0]).length()) *
           std::get<te_type>(args[1]);
    }

// Concatenated lengths of every string argument, ignoring position.
te_type str_total(std::span<const te_arg> args)
    {
    te_type total{ 0 };
    for (const auto& arg : args)
        {
        if (const auto* sv = std::get_if<std::string_view>(&arg); sv != nullptr)
            { total += static_cast<te_type>(sv->length()); }
        else
            { total += std::get<te_type>(arg); }
        }
    return total;
    }

// Not TE_PURE, so it must be re-evaluated rather than folded.
int strCallCount{ 0 };
te_type str_counted(std::span<const te_arg> args)
    {
    ++strCallCount;
    if (args.size() != 1 || !std::holds_alternative<std::string_view>(args[0]))
        { return te_parser::te_nan; }
    return static_cast<te_type>(std::get<std::string_view>(args[0]).length());
    }

// Read a value out of a (mock) database by its path.
te_type db_query(std::span<const te_arg> args)
    {
    // the "database"
    static const std::array<std::pair<std::string_view, te_type>, 3> db{ {
        { "/Equipment/Temp", 21.5 },
        { "/Equipment/Pressure", 101.3 },
        { "/Equipment/Humidity", 44 } } };

    if (args.empty() || args.size() > 2 ||
        !std::holds_alternative<std::string_view>(args[0]))
        { return te_parser::te_nan; }

    const auto path = std::get<std::string_view>(args[0]);
    const auto found = std::find_if(db.cbegin(), db.cend(),
        [path](const auto& entry) { return entry.first == path; });
    if (found == db.cend())
        {
        // optional second argument is the default for a missing key
        if (args.size() == 2 && std::holds_alternative<te_type>(args[1]))
            { return std::get<te_type>(args[1]); }
        return te_parser::te_nan;
        }
    return found->second;
    }

// The same lookup, but against a client object rather than a static table.
class te_database : public te_expr
    {
public:
    explicit te_database(const te_variable_flags type) noexcept : te_expr(type) {}
    std::array<std::pair<std::string_view, te_type>, 2> m_rows{ {
        { "voltage", 240 },
        { "current", 13 } } };
    mutable int m_readCount{ 0 };
    };

te_type query_db(const te_expr* context, std::span<const te_arg> args)
    {
    auto* db = dynamic_cast<const te_database*>(context);
    if (db == nullptr || args.size() != 1 ||
        !std::holds_alternative<std::string_view>(args[0]))
        { return te_parser::te_nan; }
    ++db->m_readCount;
    const auto key = std::get<std::string_view>(args[0]);
    const auto found = std::find_if(db->m_rows.cbegin(), db->m_rows.cend(),
        [key](const auto& row) { return row.first == key; });
    return (found == db->m_rows.cend()) ? te_parser::te_nan : found->second;
    }

// te_arg_confun: indexes the context object's array by a named "cell."
te_type cell_named(const te_expr* context, std::span<const te_arg> args)
    {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    if (c == nullptr || args.size() != 1 ||
        !std::holds_alternative<std::string_view>(args[0]))
        { return te_parser::te_nan; }
    const auto name = std::get<std::string_view>(args[0]);
    if (name == "first") { return static_cast<te_type>(c->m_data.front()); }
    if (name == "last") { return static_cast<te_type>(c->m_data.back()); }
    return te_parser::te_nan;
    }

// te_arg_confun taking a mix of strings and numbers.
te_type cell_offset(const te_expr* context, std::span<const te_arg> args)
    {
    auto* c = dynamic_cast<const te_expr_array*>(context);
    if (c == nullptr || args.size() != 2 ||
        !std::holds_alternative<std::string_view>(args[0]) ||
        !std::holds_alternative<te_type>(args[1]))
        { return te_parser::te_nan; }
    const auto name = std::get<std::string_view>(args[0]);
    const auto offset = static_cast<size_t>(std::get<te_type>(args[1]));
    if (name != "cell" || offset >= c->m_data.size()) { return te_parser::te_nan; }
    return static_cast<te_type>(c->m_data[offset]);
    }

te_type bench_a5(te_type a) {
    return a+5;
}

te_type bench_a55(te_type a) {
    return 5+a+5;
}

te_type bench_a5abs(te_type a) {
    return fabs(a+5);
}

te_type bench_a52(te_type a) {
    return (a+5)*2;
}

te_type bench_a10(te_type a) {
    return a+(5*2);
}

te_type bench_as(te_type a) {
    return static_cast<te_type>(std::sqrt(std::pow(a, 1.5) + std::pow(a, 2.5)));
}

te_type bench_al(te_type a) {
    return (1/(a+1)+2/(a+2)+3/(a+3));
}

TEST_CASE("Main tests", "[main]")
    {
    te_parser tep;

    CHECK(tep.evaluate("1") == 1);
    CHECK(tep.evaluate("1 ") == 1);
    CHECK(tep.evaluate("(1)") == 1);

    CHECK_THAT(tep.evaluate("pi"), Catch::Matchers::WithinRel(3.14159, 0.00001));
    CHECK((int)tep.evaluate("atan(1)*4 - pi") == 0);
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

    // check ranges
    CHECK(std::isnan(tep.evaluate("asin(1.01)")));
    CHECK(std::isnan(tep.evaluate("asin(-1.01)")));
    CHECK(tep.get_last_error_message() == "Argument passed to ASIN must be between -1 and 1.");
    CHECK(tep.evaluate("asin(1)") == std::asin(static_cast<te_type>(1.0)));
    CHECK(tep.get_last_error_message().empty());
    CHECK(tep.success());
    CHECK(tep.evaluate("asin(-1)") == std::asin(static_cast<te_type>(-1.0)));
    CHECK(tep.get_last_error_message().empty());
    CHECK(tep.success());

    CHECK_THAT(tep.evaluate("asin sin .5"), Catch::Matchers::WithinRel(0.5, 0.00001));
    CHECK_THAT(tep.evaluate("sin asin .5"), Catch::Matchers::WithinRel(0.5, 0.00001));
    CHECK_THAT(tep.evaluate("ln exp .5"), Catch::Matchers::WithinRel(0.5, 0.00001));
    CHECK_THAT(tep.evaluate("exp ln .5"), Catch::Matchers::WithinRel(0.5, 0.00001));

    CHECK_THAT(tep.evaluate("asin sin-.5"), Catch::Matchers::WithinRel(-0.5, 0.00001));
    CHECK_THAT(tep.evaluate("asin sin-0.5"), Catch::Matchers::WithinRel(-0.5, 0.00001));
    CHECK_THAT(tep.evaluate("asin sin -0.5"), Catch::Matchers::WithinRel(-0.5, 0.00001));
    CHECK_THAT(tep.evaluate("asin (sin -0.5)"), Catch::Matchers::WithinRel(-0.5, 0.00001));
    CHECK_THAT(tep.evaluate("asin (sin (-0.5))"), Catch::Matchers::WithinRel(-0.5, 0.00001));
    CHECK_THAT(tep.evaluate("asin sin (-0.5)"), Catch::Matchers::WithinRel(-0.5, 0.00001));
    CHECK_THAT(tep.evaluate("(asin sin (-0.5))"), Catch::Matchers::WithinRel(-0.5, 0.00001));

    CHECK_THAT(tep.evaluate("log10 1000"), Catch::Matchers::WithinRel(3, 0.00001));
    CHECK_THAT(tep.evaluate("log10 1e3"), Catch::Matchers::WithinRel(3, 0.00001));
    CHECK_THAT(tep.evaluate("log10 1000"), Catch::Matchers::WithinRel(3, 0.00001));
    CHECK_THAT(tep.evaluate("log10 1e3"), Catch::Matchers::WithinRel(3, 0.00001));
    CHECK_THAT(tep.evaluate("log10(1000)"), Catch::Matchers::WithinRel(3, 0.00001));
    CHECK_THAT(tep.evaluate("log10(1e3)"), Catch::Matchers::WithinRel(3, 0.00001));
    CHECK_THAT(tep.evaluate("log10 1.0e3"), Catch::Matchers::WithinRel(3, 0.00001));
#ifndef TE_BITWISE_OPERATORS
    CHECK_THAT(tep.evaluate("10^5*5e-5"), Catch::Matchers::WithinRel(5, 0.00001));
#endif
    CHECK_THAT(tep.evaluate("10**5*5e-5"), Catch::Matchers::WithinRel(5, 0.00001));

    CHECK_THAT(tep.evaluate("ln 1000"), Catch::Matchers::WithinRel(6.9078, 0.00001));
    CHECK_THAT(tep.evaluate("ln e"), Catch::Matchers::WithinRel(1.0, 0.00001));
    CHECK(tep.evaluate("ln(exp(3))") == 3);
    CHECK_THAT(tep.evaluate("ln(2.7182818)"), Catch::Matchers::WithinRel(1.0, 0.00001));
    CHECK_THAT(tep.evaluate("ln(86)"), Catch::Matchers::WithinRel(4.454373, 0.00001));
#ifndef TE_BITWISE_OPERATORS
    CHECK_THAT(tep.evaluate("ln (e^10)"), Catch::Matchers::WithinRel(10, 0.00001));
    CHECK_THAT(tep.evaluate("ln (e^10)"), Catch::Matchers::WithinRel(10, 0.00001));
    CHECK(tep.evaluate("100^.5+1") == 11);
    CHECK(tep.evaluate("100 ^.5+1") == 11);
    CHECK(tep.evaluate("100^+.5+1") == 11);
    CHECK(tep.evaluate("100^--.5+1") == 11);
    CHECK(tep.evaluate("100^---+-++---++-+-+-.5+1") == 11);

    CHECK_THAT(tep.evaluate("100^-.5+1"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(static_cast<te_type>(1.1)), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("100^---.5+1"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(static_cast<te_type>(1.1)), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("100^+---.5+1"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(static_cast<te_type>(1.1)), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("1e2^+---.5e0+1e0"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(static_cast<te_type>(1.1)), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("--(1e2^(+(-(-(-.5e0))))+1e0)"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(static_cast<te_type>(1.1)), WITHIN_TYPE(0.00001)));
#endif
    CHECK_THAT(tep.evaluate("ln (e**10)"), Catch::Matchers::WithinRel(10, 0.00001));
    CHECK_THAT(tep.evaluate("ln (e**10)"), Catch::Matchers::WithinRel(10, 0.00001));
    CHECK(tep.evaluate("100**.5+1") == 11);
    CHECK(tep.evaluate("100 **.5+1") == 11);
    CHECK(tep.evaluate("100**+.5+1") == 11);
    CHECK(tep.evaluate("100**--.5+1") == 11);
    CHECK(tep.evaluate("100**---+-++---++-+-+-.5+1") == 11);

    CHECK_THAT(tep.evaluate("100**-.5+1"), Catch::Matchers::WithinRel(static_cast<te_type>(1.1), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("100**---.5+1"), Catch::Matchers::WithinRel(static_cast<te_type>(1.1), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("100**+---.5+1") , Catch::Matchers::WithinRel(static_cast<te_type>(1.1), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("1e2**+---.5e0+1e0"), Catch::Matchers::WithinRel(static_cast<te_type>(1.1), WITHIN_TYPE(0.00001)));
    CHECK_THAT(tep.evaluate("--(1e2**(+(-(-(-.5e0))))+1e0)"), Catch::Matchers::WithinRel(static_cast<te_type>(1.1), WITHIN_TYPE(0.00001)));

    CHECK(tep.evaluate("sqrt 100 + 7") == 17);
    CHECK(tep.evaluate("sqrt 100 * 7") == 70);
    CHECK(tep.evaluate("sqrt (100 * 100)") == 100);
    CHECK(tep.evaluate("sqrt(9)") == 3);
    CHECK(std::isnan(tep.evaluate("sqrt(-9)")));
    CHECK(tep.get_last_error_message() == "Negative value passed to SQRT.");

    CHECK(tep.evaluate("1,2") == 2);
    CHECK(tep.evaluate("1,2+1") == 3);
    CHECK(tep.evaluate("1+1,2+2,2+1") == 3);
    CHECK(tep.evaluate("1,2,3") == 3);
    CHECK(tep.evaluate("(1,2),3") == 3);
    CHECK(tep.evaluate("1,(2,3)") == 3);
    CHECK(tep.evaluate("-(1,(2,3))") == -3);

#ifndef TE_BITWISE_OPERATORS
    CHECK(tep.evaluate("2^2") == 4);
#endif
    CHECK(tep.evaluate("2**2") == 4);
    CHECK(tep.evaluate("2 ** 2") == 4);
    CHECK(tep.evaluate("pow(2,2)") == 4);

    CHECK_THAT(tep.evaluate("atan2(1,1)"), Catch::Matchers::WithinRel(0.7854, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(1,2)"), Catch::Matchers::WithinRel(0.46364, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(2,1)"), Catch::Matchers::WithinRel(1.1071, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(3,4)"), Catch::Matchers::WithinRel(0.6435, 0.00001));
    CHECK_THAT(tep.evaluate("atan2(3+3,4*2)"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK_THAT(tep.evaluate("atan2(3+3,(4*2))"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK_THAT(tep.evaluate("atan2((3+3),4*2)"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK_THAT(tep.evaluate("atan2((3+3),(4*2))"), Catch::Matchers::WithinRel(0.6435, 0.0001));
    CHECK_THAT(tep.evaluate("tgamma (0.500000)"), Catch::Matchers::WithinRel(1.772454, 0.0001));
    CHECK_THAT(tep.evaluate("tgamma (10)"), Catch::Matchers::WithinRel(362880, 0.0001));
    CHECK_THAT(tep.evaluate("tgamma (1)"), Catch::Matchers::WithinRel(1, 0.0001));
    CHECK(std::isnan(tep.evaluate("tgamma (-1)")));
    CHECK(tep.evaluate("max(9, 7)") == 9);
    CHECK(tep.evaluate("min(9, 7)") == 7);
    CHECK(tep.evaluate("mod(12, 10)") == 2);
    CHECK(tep.evaluate("sign(-7.9)") == -1);
    CHECK(tep.evaluate("sign(7.9)") == 1);
    CHECK(tep.evaluate("sign(0)") == 0);
    CHECK(tep.evaluate("trunc(9.57878423)") == 9);
    CHECK(tep.evaluate("trunc(9.3)") == 9);
#ifndef TE_BITWISE_OPERATORS
    CHECK(tep.evaluate("2**4") == 16);
#endif
    CHECK(tep.evaluate("1+2**4") == 17);

#ifndef TE_BITWISE_OPERATORS
    CHECK(tep.evaluate("1+2^4") == 17);
#endif
    CHECK(tep.evaluate("(1+2)**4") == 81);
#ifndef TE_BITWISE_OPERATORS
    CHECK(tep.evaluate("(1+2)^4") == 81);
#endif
    CHECK(tep.evaluate("(1+2)**4") == 81);

    SECTION("variadic functions")
        {
        CHECK(tep.evaluate("round(9.57878423, 0)") == 10);
        CHECK(tep.evaluate("round(9.57878423)") == 10);
        CHECK(tep.evaluate("round(pow(2,2))") == 4);
        // non-variadic function inside of variadic
        CHECK_THAT(tep.evaluate("round(9.57878423, 1)"), Catch::Matchers::WithinRel(static_cast<te_type>(9.6), WITHIN_TYPE(0.0001)));
        CHECK_THAT(tep.evaluate("round(9.57878423, 2)"), Catch::Matchers::WithinRel(static_cast<te_type>(9.58), WITHIN_TYPE(0.0001)));
        CHECK_THAT(tep.evaluate("round(9.57878423, 3)"), Catch::Matchers::WithinRel(static_cast<te_type>(9.579), WITHIN_TYPE(0.0001)));
        CHECK(tep.evaluate("sum(9)") == 9);
        CHECK(tep.evaluate("sum(9,9)") == 18);
        CHECK(tep.evaluate("sum(9,9,9)") == 27);
        CHECK(tep.evaluate("sum(9,9,9,9)") == 36);
        CHECK(tep.evaluate("sum(9,9,9,9,9)") == 45);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9)") == 54);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8)") == 62);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4)") == 66);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7)") == 73);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1)") == 74);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4)") == 70);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10)") == 60);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8)") == 68);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5)") == 73);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7)") == 80);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9)") == 89);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11)") == 100);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11, 23)") == 123);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11, 23, 17)") == 140);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11, 23, 17, 50)") == 190);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11, 23, 17, 50, -90)") == 100);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11, 23, 17, 50, -90, 100)") == 200);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11, 23, 17, 50, -90, 100, -100)") == 100);
        CHECK(tep.evaluate("sum(9,9,9,9,9,9,8,4,7,1,-4,-10, 8, 5, 7,9,11, 23, 17, 50, -90, 100, -100, -50)") == 50);
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
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8)") == 4.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9)") == 5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10)") == 5.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11)") == 6);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12)") == 6.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13)") == 7);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14)") == 7.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)") == 8);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)") == 8.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17)") == 9);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18)") == 9.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19)") == 10);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20)") == 10.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21)") == 11);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22)") == 11.5);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23)") == 12);
        CHECK(tep.evaluate("average(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24)") == 12.5);
        }
    }

TEST_CASE("Logic & Operators", "[main]")
    {
    te_parser tep;

    SECTION("logical")
        {
        CHECK(te_parser::number_to_bool(2));
        CHECK(te_parser::number_to_bool((WITHIN_TYPE)22.1));
        CHECK(te_parser::number_to_bool(-2));
        CHECK_FALSE(te_parser::number_to_bool(0));
        CHECK_FALSE(te_parser::number_to_bool(0.0));
        CHECK_FALSE(te_parser::number_to_bool(te_parser::te_nan));

        CHECK(tep.evaluate("if(1, 9, 7)") == 9);
        CHECK(tep.evaluate("if(0, 9, 7)") == 7);
        CHECK(tep.evaluate("if(0.000001 /* non-zero means true */, 9, 7)") == 9);

        // no evaluation statement returns NaN
        CHECK(std::isnan(tep.evaluate("IFS()")));
        CHECK(std::isnan(tep.evaluate("IFS(0, 9)")));
        CHECK(std::isnan(tep.evaluate("IFS(0.000, 9)")));
        CHECK(std::isnan(tep.evaluate("IFS(FALSE, 9)")));
        CHECK(tep.evaluate("IFS(true, 9, 0.0, 7, 1, 5)") == 9);
        CHECK(tep.evaluate("IFS(FALSE, 9, TRUE, 7)") == 7);
        CHECK(tep.evaluate("IFS(FALSE, 9, 0.0, 7, 1, 5)") == 5);
        CHECK(tep.evaluate("IFS(FALSE, 9, 0.0, 7, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, 0.0, 7, 0, 8, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, 0.0, 7, 0, 8, 0, 8, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, FALSE, 9, 0.0, 7, 0, 8, 0, 8, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, FALSE, 9, FALSE, 9, 0.0, 7, 0, 8, 0, 8, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, 0.0, 7, 0, 8, 0, 8, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, 0.0, 7, 0, 8, 0, 8, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, 0.0, 7, 0, 8, 0, 8, 0, 5, TRUE, 86)") == 86);
        CHECK(tep.evaluate("IFS(FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, FALSE, 9, 0.0, 7, 0, 8, 0, 8, 0, 5, TRUE, 86)") == 86);
        // complex expressions
        CHECK(tep.evaluate("IFS(9 > 1, 9, 0.0, 7, 1, 5)") == 9);
        CHECK(tep.evaluate("IFS(9 > 10, 9, 6 > 9, 6, AND(1 > 0, 1 > -1), 1)") == 1);
        // all three expressions are false, so returns NaN
        CHECK(std::isnan(tep.evaluate("IFS(false, 9, false, 7, false, 5)")));
        // not enough args, so NaN is the default value for the last expression
        CHECK(std::isnan(tep.evaluate("IFS(FALSE, 9, 0.0, 7, 1)")));
        // NaN "condition" returns NaN
        CHECK(std::isnan(tep.evaluate("IFS(NAN, 9)")));

        CHECK_FALSE(tep.evaluate("and(0.0, 5)"));
        CHECK_FALSE(tep.evaluate("and(0.0, 0)"));
        CHECK(tep.evaluate("AND(-1, 5)") == 1);
        CHECK(tep.evaluate("AND(1, 1)") == 1);
        CHECK(tep.evaluate("AND(5, 2)") == 1);
        CHECK_FALSE(tep.evaluate("AND(5, 0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK_FALSE(tep.evaluate("AND(5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0)"));
        CHECK(tep.evaluate("or(-1, 0.0)") == 1);
        CHECK(tep.evaluate("or(0.0, 5)") == 1);
        CHECK_FALSE(tep.evaluate("or(0.0, 0)"));
        CHECK(tep.evaluate("OR(-1, 5)") == 1);
        CHECK(tep.evaluate("OR(1, 1)") == 1);
        CHECK(tep.evaluate("OR(0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK(tep.evaluate("OR(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)") == 1);
        CHECK_FALSE(tep.evaluate("not(-1)"));
        CHECK(tep.evaluate("not(0.0)") == 1);
        CHECK(tep.evaluate("NOT(0)") == 1);
        CHECK_FALSE(tep.evaluate("NOT(5)"));
        CHECK(std::isnan(tep.evaluate("NOT(NAN)")));
        CHECK(tep.evaluate("NOT(FALSE)"));
        CHECK_FALSE(tep.evaluate("NOT(TRUE)"));
        CHECK_FALSE(tep.evaluate("NOT(1+1=2)"));
        CHECK(tep.evaluate("NOT(2+2=5)"));
        CHECK(tep.evaluate("NOT(50>100)"));
        CHECK(-1 == tep.evaluate("IF(AND(NOT(50>1),NOT(50<100)),50,-1)"));
        CHECK(100 == tep.evaluate("=IF(OR(NOT(100<0),NOT(100>50)),100,-1)"));

        // garbage values
#ifndef TE_BITWISE_OPERATORS
        CHECK_FALSE(tep.evaluate("NAN & 5"));
        CHECK_FALSE(tep.evaluate("1 & NAN"));
        CHECK(std::isnan(tep.evaluate("NAN & NAN")));
        CHECK(std::isnan(tep.evaluate("NAN | NAN")));
        CHECK(tep.evaluate("NAN | 5") == 1);
        CHECK(tep.evaluate("1 | NAN") == 1);
#endif
        CHECK_FALSE(tep.evaluate("NAN && 5"));
        CHECK_FALSE(tep.evaluate("1 && NAN"));
        CHECK(std::isnan(tep.evaluate("NAN && NAN")));
        CHECK(std::isnan(tep.evaluate("NAN || NAN")));
        CHECK(tep.evaluate("NAN || 5") == 1);
        CHECK(tep.evaluate("1 || NAN") == 1);

        CHECK(tep.evaluate("IF(NAN, 9, 7)") == 7);

        CHECK(tep.evaluate("OR(NAN, NAN)"));
        CHECK(tep.evaluate("OR(NAN, 5)"));

        // at least first value must be legit
        CHECK(std::isnan(tep.evaluate("AND(NAN, NAN)")));
        // NaN values are ignored
        CHECK(tep.evaluate("AND(5, NAN)") == 1);
        CHECK(tep.evaluate("AND(5, 1, NAN, 5)") == 1);
        CHECK_FALSE(tep.evaluate("AND(5, 0, NAN)"));
        }

    SECTION("operators")
        {
#ifndef TE_BITWISE_OPERATORS
        CHECK(tep.evaluate("0.0 & 5") == 0);
        CHECK(tep.evaluate("0.0 & 0") == 0);
        CHECK(tep.evaluate("-1 & 5") == 1);
        CHECK(tep.evaluate("1 & 1") == 1);
        CHECK(tep.evaluate("0.0 | 5") == 1);
        CHECK(tep.evaluate("0.0 | 0") == 0);
        CHECK(tep.evaluate("-1 | 5") == 1);
        CHECK(tep.evaluate("1 | 1") == 1);
        CHECK(tep.evaluate("-1 | 0.0") == 1);
#endif
        CHECK(tep.evaluate("0.0 && 5") == 0);
        CHECK(tep.evaluate("0.0 && 0") == 0);
        CHECK(tep.evaluate("-1 && 5") == 1);
        CHECK(tep.evaluate("1 && 1") == 1);
        CHECK(tep.evaluate("0.0 || 5") == 1);
        CHECK(tep.evaluate("0.0 || 0") == 0);
        CHECK(tep.evaluate("-1 || 5") == 1);
        CHECK(tep.evaluate("1 || 1") == 1);
        CHECK(tep.evaluate("-1 || 0.0") == 1);
        }
    }

TEST_CASE("Optimize", "[optimize]")
    {
    te_parser tep;

    auto res = tep.evaluate("");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 0);

    res = tep.evaluate(std::string{});
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

    res = tep.evaluate("1***5");
    CHECK(std::isnan(res));
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() == 3);
    
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
    CHECK(tep.evaluate("FACT(5)") == 120);
    CHECK(tep.evaluate("FACT(1.9)") == 1);
    CHECK(tep.evaluate("FACT(0)") == 1);
    CHECK(tep.evaluate("FACT(1)") == 1);
    CHECK(std::isnan(tep.evaluate("FACT(-1)")));

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
    te_type x{ 0 }, y{ 0 }, test{ 0 };

    te_parser tep;
    tep.set_variables_and_functions({ {"x", &x}, {"y", &y}, {"te_st", &test} });
    [[maybe_unused]] auto exprRes = tep.evaluate("cos x + sin y");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == te_parser::npos);

    exprRes = tep.evaluate("x+x+x-y");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == te_parser::npos);

    exprRes = tep.evaluate("x*y^3");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == te_parser::npos);

    exprRes = tep.evaluate("te_st+5");
    CHECK(tep.success());
    CHECK(tep.get_last_error_position() == te_parser::npos);

    exprRes = tep.evaluate("xx*y^3");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != te_parser::npos);

    exprRes = tep.evaluate("tes");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != te_parser::npos);

    exprRes = tep.evaluate("sinn x");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != te_parser::npos);

    exprRes = tep.evaluate("si x");
    CHECK_FALSE(tep.success());
    CHECK(tep.get_last_error_position() != te_parser::npos);

    for (y = 2; y < 3; ++y)
        {
        for (x = 0; x < 5; ++x)
            {
            te_type ev{ 0 };

            ev = tep.evaluate("cos x + sin y");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::cos(x) + std::sin(y))));

            ev = tep.evaluate("x+x+x-y");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(x+x+x-y)));
#ifndef TE_BITWISE_OPERATORS
            ev = tep.evaluate("x*y^3");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(x*y*y*y)));
#endif
            ev = tep.evaluate("x*y**3");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(x * y * y * y)));

            test = x;
            ev = tep.evaluate("te_st+5");
            CHECK_THAT(ev, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(x+5)));
            }
        }
    }

TEST_CASE("Dynamic", "[dynamic]")
    {
    te_type x{ 2 }, f{ 5 };
    const std::set<te_variable> lookup =
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

TEST_CASE("Copy", "[copy]")
    {
    te_parser tep;
    te_type x{ 8 }, y{ 2 };
    tep.set_variables_and_functions({ {"x", &x}, {"y", &y} });
    CHECK(tep.evaluate("trunc(9.57878423)") == 9);
    CHECK(tep.evaluate() == 9);
        {
        // test operator== and copy CTOR
        te_parser tep2 = tep;
        CHECK(tep2.evaluate() == 9);
        CHECK(te_parser{ tep }.evaluate() == 9);
        }

    CHECK(tep.evaluate("(x + y) * y") == 20);
    // variable connection logic should be copied over too
        {
        te_parser tep2 = tep;
        CHECK(tep2.evaluate() == 20);
        CHECK(te_parser{ tep }.evaluate() == 20);
        }
    }

TEST_CASE("Empty", "[empty]")
    {
    te_parser tep;

    SECTION("Empty Eval")
        {
        CHECK(std::isnan(tep.evaluate()));
        CHECK_FALSE(tep.success());
        CHECK(std::string{ "Expression is empty." } == tep.get_last_error_message());
        }

    SECTION("Empty String")
        {
        CHECK(std::isnan(tep.evaluate("")));
        CHECK_FALSE(tep.success());
        CHECK(std::string{ "Expression is empty." } == tep.get_last_error_message());
        }
    }

TEST_CASE("Inf", "[inf]")
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
    CHECK(std::isinf(tep.evaluate("log10(0)")));
    }

TEST_CASE("NaN", "[nan]")
    {
    te_parser tep;

    CHECK(std::isnan(tep.evaluate("fac(-1)")));
    CHECK(std::isnan(tep.evaluate("ncr(2, 4)")));
    CHECK(std::isnan(tep.evaluate("ncr(-2, 4)")));
    CHECK(std::isnan(tep.evaluate("ncr(2, -4)")));
    CHECK(std::isnan(tep.evaluate("npr(2, 4)")));
    CHECK(std::isnan(tep.evaluate("npr(-2, 4)")));
    CHECK(std::isnan(tep.evaluate("npr(2, -4)")));

    CHECK(std::isnan(tep.evaluate("NAN()")));
    CHECK(tep.success());
    CHECK(std::isnan(tep.evaluate("NAN")));
    CHECK(tep.success());
    CHECK(std::isnan(tep.evaluate("NA")));
    CHECK(tep.success());
    CHECK(std::isnan(tep.evaluate("npr(NAN,90)")));
    CHECK(tep.success());

    CHECK(tep.evaluate("ISNAN(NA)"));
    CHECK(tep.evaluate("ISNAN(5/0)"));
    CHECK(tep.evaluate("ISNA(5/0)"));
    CHECK(tep.evaluate("ISNA(npr(2, -4))"));
    CHECK_FALSE(tep.evaluate("ISNA(2 + 2)"));

    CHECK(tep.evaluate("ISERROR(NA)"));
    CHECK(tep.evaluate("ISERR(5/0)"));
    CHECK(tep.evaluate("ISERROR(5/0)"));
    CHECK(tep.evaluate("ISERR(npr(2, -4))"));
    CHECK_FALSE(tep.evaluate("ISERROR(2 + 2)"));
    }

TEST_CASE("Even", "[even]")
    {
    te_parser tep;

    CHECK(tep.evaluate("=EVEN(1.5)") == 2);
    CHECK(tep.evaluate("=EVEN(3)") == 4);
    CHECK(tep.evaluate("=EVEN(2)") == 2);
    CHECK(tep.evaluate("=EVEN(-1)") == -2);
    CHECK(tep.evaluate("=EVEN(-3)") == -4);
    CHECK(tep.evaluate("=EVEN(-3.7)") == -4);
    CHECK(tep.evaluate("=EVEN(-3.1)") == -4);
    CHECK(tep.evaluate("=EVEN(0)") == 0);
    CHECK(std::isnan(tep.evaluate("=EVEN(NAN)")));

    CHECK_FALSE(tep.evaluate("ISEVEN(-1)"));
    CHECK(tep.evaluate("=ISEVEN(2.5)"));
    CHECK_FALSE(tep.evaluate("=ISEVEN(5)"));
    CHECK(tep.evaluate("=ISEVEN(0)"));
    CHECK(tep.evaluate("=ISEVEN(40900)"));
    CHECK(std::isnan(tep.evaluate("=ISEVEN(NAN)")));
    }

TEST_CASE("Odd", "[odd]")
    {
    te_parser tep;

    CHECK(tep.evaluate("=ODD(1.5)") == 3);
    CHECK(tep.evaluate("=ODD(3)") == 3);
    CHECK(tep.evaluate("=ODD(2)") == 3);
    CHECK(tep.evaluate("=ODD(-1)") == -1);
    CHECK(tep.evaluate("=ODD(-2)") == -3);
    CHECK(tep.evaluate("=ODD(-4)") == -5);
    CHECK(tep.evaluate("=ODD(0)") == 1);
    CHECK(std::isnan(tep.evaluate("=ODD(NAN)")));

    CHECK(tep.evaluate("ISODD(-1)"));
    CHECK_FALSE(tep.evaluate("=ISODD(2.5)"));
    CHECK_FALSE(tep.evaluate("=ISODD(0)"));
    CHECK(tep.evaluate("=ISODD(5)"));
    CHECK(std::isnan(tep.evaluate("=ISODD(NAN)")));
    }

TEST_CASE("Zeros", "[zeros]")
    {
    te_parser tep;

    CHECK(std::isnan(tep.evaluate("0/0")));
    CHECK(std::isnan(tep.evaluate("1/0")));
    CHECK(std::isnan(tep.evaluate("1%0")));
    CHECK(std::isnan(tep.evaluate("1%(1%0)")));
    CHECK(std::isnan(tep.evaluate("(1%0)%1")));
    }

TEST_CASE("Hex", "[hex]")
    {
    te_parser tep;

    CHECK(tep.evaluate("0x0") == 0);
    CHECK(tep.evaluate("0x8") == 8);
    // (2^53)-1 isn't representable as a float; both sides round to 2^53 there
    CHECK(tep.evaluate("0x1FFFFFFFFFFFFF") == static_cast<te_type>(9007199254740991));
    CHECK(tep.evaluate("0x57CEF7") == 5754615);
    CHECK(tep.evaluate("0x57CEF7") == 5754615);
    CHECK(tep.evaluate("-0X57CEF7") == -5754615);
    CHECK(std::isnan(tep.evaluate("0X")));
    }

TEST_CASE("UINT support", "[uint]")
    {
    te_parser tep;

    if constexpr(te_parser::supports_32bit())
        {
        INFO("Checking for handling of large value: " +
             std::to_string(std::numeric_limits<uint32_t>::max()));
        CHECK(tep.evaluate(std::to_string(std::numeric_limits<uint32_t>::max())) ==
              std::numeric_limits<uint32_t>::max());
        CHECK(tep.evaluate(
            "(" + std::to_string(std::numeric_limits<uint32_t>::max()) + " - 100) + 100") ==
            std::numeric_limits<uint32_t>::max());
        CHECK(tep.evaluate(
            std::to_string(std::numeric_limits<uint32_t>::max()) + " - 700") ==
            std::numeric_limits<uint32_t>::max() - 700);
        CHECK_FALSE(tep.evaluate(
            std::to_string(std::numeric_limits<uint32_t>::max()) + " - 700") ==
            std::numeric_limits<uint32_t>::max() - 699);
        }

    if constexpr(te_parser::supports_64bit())
        {
        // should be 18446744073709551615
        INFO("Checking for handling of large value: " +
             std::to_string(std::numeric_limits<uint64_t>::max()));
        CHECK((uint64_t)tep.evaluate(std::to_string(std::numeric_limits<uint64_t>::max())) ==
              std::numeric_limits<uint64_t>::max());
        CHECK((uint64_t)tep.evaluate(
            "(" + std::to_string(std::numeric_limits<uint64_t>::max()) + " - 100) + 100") ==
            std::numeric_limits<uint64_t>::max());
        CHECK((uint64_t)tep.evaluate(
            std::to_string(std::numeric_limits<uint64_t>::max()) + " - 700") ==
            std::numeric_limits<uint64_t>::max() - 700);
        CHECK_FALSE((uint64_t)tep.evaluate(
            std::to_string(std::numeric_limits<uint64_t>::max()) + " - 700") ==
            std::numeric_limits<uint64_t>::max() - 699);
        }
    }

TEST_CASE("Braces", "[braces]")
    {
    te_type x{ 100 };

    te_parser tep;
    tep.set_variables_and_functions({ {"x", &x} });
#ifdef TE_BRACKETS_AS_PARENS
    CHECK(tep.evaluate("[x+86]") == 186);
#else
    CHECK(std::isnan(tep.evaluate("[x+86]")));
#endif
    }

TEST_CASE("Functions", "[functions]")
    {
    te_type x{ 0 }, y{ 0 };

    te_parser tep;
    tep.set_variables_and_functions({ {"x", &x}, {"y", &y} });

    for (x = -5; x < 5; x += (te_type)0.1)
        {
        CHECK_THAT(tep.evaluate("abs x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::fabs(x))));
        if (!std::isnan(std::acos(x)))
            CHECK_THAT(tep.evaluate("acos x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::acos(x))));
        else
            CHECK(std::isnan(tep.evaluate("acos x")));
        if (!std::isnan(std::asin(x)))
            CHECK_THAT(tep.evaluate("asin x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::asin(x))));
        else
            CHECK(std::isnan(tep.evaluate("asin x")));
        CHECK_THAT(tep.evaluate("atan x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::atan(x))));
        CHECK_THAT(tep.evaluate("ceil x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::ceil(x))));
        CHECK_THAT(tep.evaluate("cos x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::cos(x))));
        CHECK_THAT(tep.evaluate("cosh x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::cosh(x))));
        CHECK_THAT(tep.evaluate("exp x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::exp(x))));
        CHECK_THAT(tep.evaluate("floor x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::floor(x))));
        if (!std::isnan(log(x)))
            CHECK_THAT(tep.evaluate("ln x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::log(x))));
        else
            CHECK(std::isnan(tep.evaluate("ln x")));
        if (!std::isnan(std::log10(x)))
            CHECK_THAT(tep.evaluate("log10 x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::log10(x))));
        else
            CHECK(std::isnan(tep.evaluate("log10 x")));
        CHECK_THAT(tep.evaluate("sin x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::sin(x))));
        CHECK_THAT(tep.evaluate("sinh x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::sinh(x))));
        if (!std::isnan(std::sqrt(x)))
            CHECK_THAT(tep.evaluate("sqrt x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::sqrt(x))));
        else
            CHECK(std::isnan(tep.evaluate("sqrt x")));
        CHECK_THAT(tep.evaluate("tan x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::tan(x))));
        CHECK_THAT(tep.evaluate("tanh x"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::tanh(x))));

        for (y = -2; y < 2; y += (te_type)0.2)
            {
            if (std::abs(x) < 0.01) break;
            CHECK_THAT(tep.evaluate("atan2(x,y)"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::atan2(x, y))));
            if (!std::isnan(std::pow(x, y)))
                CHECK_THAT(tep.evaluate("pow(x,y)"), Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(std::pow(x, y))));
            else
                CHECK(std::isnan(tep.evaluate("pow(x,y)")));
            }
        }
    }

TEST_CASE("Power", "[power]")
    {
    const te_type a{ 2 }, b{ 3 };

    const std::set<te_variable> lookup = {
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
#elif defined(TE_BITWISE_OPERATORS)
    CHECK(tep.evaluate("2**3**4") == tep.evaluate("(2**3)**4"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-2**2") == tep.evaluate("(-2)**2"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(-2)**2") == tep.evaluate("4"));
    CHECK(tep.success());

    CHECK(tep.evaluate("--2**2") == tep.evaluate("2**2"));
    CHECK(tep.success());

    CHECK(tep.evaluate("---2**2") == tep.evaluate("(-2)**2"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-2**2") == tep.evaluate("4"));
    CHECK(tep.success());

    CHECK(tep.evaluate("2**1.1**1.2**1.3") == tep.evaluate("((2**1.1)**1.2)**1.3"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-a**b") == tep.evaluate("(-a)**b"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-a**-b") == tep.evaluate("(-a)**(-b)"));
    CHECK(tep.success());

    CHECK(tep.evaluate("1**0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(1)**0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(-1)**0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("(-5)**0") == tep.evaluate("1"));
    CHECK(tep.success());

    CHECK(tep.evaluate("-2**-3**-4") == tep.evaluate("((-2)**(-3))**(-4)"));
    CHECK(tep.success());
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

TEST_CASE("Cells", "[closure]")
    {
    te_expr_array teArray{ TE_DEFAULT };

    te_parser tep;
    tep.set_variables_and_functions(
        {
            {"cell", cell, TE_DEFAULT, &teArray},
            {"cellmax", cell_max, TE_DEFAULT, &teArray}
        });

    auto res = tep.evaluate("cell 0");
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

    teArray.m_data = { 6, 7, 8, 5, 4 };
    res = tep.evaluate("SUM(CELL 0, CELL 1, CELL 2, CELL 3, CELL 4)");
    CHECK(tep.success());
    CHECK(tep.evaluate() == 30);

    res = tep.evaluate("CellMax()");
    CHECK(tep.success());
    CHECK(tep.evaluate() == 8);
    }

TEST_CASE("Closure", "[closure]")
    {
    te_type extra{ 0 };

    te_expr te{ TE_DEFAULT, &extra };

    std::set<te_variable> lookup = {
        {"c0", clo0, TE_DEFAULT, &te},
        {"c1", clo1, TE_DEFAULT, &te},
        {"c2", clo2, TE_DEFAULT, &te},
        {"c3", clo3, TE_DEFAULT, &te},
        {"c4", clo4, TE_DEFAULT, &te},
        {"c5", clo5, TE_DEFAULT, &te},
        {"c6", clo6, TE_DEFAULT, &te},
        {"c7", clo7, TE_DEFAULT, &te},
        {"c8", clo8, TE_DEFAULT, &te},
        {"c9", clo9, TE_DEFAULT, &te},
        {"c10", clo10, TE_DEFAULT, &te},
        {"c11", clo11, TE_DEFAULT, &te},
        {"c12", clo12, TE_DEFAULT, &te},
        {"c13", clo13, TE_DEFAULT, &te},
        {"c14", clo14, TE_DEFAULT, &te},
        {"c15", clo15, TE_DEFAULT, &te},
        {"c16", clo16, TE_DEFAULT, &te},
        {"c17", clo17, TE_DEFAULT, &te},
        {"c18", clo18, TE_DEFAULT, &te},
        {"c19", clo19, TE_DEFAULT, &te},
        {"c20", clo20, TE_DEFAULT, &te},
        {"c21", clo21, TE_DEFAULT, &te},
        {"c22", clo22, TE_DEFAULT, &te},
        {"c23", clo23, TE_DEFAULT, &te},
        {"c24", clo24, TE_DEFAULT, &te}
    };

    te_parser tep;
    tep.set_variables_and_functions(lookup);

    extra = 0;
    te_type answer{ 6 };
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
        res = tep.evaluate("C7 (10, 20, 5, 2, 8, 9, 4)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C8")
        {
        extra = 0;
        answer = 120;
        res = tep.evaluate("C8 (10, 20, 5, 2, 8, 9, 4, 62)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C9")
        {
        extra = 0;
        answer = 44;
        res = tep.evaluate("C9 (10, 5, 2, 8, 9, 4, 1, 3, 2)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C10")
        {
        extra = 0;
        answer = 55;
        res = tep.evaluate("C10 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C11")
        {
        extra = 0;
        answer = 61;
        res = tep.evaluate("C11 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C12")
        {
        extra = 0;
        answer = 68;
        res = tep.evaluate("C12 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C13")
    {
        extra = 0;
        answer = 76;
        res = tep.evaluate("C13 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C14")
        {
        extra = 0;
        answer = 85;
        res = tep.evaluate("C14 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C15")
        {
        extra = 0;
        answer = 95;
        res = tep.evaluate("C15 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C16")
        {
        extra = 0;
        answer = 106;
        res = tep.evaluate("C16 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10, 11)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C17")
        {
        extra = 0;
        answer = 118;
        res = tep.evaluate("C17 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10, 11, 12)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C18")
        {
        extra = 0;
        answer = 131;
        res = tep.evaluate("C18 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10, 11, 12, 13)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C19")
        {
        extra = 0;
        answer = 145;
        res = tep.evaluate("C19 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10, 11, 12, 13, 14)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C20")
        {
        extra = 0;
        answer = 160;
        res = tep.evaluate("C20 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C21")
        {
        extra = 0;
        answer = 176;
        res = tep.evaluate("C21 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C22")
        {
        extra = 0;
        answer = 193;
        res = tep.evaluate("C22 (10, 5, 2, 8, 9, 4, 1, 3, 2, 11, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C23")
        {
        extra = 0;
        answer = 298;
        res = tep.evaluate("C23 (10, 20, 5, 2, 8, 9, 4, 62, 10, 20, 5, 2, 8, 9, 4, 62, 10, 20, 5, 2, 8, 9, 4)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }

    SECTION("C24")
        {
        extra = 0;
        answer = 370;
        res = tep.evaluate("C24 (10, 20, 5, 2, 8, 9, 4, 62, 10, 20, 5, 2, 8, 9, 4, 62, 10, 20, 5, 2, 8, 9, 4, 72)");
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);

        extra = 10;
        res = tep.evaluate();
        CHECK(tep.success());
        CHECK(tep.evaluate() == answer + extra);
        }
    }

TEST_CASE("Constants", "[constants]")
    {
    te_parser tep;
    // could be done via add_var() also
    tep.set_constant("SALARY", 15.25);
    CHECK(tep.evaluate("SALARY") == 15.25);

    tep.set_constant("SALARY", 17.75);
    CHECK(tep.evaluate("salary") == 17.75);
    CHECK(tep.get_constant("salary") == 17.75);
    }

TEST_CASE("Long names", "[longnames]")
    {
    te_parser p;
    p.set_variables_and_functions(
        {
            { "AddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResultAddTwoNumbersTogetherThroughASimpleMathematicalOperationUsingSimpleAdditionOfJustTwoRegularNumbersWhichYielsASumAsTheResult", AddEm }
        });
    p.compile(("ADDTWONUMBERSTOGETHERTHROUGHASIMPLEMATHEMATICALOPERATIONUSINGSIMPLEADDITIONOFJUSTTWOREGULARNUMBERSWHICHYIELSASUMASTHERESULTADDTWONUMBERSTOGETHERTHROUGHASIMPLEMATHEMATICALOPERATIONUSINGSIMPLEADDITIONOFJUSTTWOREGULARNUMBERSWHICHYIELSASUMASTHERESULTADDTWONUMBERSTOGETHERTHROUGHASIMPLEMATHEMATICALOPERATIONUSINGSIMPLEADDITIONOFJUSTTWOREGULARNUMBERSWHICHYIELSASUMASTHERESULTADDTWONUMBERSTOGETHERTHROUGHASIMPLEMATHEMATICALOPERATIONUSINGSIMPLEADDITIONOFJUSTTWOREGULARNUMBERSWHICHYIELSASUMASTHERESULT(1, 2)"));
    CHECK(p.evaluate() == 3.0);
    p.compile(("addtwonumberstogetherthroughasimplemathematicaloperationusingsimpleadditionofjusttworegularnumberswhichyielsasumastheresultaddtwonumberstogetherthroughasimplemathematicaloperationusingsimpleadditionofjusttworegularnumberswhichyielsasumastheresultaddtwonumberstogetherthroughasimplemathematicaloperationusingsimpleadditionofjusttworegularnumberswhichyielsasumastheresultaddtwonumberstogetherthroughasimplemathematicaloperationusingsimpleadditionofjusttworegularnumberswhichyielsasumastheresult(1, 2)"));
    CHECK(p.evaluate() == 3.0);
    }

TEST_CASE("Precedence", "[precedence]")
    {
    te_parser tep;

    CHECK_THAT(-26.5, // "5+2-1*31/2-20+MOD(21,2)*2" in Excel
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("5+2-1*31/2-20+21%2*2"))));
    CHECK_THAT(-26.5,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("5+2-1*31/2-20+MOD(21,2)*2"))));
#ifndef TE_BITWISE_OPERATORS
    CHECK_THAT(-12.75,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("5+2^3-1*31/2^2-20+MOD(21,2)*2"))));
    CHECK_THAT(-12.75,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("5+2^3-1*31/2^2-20+ 21% 2*2"))));
#endif
    CHECK_THAT(-12.75,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("5+2**3-1*31/2**2-20+MOD(21,2)*2"))));
    CHECK_THAT(-12.75,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("5+2**3-1*31/2**2-20+ 21% 2*2"))));

#ifndef TE_FLOAT
    // The precedence that C++ compiler use for << and >>
    // Excel doesn't have operators for these, although there are
    // related functions like BITLSHIFT().
    CHECK_THAT((1 << 1 + 2 * 2),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(tep.evaluate("(1 << 1 + 2 * 2)"))));
    CHECK_THAT((32 >> 1 + 2 * 2),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(tep.evaluate("(32 >> 1 + 2 * 2)"))));
#else
    CHECK(std::isnan(tep.evaluate("(1 << 1 + 2 * 2)")));
#endif
#ifndef TE_BITWISE_OPERATORS
    CHECK_THAT(27, // this is what Excel does
               Catch::Matchers::WithinRel(
                   WITHIN_TYPE_CAST(tep.evaluate("5 ^ 2 + 2"))));
#endif
    CHECK_THAT(27, // this is what Excel does
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(tep.evaluate("5 ** 2 + 2"))));
    }

TEST_CASE("Round", "[round]")
    {
    te_parser p;
    p.compile(("ROUND(1.5, 0)"));
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

    // OR
    p.compile(("0 | 1"));
    CHECK(1 == p.evaluate());
    p.compile(("1 | 1"));
    CHECK(1 == p.evaluate());
    p.compile(("0 | 0"));
    CHECK(0 == p.evaluate());
    p.compile(("0 || 1"));
    CHECK(1 == p.evaluate());
    p.compile(("1 || 1"));
    CHECK(1 == p.evaluate());
    p.compile(("0 || 0"));
    CHECK(0 == p.evaluate());
    // AND
    p.compile(("0 & 1"));
    CHECK(0 == p.evaluate());
    p.compile(("1 & 1"));
    CHECK(1 == p.evaluate());
    p.compile(("0 & 0"));
    CHECK(0 == p.evaluate());
    p.compile(("0 && 1"));
    CHECK(0 == p.evaluate());
    p.compile(("1 && 1"));
    CHECK(1 == p.evaluate());
    p.compile(("0 && 0"));
    CHECK(0 == p.evaluate());
    // AND and OR
    p.compile(("0 || 1 && 1 || 0 && 1"));
    constexpr double result{ (0 | 1 & 1 | 0 & 1) };
    CHECK(result == p.evaluate());
    // equality
    p.compile(("5=5"));
    CHECK(1 == p.evaluate());
    p.compile(("5<>5"));
    CHECK(0 == p.evaluate());
    CHECK_FALSE(p.evaluate("5!=5"));
    CHECK(p.evaluate("5 != 5.1"));

    CHECK(p.evaluate("5 == 5"));
    CHECK_FALSE(p.evaluate("5 == 5.1"));
    CHECK_FALSE(p.evaluate("5.1 == 5"));

    p.compile(("5.1 <>5"));
    CHECK(1 == p.evaluate());
    // less than
    p.compile(("5.1 < 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5 < 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5.1 < 5.19"));
    CHECK(1 == p.evaluate());
    p.compile(("-6 < 1"));
    CHECK(1 == p.evaluate());
    // less than or equal to
    p.compile(("5.1 <= 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5 <= 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5.1 <= 5.19"));
    CHECK(1 == p.evaluate());
    p.compile(("-6 <= 1"));
    CHECK(1 == p.evaluate());
    // greater than
    p.compile(("5.1 > 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5 > 5"));
    CHECK(0 == p.evaluate());
    p.compile(("5.19 > 5.1"));
    CHECK(1 == p.evaluate());
    p.compile(("1 > -6"));
    CHECK(1 == p.evaluate());
    // greater than or equal to
    p.compile(("5.1 >= 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5 >= 5"));
    CHECK(1 == p.evaluate());
    p.compile(("5.19 >= 5.1"));
    CHECK(1 == p.evaluate());
    p.compile(("1 >= -6"));
    CHECK(1 == p.evaluate());

    // more complex examples
    CHECK(p.evaluate("1 + 1 - 2 < 1 + 1") == 1);
    CHECK(p.evaluate("1 + 1 - 2 = 1 + 1 - 2") == 1);
    CHECK(p.evaluate("1 + 1 - 2 <> 1 + 1 - 7") == 1);
#ifndef TE_BITWISE_OPERATORS
    CHECK(p.evaluate("1 - 1 & 2") == 0);
    CHECK(p.evaluate("1 - 1 | 2 - 2") == 0);
    CHECK(p.evaluate("1 - 1 | 2*4 - 2") == 1);

    CHECK(p.evaluate("1 - 1 < 1 & 2") == 1);
#endif
    CHECK(p.evaluate("1 - 1 && 2") == 0);
    CHECK(p.evaluate("1 - 1 || 2 - 2") == 0);
    CHECK(p.evaluate("1 - 1 || 2*4 - 2") == 1);

    CHECK(p.evaluate("1 - 1 < 1 && 2") == 1);
    // examples from manual
    CHECK_THAT(12.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate("5+5+5/2"))));
    CHECK_THAT(7.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate("(5+5+5)/2"))));
#ifndef TE_BITWISE_OPERATORS
    CHECK_THAT(49, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate("(2+5)^2"))));
    CHECK_THAT(27, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate("2+5^2"))));
#endif
    CHECK_THAT(49, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate("(2+5)**2"))));
    CHECK_THAT(27, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate("2+5**2"))));
    }

TEST_CASE("Statistics", "[stats]")
    {
    te_parser p;

    p.compile(("sum(1, 2, 3, 4)"));
    CHECK(10 == p.evaluate());
    p.compile(("SUM(1.1, 2.7, 3, 4.9)"));
    CHECK_THAT(11.7, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("AVERAGE(1, 2, 3, 4, 5)"));
    CHECK(3 == p.evaluate());
    p.compile(("AVERAGE(1.1, 2.7, 3.2, 4, 5.7)"));
    CHECK_THAT(3.34, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(1.1)"));
    CHECK_THAT(1.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(1.1, 1.2)"));
    CHECK_THAT(1.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-1, 2)"));
    CHECK_THAT(-1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-1, 2, 0, -5.8, 9)"));
    CHECK_THAT(-5.8, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9)"));
    CHECK_THAT(-9, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87)"));
    CHECK_THAT(-87, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90)"));
    CHECK_THAT(-90, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99)"));
    CHECK_THAT(-99, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101)"));
    CHECK_THAT(-101, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103)"));
    CHECK_THAT(-103, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111)"));
    CHECK_THAT(-111, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113)"));
    CHECK_THAT(-113, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150)"));
    CHECK_THAT(-150, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175)"));
    CHECK_THAT(-175, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199)"));
    CHECK_THAT(-199, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220)"));
    CHECK_THAT(-220, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220, -222)"));
    CHECK_THAT(-222, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220, -222, -233)"));
    CHECK_THAT(-233, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220, -222, -233, -245)"));
    CHECK_THAT(-245, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220, -222, -233, -245, -255)"));
    CHECK_THAT(-255, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220, -222, -233, -245, -255, -300)"));
    CHECK_THAT(-300, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220, -222, -233, -245, -255, -300, -320)"));
    CHECK_THAT(-320, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MIN(-9, 2, 0, -5.8, 9, 8, -87, -90, -99, -101, -103, -111, -113, -150, -175, -199, -220, -222, -233, -245, -255, -300, -320, -450)"));
    CHECK_THAT(-450, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("MAX(1.1)"));
    CHECK_THAT(1.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(1.1, 1.2)"));
    CHECK_THAT(1.2, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(-1, 2)"));
    CHECK_THAT(2, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(1.1, 1.2, 0, 5.8)"));
    CHECK_THAT(5.8, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8)"));
    CHECK_THAT(9.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127)"));
    CHECK_THAT(127, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156)"));
    CHECK_THAT(156, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201)"));
    CHECK_THAT(201, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207)"));
    CHECK_THAT(207, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209)"));
    CHECK_THAT(209, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226)"));
    CHECK_THAT(226, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256)"));
    CHECK_THAT(256, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300)"));
    CHECK_THAT(300, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301)"));
    CHECK_THAT(301, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303)"));
    CHECK_THAT(303, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309)"));
    CHECK_THAT(309, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309, 326)"));
    CHECK_THAT(326, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309, 326, 350)"));
    CHECK_THAT(350, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309, 326, 350, 388)"));
    CHECK_THAT(388, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309, 326, 350, 388, 390)"));
    CHECK_THAT(390, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309, 326, 350, 388, 390, 401)"));
    CHECK_THAT(401, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309, 326, 350, 388, 390, 401, 403)"));
    CHECK_THAT(403, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("MAX(9.1, 1.2, 0, 5.8, 80, -1, 127, 156, 201, 207, 209, 226, 256, 300, 301, 303, 309, 326, 350, 388, 390, 401, 403, 777)"));
    CHECK_THAT(777, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    }

TEST_CASE("Round higher precision", "[round]")
    {
    te_parser p;

    CHECK_THAT(23.78, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate("round(23.7825, 2)"))));

    p.compile(("ROUND(-1.475, 2)"));
    CHECK_THAT(-1.48, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(1.55, 1)"));
    CHECK_THAT(1.6, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("ROUND(-1.55, 1)"));
    CHECK_THAT(-1.6, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.1415678, 2)"));
    CHECK_THAT(3.14, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.1415678, 3)"));
    CHECK_THAT(3.142, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.1415678, 4)"));
    CHECK_THAT(3.1416, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.1415678, 5)"));
    CHECK_THAT(3.14157, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.1415678, 6)"));
    CHECK_THAT(3.141568, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.14156785, 7)"));
    CHECK_THAT(3.1415679, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), WITHIN_TYPE(0.0000001)));

    p.compile(("round(3.141567854, 8)"));
    CHECK_THAT(3.14156785, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.1415678546, 9)"));
    CHECK_THAT(3.141567855, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.14156785467, 10)"));
    CHECK_THAT(3.1415678547, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.141567854672, 11)"));
    CHECK_THAT(3.14156785467, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(3.1415678546727, 12)"));
    CHECK_THAT(3.141567854673, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("round(-3.1415678, 6)"));
    CHECK_THAT(-3.141568, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    }

TEST_CASE("Round negative", "[round]")
    {
    // https://support.microsoft.com/en-us/office/round-function-c018c5d8-40fb-4053-90b1-b3e7f61a213c
    te_parser p;

    CHECK(p.evaluate("ROUND(21.5, -1)") == 20);
    CHECK(p.evaluate("ROUND(21, -1)") == 20);
    CHECK(p.evaluate("ROUND(25.5, -1)") == 30);
    CHECK(p.evaluate("ROUND(-50.55,-2)") == -100);
    CHECK(p.evaluate("ROUND(626.3,-3)") == 1000);
    CHECK(p.evaluate("ROUND(6626.3,-4)") == 10000);
    // verified in Excel 2016
    CHECK(p.evaluate("ROUND(626.3,-4)") == 0);
    CHECK(p.evaluate("ROUND(626.3,-10)") == 0);
    // Excel politely returns zero, but we return NaN since
    // this is a ridiculous number of digits to request
    CHECK(std::isnan(p.evaluate("ROUND(22, -100000)")));
    CHECK(std::isnan(p.evaluate("ROUND(22, 100000)")));
    }

TEST_CASE("Math operators", "[math]")
    {
    te_parser p;

    p.compile(("9*3/2+8-2"));
    CHECK_THAT(19.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("9*((3/2)+(8-2))")); // change up the order of operations
    CHECK_THAT(67.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
#ifndef TE_BITWISE_OPERATORS
    p.compile(("9*3^3/2+8-(11%2)"));
    CHECK_THAT(128.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("9.2*3.4^3/2+8.7-(11%2)"));
    CHECK_THAT(188.4984, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
#endif
    p.compile(("9*3**3/2+8-(11%2)"));
    CHECK_THAT(128.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("9.2*3.4**3/2+8.7-(11%2)"));
    CHECK_THAT(188.4984, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    }

TEST_CASE("Division", "[math]")
    {
    te_parser p;

    p.compile("4/2.2");
    CHECK_THAT(1.81818, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));
    CHECK(std::isnan(p.evaluate("5 / 0")));
    CHECK_FALSE(p.success());
    CHECK(p.get_last_error_message() == "Division by zero.");
    }

TEST_CASE("Modulus", "[math]")
    {
    te_parser p;

    p.compile(("MOD(5,2)"));
    CHECK(1 == p.evaluate());
    CHECK(0 == p.evaluate("mod(5,2.5)"));
    CHECK(2 == p.evaluate("MOD(5,3)"));
    CHECK(0 == p.evaluate("mod(5,5)"));
    CHECK(5 == p.evaluate("MoD(5,6)"));

    CHECK(std::isnan(p.evaluate("5 % 0")));
    CHECK_FALSE(p.success());
    CHECK(p.get_last_error_message() == "Modulus by zero.");
    }

#ifndef TE_NO_BOOKKEEPING
TEST_CASE("Is function used", "[functions]")
    {
    te_parser p;

    p.set_variables_and_functions({
        { "MULT", __mult }
        });
    p.compile(("log10(5)+sin(atan(6))-MULT(2,30,4,5)+1"));
    CHECK(p.is_function_used(("MULT")));
    CHECK(p.is_function_used(("Log10")));
    CHECK(p.is_function_used(("sIn")));
    CHECK(p.is_function_used(("atAn")));
    CHECK(p.is_function_used(("MuLT")));
    CHECK_FALSE(p.is_function_used(("tan")));
    CHECK_FALSE(p.is_function_used(("sing")));
    CHECK_FALSE(p.is_function_used(("si")));
    }

TEST_CASE("Remove custom var", "[functions]")
    {
    te_parser p;

    p.set_variables_and_functions({
        {"STRESS_L", static_cast<te_type>(10.1) },
        {"P_LEVEL", static_cast<te_type>(.5) },
        {"z", static_cast<te_type>(.75) } });
    p.compile(("z + STRESS_L + P_LEVEL"));
    CHECK(p.is_variable_used(("Z")));
    CHECK(p.is_variable_used(("STRESs_L")));
    CHECK(p.is_variable_used(("P_LEVEL")));
    CHECK(p.success());
    p.remove_variable_or_function("stress_l");
    p.compile(("z + P_LEVEL"));
    CHECK(p.success());
    CHECK_FALSE(p.compile(("z + STRESS_L + P_LEVEL")));

    p.remove_variable_or_function("p_level");
    p.compile(("z"));
    CHECK(p.success());
    CHECK_FALSE(p.compile(("z + P_LEVEL")));

    p.remove_variable_or_function("z");
    CHECK_FALSE(p.compile(("z")));
    }

TEST_CASE("Is variable used", "[functions]")
    {
    te_parser p;

    p.set_variables_and_functions({
        {"STRESS_L", static_cast<te_type>(10.1) },
        {"P_LEVEL", static_cast<te_type>(.5) },
        {"z", static_cast<te_type>(.75) } });
    p.compile(("z + STRESS_L"));
    CHECK(p.is_variable_used(("Z")));
    CHECK(p.is_variable_used(("STRESs_L")));
    CHECK_FALSE(p.is_variable_used(("P_LEVEL")));
    CHECK_FALSE(p.is_variable_used(("zz")));
    CHECK_FALSE(p.is_variable_used(("TRESS_L")));
    }

TEST_CASE("Remove unused variables", "[variables]")
    {
    te_parser p;
    // nothing in here yet
    p.remove_unused_variables_and_functions();

    p.set_variables_and_functions({
        {"STRESS_L", static_cast<te_type>(10.1) },
        {"P_LEVEL", static_cast<te_type>(.5) },
        {"z", static_cast<te_type>(.75) } });
    CHECK(p.get_variables_and_functions().size() == 3);

    p.compile(("z + P_LEVEL"));
    CHECK(p.is_variable_used(("Z")));
    CHECK_FALSE(p.is_variable_used(("STRESS_L")));
    CHECK(p.is_variable_used(("P_LEVEL")));
    CHECK(p.success());
    CHECK(p.get_variables_and_functions().size() == 3);
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().size() == 2);

    p.compile(("P_LEVEL"));
    CHECK(p.success());
    CHECK_FALSE(p.is_variable_used(("Z")));
    CHECK_FALSE(p.is_variable_used(("STRESS_L")));
    CHECK(p.is_variable_used(("P_LEVEL")));
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().size() == 1);

    p.compile(("5 + 2"));
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().empty());

    // remove all at once
    p.set_variables_and_functions({
        {"STRESS_L", static_cast<te_type>(10.1) },
        {"P_LEVEL", static_cast<te_type>(.5) },
        {"z", static_cast<te_type>(.75) } });
    p.compile(("5 + 2"));
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().empty());

    // shouldn't do anything
    p.remove_unused_variables_and_functions();
    }

TEST_CASE("Remove unused functions", "[functions]")
    {
    te_parser p;
    // nothing in here yet
    p.remove_unused_variables_and_functions();

    p.set_variables_and_functions({
        {"STRESS_L", return5 },
        {"P_LEVEL", __mult },
        {"z", AddEm } });
    CHECK(p.get_variables_and_functions().size() == 3);

    p.compile(("z(2,5) + P_LEVEL(2,30,4,5)"));
    CHECK(p.is_function_used(("Z")));
    CHECK_FALSE(p.is_function_used(("STRESS_L")));
    CHECK(p.is_function_used(("P_LEVEL")));
    CHECK(p.success());
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().size() == 2);

    p.compile(("P_LEVEL(2,30,4,5)"));
    CHECK(p.success());
    CHECK_FALSE(p.is_function_used(("Z")));
    CHECK_FALSE(p.is_function_used(("STRESS_L")));
    CHECK(p.is_function_used(("P_LEVEL")));
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().size() == 1);

    p.compile(("5 + 2"));
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().empty());

    // remove all at once
    p.set_variables_and_functions({
        {"STRESS_L", return5 },
        {"P_LEVEL", __mult },
        {"z", AddEm } });
    p.compile(("5 + 2"));
    p.remove_unused_variables_and_functions();
    CHECK(p.get_variables_and_functions().empty());

    // function shouldn't be recognized now
    p.compile(("P_LEVEL(2,30,4,5)"));
    CHECK_FALSE(p.success());

    // shouldn't do anything
    p.remove_unused_variables_and_functions();
    }
#endif

TEST_CASE("Custom test", "[functions]")
    {
    te_parser p;

    SECTION("Custom test unknown parameters")
        {
        p.set_variables_and_functions({ { "MULT", __mult} });
        p.compile("MULT(2,30,4,5)+1");
        CHECK(1201 == p.evaluate());
        }
    SECTION("0 Parameters")
        {
        p.set_variables_and_functions({ {"Return5", return5} });
        p.compile("Return5()");
        CHECK_THAT(5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        }
    SECTION("1 Parameter")
        {
        p.set_variables_and_functions({ { "value", __value} });
        p.compile("value(2.1)");
        CHECK_THAT(2.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        }
    SECTION("2 Parameters")
        {
        p.set_variables_and_functions({ { "AddEm", AddEm} });
        p.compile("ADDEM(2.1, 86.8)");
        CHECK_THAT(88.9, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        }
    SECTION("3 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm3", AddEm3} });
        p.compile("ADDEM3(2.1, 86.8, 2)");
        CHECK_THAT(90.9, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("Bogus"); // nothing should happen
        p.compile(("ADDEM3(2.1, 86.8, 2)"));
        CHECK_THAT(90.9, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("addem3");
        CHECK_FALSE(p.compile(("ADDEM3(2.1, 86.8, 2)")));
        }


    SECTION("24 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm24", AddEm24} });
        p.compile("AddEm24(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1)");
        CHECK_THAT(18456.8, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("AddEm24");
        CHECK_FALSE(p.compile(("AddEm24(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1)")));
        }

    SECTION("23 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm23", AddEm23} });
        p.compile("AddEm23(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945)");
        CHECK_THAT(18454.7, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm23");
        CHECK_FALSE(p.compile("AddEm23(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945)"));
        }

    SECTION("22 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm22", AddEm22} });
        p.compile("AddEm22(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82, 9, 72.9, 8, 73, 2.3, -9, 8)");
        CHECK_THAT(9563.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm22");
        CHECK_FALSE(p.compile("AddEm22(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1, 2.1, 86.8, 82, 9, 72.9, 8, 73, 2.3, -9, 8)"));
        }

    SECTION("21 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm21", AddEm21} });
        p.compile("AddEm21(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82, 9, 72.9, 8, 73, 2.3, -9)");
        CHECK_THAT(9555.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm21");
        CHECK_FALSE(p.compile("AddEm21(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,2.1, 86.8, 82, 9, 72.9, 8, 73, 2.3, -9)"));
        }

    SECTION("20 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm20", AddEm20} });
        p.compile("AddEm20(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82, 9, 72.9, 8, 73, 2.3)");
        CHECK_THAT(9564.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm20");
        CHECK_FALSE(p.compile("AddEm20(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,2.1, 86.8, 82, 9, 72.9, 8, 73, 2.3)"));
        }

    SECTION("19 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm19", AddEm19} });
        p.compile("AddEm19(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82, 9, 72.9, 8, 73)");
        CHECK_THAT(9562.2, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm19");
        CHECK_FALSE(p.compile("AddEm19(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,2.1, 86.8, 82, 9, 72.9, 8, 73)"));
        }

    SECTION("18 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm18", AddEm18} });
        p.compile("AddEm18(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82, 9, 72.9, 8)");
        CHECK_THAT(9489.2, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm18");
        CHECK_FALSE(p.compile("AddEm18(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,2.1, 86.8, 82, 9, 72.9, 8)"));
        }

    SECTION("17 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm17", AddEm17} });
        p.compile("AddEm17(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82, 9, 72.9)");
        CHECK_THAT(9481.2, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm17");
        CHECK_FALSE(p.compile("AddEm17(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,2.1, 86.8, 82, 9, 72.9)"));
        }

    SECTION("16 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm16", AddEm16} });
        p.compile("AddEm16(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82, 9)");
        CHECK_THAT(9408.3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm16");
        CHECK_FALSE(p.compile("AddEm16(.2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,2.1, 86.8, 82, 9)"));
        }

    SECTION("15 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm15", AddEm15} });
        p.compile("AddEm15(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,"
                           "2.1, 86.8, 82)");
        CHECK_THAT(9399.3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm15");
        CHECK_FALSE(p.compile("AddEm15(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1,2.1, 86.8, 82))"));
        }

    SECTION("14 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm14", AddEm14} });
        p.compile("AddEm14(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1, 2.1, 69)");
        CHECK_THAT(9299.5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm14");
        CHECK_FALSE(p.compile("AddEm14(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1, 2.1, 69)"));
        }

    SECTION("13 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm13", AddEm13} });
        p.compile("AddEm13(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1, 69)");
        CHECK_THAT(9297.4, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm13");
        CHECK_FALSE(p.compile("AddEm13(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 2.1, 69)"));
        }

    SECTION("12 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm12", AddEm12} });
        p.compile("AddEm12(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 3.1)");
        CHECK_THAT(9229.4, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm12");
        CHECK_FALSE(p.compile("AddEm12(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945, 3.1)"));
        }

    SECTION("11 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm11", AddEm11} });
        p.compile("AddEm11(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945)");
        CHECK_THAT(9226.3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm11");
        CHECK_FALSE(p.compile("AddEm11(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98, 8945)"));
        }

    SECTION("10 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm10", AddEm10} });
        p.compile("AddEm10(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98)");
        CHECK_THAT(281.3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.remove_variable_or_function("AddEm10");
        CHECK_FALSE(p.compile("AddEm10(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2, 98)"));
        }

    SECTION("9 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm9", AddEm9} });
        p.compile("AddEm9(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2)");
        CHECK_THAT(183.3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("AddEm9");
        CHECK_FALSE(p.compile("AddEm9(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9, 7.2)"));
        }

    SECTION("8 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm8", AddEm8} });
        p.compile("AddEm8(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9)");
        CHECK_THAT(176.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("AddEm8");
        CHECK_FALSE(p.compile("AddEm8(2.1, 86.8, 2, 72.9, -5, 0.3, 8, 9)"));
        }

    SECTION("7 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm7", AddEm7} });
        p.compile("AddEm7(2.1, 86.8, 2, 72.9, -5, 0.3, 8)");
        CHECK_THAT(167.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("AddEm7");
        CHECK_FALSE(p.compile("AddEm7(2.1, 86.8, 2, 72.9, -5, 0.3, 8)"));
        }

    SECTION("6 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm6", AddEm6} });
        p.compile("AddEm6(2.1, 86.8, 2, 72.9, -5, 0.3)");
        CHECK_THAT(159.1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("AddEm6");
        CHECK_FALSE(p.compile("AddEm6(2.1, 86.8, 2, 72.9, -5, 0.3)"));
        }


    SECTION("5 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm5", AddEm5} });
        p.compile("AddEm5(2.1, 86.8, 2, 72.9, -5)");
        CHECK_THAT(158.8, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("AddEm5");
        CHECK_FALSE(p.compile("AddEm5(2.1, 86.8, 2, 72.9, -5)"));
        }

    SECTION("4 Parameters")
        {
        p.set_variables_and_functions({ {"AddEm4", AddEm4} });
        p.compile("AddEm4(2.1, 86.8, 2, 72.9)");
        CHECK_THAT(163.8, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        // remove function
        p.remove_variable_or_function("AddEm4");
        CHECK_FALSE(p.compile("AddEm4(2.1, 86.8, 2, 72.9)"));
        }

    SECTION("Custom variables")
        {
        p.set_variables_and_functions({ {"STRESS_L", static_cast<te_type>(10.1) },
            {"P_LEVEL", static_cast<te_type>(.5) } });
        p.compile("STRESS_L*P_LEVEL");
        CHECK_THAT(5.05, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.set_constant("P_LEVEL", static_cast<te_type>(.9));
        CHECK_THAT(9.09, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.compile(("IF(STRESS_L >= P_LEVEL, 1, 0)"));
        CHECK(1 == p.evaluate());
        }
    SECTION("Custom variables and if")
        {
        p.set_variables_and_functions({ {"smartMeter1.power", static_cast<te_type>(1'950.0) },
            {"sensor1.temperature", static_cast<te_type>(45.0) } });
        p.compile("IF(AND(smartMeter1.power > 1,900, sensor1.temperature < 52), "
            "TRUE, "
            "IF(AND(smartMeter1.power < 300, sensor1.temperature > 55), FALSE,"
            "NAN) )");
        CHECK(1 == p.evaluate());
        p.set_constant("smartMeter1.power", 200.0);
        p.set_constant("sensor1.temperature", 57.0);
        CHECK(0 == p.evaluate());
        // on accounted for scenario
        p.set_constant("smartMeter1.power", 500.0);
        p.set_constant("sensor1.temperature", 57.0);
        CHECK(std::isnan(p.evaluate()));
        }
    }

TEST_CASE("Funcs and vars with period", "[functions]")
    {
    te_parser p;

    SECTION("Custom test unknown parameters")
        {
        p.set_variables_and_functions({ { "MATH.MULT", __mult} });
        p.compile(("math.MULT(2,30,4,5)+1"));
        CHECK(1201 == p.evaluate());
        }
    SECTION("0 Parameters")
        {
        p.set_variables_and_functions({ {"MATH.Return5", return5} });
        p.compile(("math.Return5()"));
        CHECK_THAT(5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        }
    SECTION("2 Parameters")
        {
        p.set_variables_and_functions({ { "MATH.AddEm", AddEm} });
        p.compile(("math.ADDEM(2.1, 86.8)"));
        CHECK_THAT(88.9, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        }
    SECTION("Custom variables")
        {
        p.set_variables_and_functions({ {"STATS.STRESS_L", static_cast<te_type>(10.1) },
            {"stats.REGRESSION.P_LEVEL", static_cast<te_type>(.5) } });
        p.compile(("statS.STRESS_L*StAts.REGRESSION.P_LEVEL"));
        CHECK_THAT(5.05, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.set_constant("statS.REGRESSION.P_LEVEL", static_cast<te_type>(.9));
        CHECK_THAT(9.09, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.compile(("IF(StAts.STRESS_L >= Stats.REGRESSION.P_LEVEL, 1, 0)"));
        CHECK(1 == p.evaluate());
        // comma (instead of period) will cause a syntax error
        CHECK(std::isnan(p.evaluate(("STATS,STRESS_L*STATS.REGRESSION.P_LEVEL"))));
        CHECK(p.get_last_error_position() == 4);
        // incomplete scope on P_LEVEL
        CHECK(std::isnan(p.evaluate(("STATS.STRESS_L*STATS.P_LEVEL"))));
        CHECK(p.get_last_error_position() == 27);
        // stray space
        CHECK(std::isnan(p.evaluate(("STATS.STRESS_L*STATS. REGRESSION.P_LEVEL"))));
        CHECK(p.get_last_error_position() == 20);
        }
    }

TEST_CASE("Funcs and vars start with underscore", "[functions]")
    {
    te_parser p;

    SECTION("Custom test unknown parameters")
        {
        p.set_variables_and_functions({ { "__MATH.MULT", __mult} });
        p.compile(("__math.MULT(2,30,4,5)+1"));
        CHECK(1201 == p.evaluate());
        }
    SECTION("0 Parameters")
        {
        p.set_variables_and_functions({ {"_MATH.Return5", return5} });
        p.compile(("_math.Return5()"));
        CHECK_THAT(5, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        }
    SECTION("2 Parameters")
        {
        p.set_variables_and_functions({ { "_MATH.AddEm", AddEm} });
        p.compile(("_math.ADDEM(2.1, 86.8)"));
        CHECK_THAT(88.9, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        }
    SECTION("Custom variables")
        {
        p.set_variables_and_functions({ {"_STATS.STRESS_L", static_cast<te_type>(10.1) },
            {"_stats.REGRESSION.P_LEVEL", static_cast<te_type>(.5) } });
        p.compile(("_statS.STRESS_L*_StAts.REGRESSION.P_LEVEL"));
        CHECK_THAT(5.05, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.set_constant("_statS.REGRESSION.P_LEVEL", static_cast<te_type>(.9));
        CHECK_THAT(9.09, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
        p.compile(("IF(_StAts.STRESS_L >= _Stats.REGRESSION.P_LEVEL, 1, 0)"));
        CHECK(1 == p.evaluate());
        // comma (instead of period) will cause a syntax error
        CHECK(std::isnan(p.evaluate(("_STATS,STRESS_L*_STATS.REGRESSION.P_LEVEL"))));
        CHECK(p.get_last_error_position() == 5);
        // incomplete scope on P_LEVEL
        CHECK(std::isnan(p.evaluate(("_STATS.STRESS_L*_STATS.P_LEVEL"))));
        CHECK(p.get_last_error_position() == 29);
        // stray space
        CHECK(std::isnan(p.evaluate(("_STATS.STRESS_L*_STATS. REGRESSION.P_LEVEL"))));
        CHECK(p.get_last_error_position() == 22);
        }
    }

TEST_CASE("Complex", "[functions]")
    {
    te_parser tep;
    tep.set_variables_and_functions({ {"N_OBS", static_cast<te_type>(29.0) },
            {"P_LEVEL", static_cast<te_type>(.049) } });

    [[maybe_unused]] auto res = tep.evaluate(R"(
IF(AND(P_LEVEL < .05, N_OBS >= 30),
P_LEVEL,
NAN)
)");
    // successful parse, result was explicilty set to NaN by us
    CHECK(tep.success());
    CHECK(std::isnan(tep.get_result()));

    // we have enough observations now
    tep.set_constant("N_OBS", 31);
    CHECK_THAT(.049, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate())));

    // try it with some comments
    res = tep.evaluate(R"(
/* Returns the p-level of a study if:
   p-level < 5% AND
   number of observations in the study was at least 30.
   Otherwise, NaN is returned. */
IF(
// Review the results from the analysis
AND(P_LEVEL < .05, N_OBS >= 30),
// ...and return the p-level if we should use it
P_LEVEL,
// or NaN if not
NAN)
)");
    CHECK(tep.success());
    CHECK_THAT(.049, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate())));

    // same, but with & operator
    res = tep.evaluate(R"(
IF(P_LEVEL < .05 & N_OBS >= 30,
P_LEVEL,
NAN)
)");
    tep.set_constant("N_OBS", 31);
    CHECK_THAT(.049, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate())));

    tep.set_constant("P_LEVEL", static_cast<te_type>(.06));
    res = tep.evaluate(R"(
IF(P_LEVEL < .05 & N_OBS >= 30,
P_LEVEL,
NAN)
)");
    // successful parse, result p-level was too high
    CHECK(tep.success());
    CHECK(std::isnan(tep.get_result()));

    // OR will make it work now
    res = tep.evaluate(R"(
IF(P_LEVEL < .05 | N_OBS >= 30,
P_LEVEL,
NAN)
)");
    CHECK_THAT(.06, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate())));

    res = tep.evaluate(R"(
IF(OR(P_LEVEL < .05, N_OBS >= 30),
P_LEVEL,
NAN)
)");
    CHECK_THAT(.06, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate())));

    res = tep.evaluate(R"(/*Nothing but comments*/)");
    // no expression
    CHECK(std::isnan(tep.get_result()));

    // complicated formula
#ifndef TE_BITWISE_OPERATORS
    CHECK_THAT(4.5,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("ABS(((5+2) / (ABS(-2))) * -9 + 2) - 5^2"))));
#endif
    CHECK_THAT(4.5,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("ABS(((5+2) / (ABS(-2))) * -9 + 2) - 5**2"))));

    // make it look like an Excel function
#ifndef TE_BITWISE_OPERATORS
    CHECK_THAT(4.5,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("=ABS(((5+2) / (ABS(-2))) * -9 + 2) - 5^2"))));
#endif
    CHECK_THAT(4.5,
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("=ABS(((5+2) / (ABS(-2))) * -9 + 2) - 5**2"))));
    }

TEST_CASE("Permutation & Combination", "[math]")
    {
    te_parser p;

    // COMB
    p.compile(("COMBIN(15, 3)"));
    CHECK(455 == p.evaluate());
    CHECK(p.evaluate("COMBIN(8,2)") == 28);
    CHECK(p.evaluate("NCR(8,2)") == 28);

    CHECK(std::isnan(p.evaluate("COMBIN(-1, 3)")));
    CHECK(std::isnan(p.evaluate("COMBIN(8, -1)")));
    CHECK(std::isnan(p.evaluate("COMBIN(2, 3)")));
    // PERMUT
    p.compile(("PERMUT(15, 3)"));
    CHECK(2'730 == p.evaluate());
    CHECK(p.evaluate("PERMUT(15, 0)") == 1);
    CHECK(p.evaluate("PERMUT(3,2)") == 6);
    CHECK(p.evaluate("PERMUT(100,3)") == 970200);

    CHECK(std::isnan(p.evaluate("PERMUT(0, 3)")));
    CHECK(std::isnan(p.evaluate("PERMUT(-1, 3)")));
    
    CHECK(std::isnan(p.evaluate("PERMUT(15, -1)")));
    CHECK(std::isnan(p.evaluate("PERMUT(5, 6)")));
    }

TEST_CASE("Additional math functions", "[math]")
    {
    te_parser p;

    p.compile(("SQR(3)"));
    CHECK_THAT(9, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("SIN(3)"));
    CHECK_THAT(0.141120008, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("COS(7)"));
    CHECK_THAT(.7539, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("TAN(7)"));
    CHECK_THAT(.871447983, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("ATAN(7)"));
    CHECK_THAT(1.42889927, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("SINH(7)"));
    CHECK_THAT(548.316123, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("COSH(1)"));
    CHECK_THAT(1.54308, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("FLOOR(-3.2)"));
    CHECK_THAT(-4, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("FLOOR(3.2)"));
    CHECK_THAT(3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("CEIL(-3.2)"));
    CHECK_THAT(-3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("CEIL(3.2)"));
    CHECK_THAT(4, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("TRUNC(-3.2)"));
    CHECK_THAT(-3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("TRUNC(3.2)"));
    CHECK_THAT(3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("LOG10(10)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("LOG10(100)"));
    CHECK_THAT(2, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("LN(10)"));
    CHECK_THAT(2.30258509, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("LN(100)"));
    CHECK_THAT(4.60517019, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("ABS(-2.7)"));
    CHECK_THAT(2.7, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("ABS(68.84)"));
    CHECK_THAT(68.84, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("IF(0, 1, -1)"));
    CHECK_THAT(-1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("IF(1, 1, -1)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("POW(3, 3)"));
    CHECK_THAT(27, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("POW(3, 0)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("POW(-4, 2)"));
    CHECK_THAT(16, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("SIGN(-85.6)"));
    CHECK_THAT(-1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("SIGN(89.0)"));
    CHECK_THAT(1, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("SIGN(0)"));
    CHECK_THAT(0, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));

    p.compile(("COT(0.1)"));
    CHECK_THAT(9.9666, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("COT(1.57)"));
    CHECK_THAT(0.0007963, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("EXP(3)"));
    CHECK_THAT(20.085540, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate()), (WITHIN_TYPE)0.0001));

    p.compile(("SQRT(9)"));
    CHECK_THAT(3, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    p.compile(("SQRT(27.04)"));
    CHECK_THAT(5.2, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(p.evaluate())));
    }

TEST_CASE("Logical functions", "[logic]")
    {
    te_parser p;

    SECTION("TRUE/FALSE")
        {
        CHECK(p.evaluate("true"));
        CHECK(p.evaluate("TRUE"));
        CHECK(p.evaluate("TRUE()"));
        CHECK(p.evaluate("IF(TRUE(), TRUE, FALSE)"));
        CHECK(p.evaluate("IF(5 > 4, TRUE, FALSE)"));
        CHECK_FALSE(p.evaluate("IF(5 < 4, TRUE, FALSE)"));
        CHECK_FALSE(p.evaluate("false"));
        CHECK_FALSE(p.evaluate("FALSE"));
        CHECK_FALSE(p.evaluate("FALSE()"));
        }

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
    CHECK_THROWS(tep.add_variable_or_function({ "", static_cast<te_type>(5.0) }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "", static_cast<te_type>(5.0) } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Var WithSpace", static_cast<te_type>(5.0) } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Varÿ", static_cast<te_type>(5.0) } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Var,", static_cast<te_type>(5.0) } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Var$", static_cast<te_type>(5.0) } }));
    CHECK_THROWS(tep.set_variables_and_functions({ { "Var ", static_cast<te_type>(5.0) } }));

    // should be fine
    CHECK_NOTHROW(tep.set_variables_and_functions({ { "Var_OK74_", static_cast<te_type>(5.0) } }));
    }

TEST_CASE("Clamp", "[clamp]")
    {
    te_parser tep;

    CHECK(tep.evaluate("CLAMP(1, 1, 9)") == 1);
    CHECK(tep.evaluate("CLAMP(0, 1, 9)") == 1);
    CHECK(tep.evaluate("CLAMP(9, 1, 9)") == 9);
    CHECK(tep.evaluate("CLAMP(10, 1, 9)") == 9);
    CHECK(tep.evaluate("CLAMP(4, 1, 9)") == 4);
    // wrong order
    CHECK(tep.evaluate("CLAMP(10, 9, 1)") == 9);
    CHECK(tep.evaluate("CLAMP(0, 9, 1)") == 1);
    }

TEST_CASE("Lambdas", "[lambdas]")
    {
    te_parser tep;
    tep.set_variables_and_functions({
        { "mysum",
            [](te_type a, te_type b) noexcept
                { return a + b; } }
        });

    CHECK(tep.evaluate("MYSUM(5, 6)") == 11);
    }

TEST_CASE("Random", "[random]")
    {
    te_parser tep;
    // can't have reproducible results for rand, so just run it and make
    // sure it doesn't crash...
    CHECK_NOTHROW(tep.evaluate("rand()"));
    // ...and within 0-1
    auto res = tep.evaluate("rand()");
    CHECK((res >= 0 && res <= 1));
    }

TEST_CASE("Available functions", "[available]")
    {
    te_parser tep;
    // nothing to really test, just call it and make sure it doesn't crash
    CHECK_NOTHROW(tep.list_available_functions_and_variables());
    }

#ifndef TE_FLOAT
TEST_CASE("Bitwise operators", "[bitwise]")
    {
    te_parser tep;

    SECTION("BITOR")
        {
#ifdef TE_BITWISE_OPERATORS
        CHECK(tep.evaluate("23 | 10") == 31);
        CHECK(tep.evaluate("23 | 0") == (23 | 0));
        CHECK(tep.evaluate("0 | 10") == (0 | 10));
        // technical, negative should be OK, but Excel and LibreOffice
        // do not allow them, so we don't either
        CHECK(std::isnan(tep.evaluate("-15 | 17")));
        CHECK(std::isnan(tep.evaluate("17 | -15")));
        // max int 32-bit (64-bit int won't be supported if long double can't hold it)
        CHECK(tep.evaluate("4294967295 | 8000") ==
            (4294967295 | 8000));
        CHECK(tep.evaluate("8000 | 4294967295") ==
            (8000 | 4294967295));
#endif
        CHECK(tep.evaluate("=BITOR((2**48)-1, 1)") == 281474976710655);
        CHECK(tep.evaluate("=BITOR((2**48)-1, (2**48)-1)") == 281474976710655);
        CHECK(std::isnan(tep.evaluate("=BITOR((2**48)-1, (2**48))")));
        CHECK(tep.evaluate("BITOR(23, 10)") == 31);
        CHECK(tep.evaluate("BITOR(23, 0)") == (23 | 0));
        CHECK(tep.evaluate("BITOR(0, 10)") == (0 | 10));
        // technical, negative should be OK, but Excel and LibreOffice
        // do not allow them, so we don't either
        CHECK(std::isnan(tep.evaluate("BITOR(-15, 17)")));
        CHECK(std::isnan(tep.evaluate("BITOR(17, -15)")));
        // max int 32-bit (64-bit int won't be supported if long double can't hold it)
        CHECK(tep.evaluate("BITOR(4294967295, 8000)") ==
            (4294967295 | 8000));
        CHECK(tep.evaluate("BITOR(8000, 4294967295)") ==
            (8000 | 4294967295));
        }

    SECTION("BITXOR")
        {
#ifdef TE_BITWISE_OPERATORS
        CHECK(tep.evaluate("5 ^ 3") == 6);
        CHECK(tep.evaluate("5 ^ 9") == 12);
        CHECK(tep.evaluate("23^ 0") == (23 ^ 0));
        CHECK(tep.evaluate("0 ^10") == (0 ^ 10));
        // technical, negative should be OK, but Excel and LibreOffice
        // do not allow them, so we don't either
        CHECK(std::isnan(tep.evaluate("-15 ^ 17")));
        CHECK(std::isnan(tep.evaluate("17 ^ -15")));
        // max int 32-bit (64-bit int won't be supported if long double can't hold it)
        CHECK(tep.evaluate("4294967295^8000") ==
            (4294967295 ^ 8000));
        CHECK(tep.evaluate("8000  ^ 4294967295") ==
            (8000 ^ 4294967295));
#endif
        CHECK(tep.evaluate("=BITXOR((2**48)-1, 1)") == 281474976710654);
        CHECK(tep.evaluate("=BITXOR((2**48)-1, (2**48)-1)") == 0);
        CHECK(tep.evaluate("=BITXOR((2**48)-1, 1587)") == 281474976709068);
        CHECK(std::isnan(tep.evaluate("=BITXOR((2**48)-1, (2**48))")));
        CHECK(tep.evaluate("BITXOR(5,3)") == 6);
        CHECK(tep.evaluate("BITXOR(5,9)") == 12);
        CHECK(tep.evaluate("BITXOR(23, 0)") == (23 ^ 0));
        CHECK(tep.evaluate("BITXOR(0, 10)") == (0 ^ 10));
        // technical, negative should be OK, but Excel and LibreOffice
        // do not allow them, so we don't either
        CHECK(std::isnan(tep.evaluate("BITXOR(-15, 17)")));
        CHECK(std::isnan(tep.evaluate("BITXOR(17, -15)")));
        // max int 32-bit (64-bit int won't be supported if long double can't hold it)
        CHECK(tep.evaluate("BITXOR(4294967295, 8000)") ==
            (4294967295 ^ 8000));
        CHECK(tep.evaluate("BITXOR(8000, 4294967295)") ==
            (8000 ^ 4294967295));
        }

    SECTION("BITAND")
        {
#ifdef TE_BITWISE_OPERATORS
        CHECK(tep.evaluate("1 & 5") == 1);
        CHECK(tep.evaluate("13 & 25") == 9);
        CHECK(tep.evaluate("23 & 0") == (23 & 0));
        CHECK(tep.evaluate("0 & 10") == (0 & 10));
#endif
        CHECK(tep.evaluate("=BITAND((2**48)-1, 1)") == 1);
        CHECK(tep.evaluate("=BITAND((2**48)-1, (2**48)-1)") == 281474976710655);
        CHECK(tep.evaluate("=BITAND((2**48)-1, 1587)") == 1587);
        CHECK(std::isnan(tep.evaluate("=BITAND((2**48)-1, (2**48))")));
        CHECK(tep.evaluate("BITAND(1, 5)") == 1);
        CHECK(tep.evaluate("BITAND(13, 25)") == 9);
        CHECK(tep.evaluate("BITAND(23, 0)") == (23 & 0));
        CHECK(tep.evaluate("BITAND(0, 10)") == (0 & 10));
        // technical, negative should be OK, but Excel and LibreOffice
        // do not allow them, so we don't either
        CHECK(std::isnan(tep.evaluate("BITAND(-15, 17)")));
        CHECK(std::isnan(tep.evaluate("BITAND(17, -15)")));
        // max int 32-bit (64-bit int won't be supported if long double can't hold it)
        CHECK(tep.evaluate("BITAND(4294967295, 8000)") ==
            (4294967295 & 8000));
        CHECK(tep.evaluate("BITAND(8000, 4294967295)") ==
            (8000 & 4294967295));
        }

    SECTION("BITNOT8")
        {
        for (uint8_t i = 0; i < std::numeric_limits<decltype(i)>::max(); ++i)
            {
            decltype(i) res = ~i;
            REQUIRE(tep.evaluate("=BITNOT8(" + std::to_string(i) + ")") == res);
            }
        }

    SECTION("BITNOT16")
        {
        for (uint16_t i = 0; i < std::numeric_limits<decltype(i)>::max(); ++i)
            {
            decltype(i) res = ~i;
            REQUIRE(tep.evaluate("=BITNOT16(" + std::to_string(i) + ")") == res);
            }
        // Excel example
        REQUIRE(tep.evaluate("=BITNOT16(6)") == 65529);
        }

    SECTION("BITNOT32")
        {
        // not practical to check every possible value, so do the extremes and middle
        uint32_t val{ std::numeric_limits<uint32_t>::max() };
        decltype(val) res = ~val;
        CHECK(tep.evaluate("=BITNOT32(" + std::to_string(val) + ")") == res);

        val /= 2;
        res = ~val;
        CHECK(tep.evaluate("=BITNOT32(" + std::to_string(val) + ")") == res);

        val = 0;
        res = ~val;
        CHECK(tep.evaluate("=BITNOT32(" + std::to_string(val) + ")") == res);

        // ~ falling back to 32-bit
        if constexpr(!te_parser::supports_64bit() &&
            te_parser::supports_32bit())
            {
            val = std::numeric_limits<uint32_t>::max();
            decltype(val) res2 = ~val;
            CHECK(tep.evaluate("~" + std::to_string(val)) == res2);

            val /= 2;
            res2 = ~val;
            CHECK(tep.evaluate("~" + std::to_string(val)) == res2);

            val = 1986;
            res2 = ~val;
            CHECK(tep.evaluate("~" + std::to_string(val)) == res2);
            CHECK(tep.evaluate("+~1986") == res2);
            CHECK(tep.evaluate("~+1986") == res2);
            }
        }

    SECTION("BITNOT64")
        {
        if constexpr(te_parser::supports_64bit())
            {
            // not practical to check every possible value, so do the extremes and middle
            uint64_t val{ std::numeric_limits<uint64_t>::max() };
            decltype(val) res = ~val;
            CHECK(tep.evaluate("=BITNOT64(" + std::to_string(val) + ")") == res);

            val /= 2;
            res = ~val;
            CHECK(tep.evaluate("=BITNOT64(" + std::to_string(val) + ")") == res);

            val = 0;
            res = ~val;
            CHECK(tep.evaluate("=BITNOT64(" + std::to_string(val) + ")") == res);
            }
        else
            {
            CHECK(std::isnan(tep.evaluate("=BITNOT64(0)")));
            }
        }
    }
#endif

#if __cplusplus >= 202002L && !defined(TE_FLOAT)
TEST_CASE("Rotate operators", "[rotate]")
    {
    te_parser tep;

    SECTION("BITLROTATE8")
        {
        constexpr uint8_t i = std::numeric_limits<uint8_t>::max();
        CHECK(tep.evaluate("BITLROTATE8(0, 0)") == std::rotl((uint8_t)0, 0));
        CHECK(tep.evaluate("BITLROTATE8(255, 0)") == std::rotl(i, 0));
        CHECK(tep.evaluate("BITLROTATE8(255, 1)") == std::rotl(i, 1));
        CHECK(tep.evaluate("BITLROTATE8(255, 4)") == std::rotl(i, 4));
        CHECK(std::isnan(tep.evaluate("BITLROTATE8(255, 9)")));
        CHECK(tep.evaluate("BITLROTATE8(255, -1)") == std::rotl(i, -1));
        }
    SECTION("BITLROTATE16")
        {
        constexpr uint16_t i = std::numeric_limits<uint16_t>::max();
        CHECK(tep.evaluate("BITLROTATE16(0, 0)") == std::rotl((uint16_t)0, 0));
        CHECK(tep.evaluate("BITLROTATE16(65535, 0)") == std::rotl(i, 0));
        CHECK(tep.evaluate("BITLROTATE16(65535, 1)") == std::rotl(i, 1));
        CHECK(tep.evaluate("BITLROTATE16(65535, 4)") == std::rotl(i, 4));
        CHECK(tep.evaluate("BITLROTATE16(65535, 9)") == std::rotl(i, 9));
        CHECK(tep.evaluate("BITLROTATE16(65535, -1)") == std::rotl(i, -1));
        }
    SECTION("BITLROTATE32")
        {
        constexpr uint32_t i = std::numeric_limits<uint32_t>::max();
        CHECK(tep.evaluate("BITLROTATE32(0, 0)") == std::rotl((uint32_t)0, 0));
        CHECK(tep.evaluate("BITLROTATE32(4294967295, 0)") == std::rotl(i, 0));
        CHECK(tep.evaluate("BITLROTATE32(4294967295, 1)") == std::rotl(i, 1));
        CHECK(tep.evaluate("BITLROTATE32(4294967295, 4)") == std::rotl(i, 4));
        CHECK(tep.evaluate("BITLROTATE32(4294967295, 9)") == std::rotl(i, 9));
        CHECK(tep.evaluate("BITLROTATE32(4294967295, -1)") == std::rotl(i, -1));
        }
    SECTION("BITLROTATE")
        {
        // malformed
        CHECK(std::isnan(tep.evaluate("5 <")));
        CHECK(std::isnan(tep.evaluate("5 <<")));
        CHECK(std::isnan(tep.evaluate("5 <<<")));

        if constexpr(te_parser::supports_64bit())
            {
            const std::uint64_t i = 4294967295;
            CHECK(tep.evaluate("0 <<< 0") == std::rotl((uint64_t)0, 0));
            CHECK(tep.evaluate("4294967295 <<< 0") == std::rotl(i, 0));
            CHECK(tep.evaluate("4294967295 <<< 1") == std::rotl(i, 1));
            CHECK(tep.evaluate("4294967295 <<< 4") == std::rotl(i, 4));
            CHECK(tep.evaluate("4294967295 <<< 9") == std::rotl(i, 9));
            CHECK(tep.evaluate("4294967295 <<< -1") == std::rotl(i, -1));

            CHECK(tep.evaluate("BITLROTATE(0, 0)") == std::rotl((uint64_t)0, 0));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 0)") == std::rotl(i, 0));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 1)") == std::rotl(i, 1));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 4)") == std::rotl(i, 4));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 9)") == std::rotl(i, 9));
            CHECK(tep.evaluate("BITLROTATE(4294967295, -1)") == std::rotl(i, -1));
            }
        else if constexpr (te_parser::supports_32bit())
            {
            const std::uint32_t i = 4294967295;
            CHECK(tep.evaluate("0 <<< 0") == std::rotl((uint32_t)0, 0));
            CHECK(tep.evaluate("4294967295 <<< 0") == std::rotl(i, 0));
            CHECK(tep.evaluate("4294967295 <<< 1") == std::rotl(i, 1));
            CHECK(tep.evaluate("4294967295 <<< 4") == std::rotl(i, 4));
            CHECK(tep.evaluate("4294967295 <<< 9") == std::rotl(i, 9));
            CHECK(tep.evaluate("4294967295 <<< -1") == std::rotl(i, -1));

            CHECK(tep.evaluate("BITLROTATE(0, 0)") == std::rotl((uint32_t)0, 0));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 0)") == std::rotl(i, 0));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 1)") == std::rotl(i, 1));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 4)") == std::rotl(i, 4));
            CHECK(tep.evaluate("BITLROTATE(4294967295, 9)") == std::rotl(i, 9));
            CHECK(tep.evaluate("BITLROTATE(4294967295, -1)") == std::rotl(i, -1));
            }
        }

    SECTION("BITRROTATE8")
        {
        constexpr std::uint8_t i = std::numeric_limits<uint8_t>::max();
        CHECK(tep.evaluate("BITRROTATE8(0, 0)") == std::rotr((uint8_t)0, 0));
        CHECK(tep.evaluate("BITRROTATE8(255, 0)") == std::rotr(i, 0));
        CHECK(tep.evaluate("BITRROTATE8(255, 1)") == std::rotr(i, 1));
        CHECK(tep.evaluate("BITRROTATE8(255, 4)") == std::rotr(i, 4));
        CHECK(std::isnan(tep.evaluate("BITRROTATE8(255, 9)")));
        CHECK(tep.evaluate("BITRROTATE8(255, -1)") == std::rotr(i, -1));
        }
    SECTION("BITRROTATE16")
        {
        constexpr std::uint16_t i = std::numeric_limits<uint16_t>::max();
        CHECK(tep.evaluate("BITRROTATE16(0, 0)") == std::rotr((uint16_t)0, 0));
        CHECK(tep.evaluate("BITRROTATE16(65535, 0)") == std::rotr(i, 0));
        CHECK(tep.evaluate("BITRROTATE16(65535, 1)") == std::rotr(i, 1));
        CHECK(tep.evaluate("BITRROTATE16(65535, 4)") == std::rotr(i, 4));
        CHECK(tep.evaluate("BITRROTATE16(65535, 9)") == std::rotr(i, 9));
        CHECK(tep.evaluate("BITRROTATE16(65535, -1)") == std::rotr(i, -1));
        }
    SECTION("BITRROTATE32")
        {
        constexpr std::uint32_t i = std::numeric_limits<uint32_t>::max();
        CHECK(tep.evaluate("BITRROTATE32(0, 0)") == std::rotr((uint32_t)0, 0));
        CHECK(tep.evaluate("BITRROTATE32(4294967295, 0)") == std::rotr(i, 0));
        CHECK(tep.evaluate("BITRROTATE32(4294967295, 1)") == std::rotr(i, 1));
        CHECK(tep.evaluate("BITRROTATE32(4294967295, 4)") == std::rotr(i, 4));
        CHECK(tep.evaluate("BITRROTATE32(4294967295, 9)") == std::rotr(i, 9));
        CHECK(tep.evaluate("BITRROTATE32(4294967295, -1)") == std::rotr(i, -1));
        }
    SECTION("BITRROTATE")
        {
        // malformed
        CHECK(std::isnan(tep.evaluate("5 >")));
        CHECK(std::isnan(tep.evaluate("5 >>")));
        CHECK(std::isnan(tep.evaluate("5 >>>")));

        if constexpr (te_parser::supports_64bit())
            {
            constexpr std::uint64_t i = std::numeric_limits<uint64_t>::max();
            CHECK(tep.evaluate("0 >>> 0") == std::rotr((uint64_t)0, 0));
            CHECK(tep.evaluate(std::to_string(i) + " >>> 0") == std::rotr(i, 0));
            CHECK(tep.evaluate(std::to_string(i) + " >>> 1") == std::rotr(i, 1));
            CHECK(tep.evaluate(std::to_string(i) + " >>> 4") == std::rotr(i, 4));
            CHECK(tep.evaluate(std::to_string(i) + " >>> 9") == std::rotr(i, 9));
            CHECK(tep.evaluate(std::to_string(i) + " >>> -1") == std::rotr(i, -1));

            CHECK(tep.evaluate("BITRROTATE64(" + std::to_string(i) + ", 0)") == std::rotr(i, 0));
            CHECK(tep.evaluate("BITRROTATE64(" + std::to_string(i) + ", 1)") == std::rotr(i, 1));
            CHECK(tep.evaluate("BITRROTATE64(" + std::to_string(i) + ", 4)") == std::rotr(i, 4));
            CHECK(tep.evaluate("BITRROTATE64(" + std::to_string(i) + ", 9)") == std::rotr(i, 9));
            CHECK(tep.evaluate("BITRROTATE64(" + std::to_string(i) + ", -1)") == std::rotr(i, -1));

            CHECK(tep.evaluate("BITRROTATE(0, 0)") == std::rotr((uint64_t)0, 0));
            CHECK(tep.evaluate("BITRROTATE(" + std::to_string(i) + ", 0)") == std::rotr(i, 0));
            CHECK(tep.evaluate("BITRROTATE(" + std::to_string(i) + ", 1)") == std::rotr(i, 1));
            CHECK(tep.evaluate("BITRROTATE(" + std::to_string(i) + ", 4)") == std::rotr(i, 4));
            CHECK(tep.evaluate("BITRROTATE(" + std::to_string(i) + ", 9)") == std::rotr(i, 9));
            CHECK(tep.evaluate("BITRROTATE(" + std::to_string(i) + ", -1)") == std::rotr(i, -1));
            }
        else if constexpr (te_parser::supports_32bit())
            {
            constexpr std::uint32_t i = std::numeric_limits<uint32_t>::max();
            CHECK(tep.evaluate("0 >>> 0") == std::rotr((uint32_t)0, 0));
            CHECK(tep.evaluate("4294967295 >>> 0") == std::rotr(i, 0));
            CHECK(tep.evaluate("4294967295 >>> 1") == std::rotr(i, 1));
            CHECK(tep.evaluate("4294967295 >>> 4") == std::rotr(i, 4));
            CHECK(tep.evaluate("4294967295 >>> 9") == std::rotr(i, 9));
            CHECK(tep.evaluate("4294967295 >>> -1") == std::rotr(i, -1));

            CHECK(tep.evaluate("BITRROTATE(0, 0)") == std::rotr((uint32_t)0, 0));
            CHECK(tep.evaluate("BITRROTATE(4294967295, 0)") == std::rotr(i, 0));
            CHECK(tep.evaluate("BITRROTATE(4294967295, 1)") == std::rotr(i, 1));
            CHECK(tep.evaluate("BITRROTATE(4294967295, 4)") == std::rotr(i, 4));
            CHECK(tep.evaluate("BITRROTATE(4294967295, 9)") == std::rotr(i, 9));
            CHECK(tep.evaluate("BITRROTATE(4294967295, -1)") == std::rotr(i, -1));
            }
        }
    }
#endif

#ifndef TE_FLOAT
TEST_CASE("Shift operators", "[shift]")
    {
    te_parser tep;

    for (uint64_t i = 0; i < te_parser::get_max_integer_bitness() + (te_parser::supports_64bit() ? 0 : 1); ++i)
        {
        INFO("Shift: " + std::to_string(i));
        CHECK(tep.evaluate((std::string("1 << ") + std::to_string(i)).c_str()) == ((uint64_t)1 << i));
        CHECK(tep.evaluate((std::string("1 >> ") + std::to_string(i)).c_str()) == ((uint64_t)1 >> i));
        }
    for (uint64_t i = 0; i < te_parser::get_max_integer_bitness() + (te_parser::supports_64bit() ? -1 : 1); ++i)
        {
        INFO("Shift: " + std::to_string(i));
        CHECK(tep.evaluate((std::string("2 << ") + std::to_string(i)).c_str()) == ((uint64_t)2 << i));
        CHECK(tep.evaluate((std::string("2 >> ") + std::to_string(i)).c_str()) == ((uint64_t)2 >> i));
        }
    // will be too large, even for 64-bit
    CHECK(std::isnan(tep.evaluate("2 << 63")));
    SECTION("BITLSHIFT")
        {
        CHECK(tep.evaluate("BITLSHIFT(2, 25)") == 67108864);
        CHECK(tep.evaluate("BITLSHIFT(0, 25)") == 0);
        CHECK(tep.evaluate("BITLSHIFT(5, 8)") == 1280);
        CHECK(tep.evaluate("BITLSHIFT(5, 0)") == 5);
        // negative turns it into a right shift
        CHECK(tep.evaluate("BITLSHIFT(500, -2)") == 125);
        }
    SECTION("BITRSHIFT")
        {
        CHECK(tep.evaluate("BITRSHIFT(13, 2)") == 3);
        CHECK(tep.evaluate("BITRSHIFT(10, 0)") == 10);
        CHECK(tep.evaluate("BITRSHIFT(1024, 4)") == 64);
        CHECK(tep.evaluate("BITRSHIFT(500, 2)") == 125);
        CHECK(tep.get_last_error_message().empty());
        // negative turns it into a left shift
        CHECK(tep.evaluate("BITRSHIFT(2, -4)") == 32);
        }
    SECTION("Left")
        {
        CHECK(tep.evaluate("0 << 4") == ((uint64_t)0 << 4));
        if constexpr(te_parser::supports_64bit())
            {
            CHECK(tep.compile("1 << 54"));
            CHECK(tep.evaluate("1 << 63") == ((uint64_t)1 << 63));
            }
        else
            {
            CHECK_FALSE(tep.compile("1 << 54"));
            CHECK(std::isnan(tep.evaluate()));
            CHECK(std::isnan(tep.evaluate("1 << 63")));
            }
        CHECK(std::isnan(tep.evaluate("1 << -5")));
        CHECK(tep.evaluate("31 << 53") == ((uint64_t)31 << 53));
        // overflow
        CHECK(std::isnan(tep.evaluate("32 << 59")));
        CHECK(std::isnan(tep.evaluate("2 << 63")));
        CHECK(std::isnan(tep.evaluate("-1 << 2")));
        CHECK(tep.evaluate("1.0 << 4.0") == ((uint64_t)1 << 4));
        CHECK(std::isnan(tep.evaluate("1.01 << 2")));
        CHECK(std::isnan(tep.evaluate("1 << 2.001")));
        // You may get a warning like such:
        // warning C4554: '<<': check operator precedence for possible error; use parentheses to clarify precedence
        // Good advice, but in this case we do follow the order of precedence where << and >> are the lowest
        // of precedence amongst the operators and that's what we are testing
        // (the compiler will do the same).
        CHECK(tep.evaluate("(3 + 2 << 4 - 1)") == (3 + (uint64_t)2 << 4 - 1));
        CHECK(tep.evaluate("(3 + 2 << 4 - 1)") == ((uint64_t)5 << 3));
        CHECK(tep.evaluate("(3 + 2 << 2 * 2)") == (3 + (uint64_t)2 << 2 * 2));
        // error state is reset
        CHECK(tep.compile("1 << 10"));
        CHECK(tep.evaluate() == 1 << 10);
        CHECK(tep.get_last_error_message().empty());
        }
    SECTION("Right")
        {
        CHECK(tep.evaluate("0 >> 4") == ((uint64_t)0 >> 4));
        if constexpr (te_parser::supports_64bit())
            {
            CHECK(tep.evaluate("1 >> 63") == ((uint64_t)1 >> 63));
            }
        else
            {
            CHECK(std::isnan(tep.evaluate("1 >> 63")));
            }
        CHECK(std::isnan(tep.evaluate("1 >> -5")));
        CHECK(std::isnan(tep.get_result()));
        CHECK(tep.evaluate("32 >> 4") == ((uint64_t)32 >> 4));
        CHECK(tep.evaluate("32 >> 5") == ((uint64_t)32 >> 5));
        // (32 / 64) = 0.5, which is floored to zero
        CHECK(tep.evaluate("32 >> 6") == ((uint64_t)32 >> 6));
        CHECK(std::isnan(tep.evaluate("-1 >> 2")));
        CHECK(std::isnan(tep.get_result()));
        CHECK(tep.evaluate("1.0 >> 4.0") == ((uint64_t)1 >> 4));
        CHECK(std::isnan(tep.evaluate("1.01 >> 2")));
        CHECK(tep.get_last_error_message() == "Left side of right shift (>>) operation must be an integer.");
        CHECK(std::isnan(tep.get_result()));
        CHECK(std::isnan(tep.evaluate("1 >> 2.001")));
        CHECK(std::isnan(tep.get_result()));

        CHECK(tep.evaluate("(3 + 2 >> 4 - 1)") == (3 + (uint64_t)2 >> 4 - 1));
        CHECK(tep.evaluate("(3 + 2 >> 4 - 1)") == ((uint64_t)5 >> 3));
        CHECK(tep.evaluate("(3 + 2 >> 2 * 2)") == (3 + (uint64_t)2 >> 2 * 2));

        // error state is reset
        CHECK(tep.compile("1 << 10"));
        CHECK(tep.evaluate() == 1 << 10);
        CHECK(tep.get_last_error_message().empty());
        }
    }
#elif defined(TE_FLOAT)
    // just make sure bitwise operators cause an error as they aren't supported for float
    TEST_CASE("Bitwise operators null", "[shift,rotate]")
        {
        te_parser tep;

        CHECK(std::isnan(tep.evaluate("0 >> 4")));
        CHECK(std::isnan(tep.evaluate("0 >>> 4")));
        CHECK(std::isnan(tep.evaluate("0 << 4")));
        CHECK(std::isnan(tep.evaluate("0 <<< 4")));
        }
#endif

te_type ResolveResolutionSymbols(std::string_view str)
    {
    return (str == "RES" || str == "RESOLUTION") ?
        96 : te_parser::te_nan;
    }

TEST_CASE("Unknown symbol resolve funct pointer keep resolved", "[usr]")
    {
    te_parser tep;
    tep.set_unknown_symbol_resolver(ResolveResolutionSymbols);

    CHECK(tep.evaluate("RESOLUTION * 3") == 3 * 96);
    // is in the parser now and can be recognized case sensitively
    CHECK(tep.evaluate("resolution * 5") == 480);
    }

TEST_CASE("Unknown symbol resolve funct pointer purge resolved", "[usr]")
    {
    te_parser tep;
    tep.set_unknown_symbol_resolver(ResolveResolutionSymbols, false);

    CHECK(tep.evaluate("RESOLUTION * 3") == 3 * 96);
    // not in the parser, so case sensitive look up will fail
    CHECK(std::isnan(tep.evaluate("resolution * 5")));
    }

TEST_CASE("Unknown symbol resolve funct pointer purge resolved 2", "[usr]")
    {
    std::string str("id.temperature < 51");
    te_parser parser;
    parser.set_unknown_symbol_resolver([]([[maybe_unused]] std::string_view symbol)
        {
        static te_type temperature = 49.0;
        return temperature += 1.0;
        }, false);
    CHECK(parser.compile(str));        // 50
    CHECK_FALSE(parser.evaluate(str)); // 51
    CHECK_FALSE(parser.evaluate(str)); // 52
    CHECK(parser.evaluate("id.temperature") == 53);
    }

TEST_CASE("Unknown symbol resolve lambda with capture", "[usr]")
    {
    std::string str("id.temperature < 51");
    te_type temperature = 49.0;
    te_parser parser;
    parser.set_unknown_symbol_resolver([&]([[maybe_unused]] std::string_view symbol)
        {
        return temperature += 1.0;
        }, false);
    CHECK(parser.compile(str));        // 50
    CHECK_FALSE(parser.evaluate(str)); // 51
    CHECK_FALSE(parser.evaluate(str)); // 52
    CHECK(parser.evaluate("id.temperature") == 53);
    }

TEST_CASE("Unknown symbol resolve 1 param purged", "[usr]")
    {
    te_parser tep;
    tep.set_unknown_symbol_resolver(
        [](std::string_view str) -> te_type
        {
        static te_type stressLevel{ 3 };
        if (std::strncmp(str.data(), "STRESS", 6) == 0)
            { return stressLevel++; }
        else
            { return te_parser::te_nan; }
        },
        // purge resolved varialbes after each evaluation
        false);

    CHECK(tep.evaluate("STRESS_LEVEL") == 3);
    CHECK(tep.evaluate("STRESS_LEVEL") == 4);
    CHECK(tep.evaluate("STRESS_LEVEL") == 5);
    CHECK(tep.evaluate("STRESS_LEVEL") == 6);
    CHECK(tep.compile("STRESS_LEVEL"));
    CHECK(tep.evaluate() == 7);
    }

TEST_CASE("Unknown symbol resolve 1 param", "[usr]")
    {
    te_parser tep;
    tep.set_unknown_symbol_resolver(
        [](std::string_view str) -> te_type
        {
        if (std::strncmp(str.data(), "STRESS_LOW", str.length()) == 0)
            { return 2; }
        else if (std::strncmp(str.data(), "STRESS_HIGH", str.length()) == 0)
            { return 8; }
        else
            { return te_parser::te_nan; }
        });

    CHECK(tep.evaluate("STRESS_LOW * 5") == 10);
    CHECK(tep.evaluate("STRESS_HIGH * 5") == 40);
    // STRESS_LOW will be in the parser now, won't need to be resolved
    CHECK(tep.evaluate("STRESS_LOW * 1") == 2);
    tep.set_constant("STRESS_LOW", 1);
    CHECK(tep.evaluate("STRESS_LOW * 1") == 1); // change it outside of the resolver
    // won't be resolved
    CHECK(std::isnan(tep.evaluate("STRESS_UNK * 5")));
    CHECK(tep.get_last_error_position() == 9);
    }

TEST_CASE("Unknown symbol resolve 2 param", "[usr]")
    {
    te_parser tep;
    tep.set_unknown_symbol_resolver(
        [](std::string_view str, std::string& message) -> te_type
        {
        if (std::strncmp(str.data(), "STRESS_LOW", str.length()) == 0)
            {
            message = "STRESS constant being set.";
            return 2;
            }
        else if (std::strncmp(str.data(), "STRESS_HIGH", str.length()) == 0)
            {
            message = "STRESS constant being set.";
            return 8;
            }
        else
            {
            message = "Unknown stress level!";
            return te_parser::te_nan;
            }
        });

    CHECK(tep.evaluate("STRESS_LOW * 5") == 10);
    CHECK(tep.get_last_error_message() == "STRESS constant being set.");
    CHECK(tep.evaluate("STRESS_HIGH * 5") == 40);
    // STRESS_LOW will be in the parser now, won't need to be resolved
    CHECK(tep.evaluate("STRESS_LOW * 1") == 2);
    tep.set_constant("STRESS_LOW", 1);
    CHECK(tep.evaluate("STRESS_LOW * 1") == 1); // change it outside of the resolver
    // won't be resolved
    CHECK(std::isnan(tep.evaluate("STRESS_UNK * 5")));
    CHECK(tep.get_last_error_position() == 9);
    CHECK(tep.get_last_error_message() == "Unknown stress level!");
    }

TEST_CASE("Unknown symbol resolve disable", "[usr]")
    {
    te_parser tep;
    tep.set_unknown_symbol_resolver(
        [](std::string_view str, std::string& message) -> te_type
        {
        if (std::strncmp(str.data(), "STRESS_LOW", str.length()) == 0)
            {
            message = "STRESS constant being set.";
            return 2;
            }
        else if (std::strncmp(str.data(), "STRESS_HIGH", str.length()) == 0)
            {
            message = "STRESS constant being set.";
            return 8;
            }
        else
            {
            message = "Unknown stress level!";
            return te_parser::te_nan;
            }
        });

    CHECK(tep.evaluate("STRESS_LOW * 5") == 10);
    tep.set_unknown_symbol_resolver(te_usr_noop{});
    // user-defined USR has been swapped out with a no-op, so
    // STRESS_HIGH won't be resolved
    CHECK(std::isnan(tep.evaluate("STRESS_HIGH * 5")));
    CHECK(tep.get_last_error_position() == 10);
    }

TEST_CASE("Unknown symbol resolve throws", "[usr]")
    {
    te_parser tep;
    tep.set_unknown_symbol_resolver(
        [](std::string_view str) -> te_type
        {
        if (std::strncmp(str.data(), "STRESS_LOW", str.length()) == 0)
            { return 2; }
        else if (std::strncmp(str.data(), "STRESS_HIGH", str.length()) == 0)
            { return 8; }
        else
            { throw std::runtime_error("Unknown stress level!"); }
        });

    // won't be resolved
    CHECK(std::isnan(tep.evaluate("STRESS_UNK * 5")));
    CHECK(tep.get_last_error_position() == 9);
    CHECK(tep.get_last_error_message() == "Unknown stress level!");
    }

TEST_CASE("Unknown symbol resolve dynamic", "[usr]")
    {
    te_parser tep;

    // Create a handler for undefined tokens that will recognize
    // dynamic strings like "FY2004" or "FY1997" and convert them to 2004 and 1997.
    tep.set_unknown_symbol_resolver(
        // Handler should except a string (which will be the unrecognized token)
        // and return a te_type.
        [](std::string_view str) -> te_type
        {
        const std::regex re{ "FY([0-9]{4})",
            std::regex_constants::icase | std::regex_constants::ECMAScript };
        std::smatch matches;
        std::string var{ str };
        if (std::regex_search(var.cbegin(), var.cend(), matches, re))
            {
            // Unrecognized token is something like "FY1982," so extract "1982"
            // from that and return 1982 as a number. At this point, the variable
            // "FY1982" will added to the parser and set to 1982. All future
            // evaluations will see this as 1982 (unless set_constant() is called
            // to change it).
            if (matches.size() > 1)
                { return static_cast<te_type>(std::atol(matches[1].str().c_str())); }
            else
                { return te_parser::te_nan; }
            }
        // Can't resolve what this token is, so return NaN.
        else
            { return te_parser::te_nan; }
        });

    CHECK(tep.evaluate("-(FY1999-FY2009)") == 10);
    }

TEST_CASE("String comparison helper", "[stringcmp]")
    {
    SECTION("Operator()")
        {
        te_string_less sl;

        CHECK_FALSE(sl("", ""));
        CHECK_FALSE(sl("a", "a"));
        CHECK(sl("", "a"));
        CHECK(sl("a", "b"));
        CHECK(sl("abc", "abcd"));
        CHECK_FALSE(sl("abcd", "abcd"));
        CHECK_FALSE(sl("z", "abcd"));
        CHECK(sl("abc", "z"));

        CHECK_FALSE(sl("A", "a"));
        CHECK_FALSE(sl("a", "A"));
        CHECK(sl("A", "b"));
        CHECK(sl("a", "B"));
        CHECK(sl("Abc", "abcd"));
        CHECK(sl("abc", "ABCD"));
        CHECK_FALSE(sl("ABCD", "abcd"));
        CHECK_FALSE(sl("abcd", "ABCD"));
        CHECK_FALSE(sl("z", "ABCD"));
        CHECK(sl("ABC", "z"));
        }
    SECTION("tolower")
        {
        te_string_less sl;

        CHECK(sl.tolower('A') == 'a');
        CHECK(sl.tolower('B') == 'b');
        CHECK(sl.tolower('C') == 'c');
        CHECK(sl.tolower('D') == 'd');
        CHECK(sl.tolower('E') == 'e');
        CHECK(sl.tolower('F') == 'f');
        CHECK(sl.tolower('G') == 'g');
        CHECK(sl.tolower('H') == 'h');
        CHECK(sl.tolower('I') == 'i');
        CHECK(sl.tolower('J') == 'j');
        CHECK(sl.tolower('K') == 'k');
        CHECK(sl.tolower('L') == 'l');
        CHECK(sl.tolower('M') == 'm');
        CHECK(sl.tolower('N') == 'n');
        CHECK(sl.tolower('O') == 'o');
        CHECK(sl.tolower('P') == 'p');
        CHECK(sl.tolower('Q') == 'q');
        CHECK(sl.tolower('R') == 'r');
        CHECK(sl.tolower('S') == 's');
        CHECK(sl.tolower('T') == 't');
        CHECK(sl.tolower('U') == 'u');
        CHECK(sl.tolower('V') == 'v');
        CHECK(sl.tolower('W') == 'w');
        CHECK(sl.tolower('X') == 'x');
        CHECK(sl.tolower('Y') == 'y');
        CHECK(sl.tolower('Z') == 'z');

        CHECK(sl.tolower('a') == 'a');
        CHECK(sl.tolower('b') == 'b');
        CHECK(sl.tolower('c') == 'c');
        CHECK(sl.tolower('d') == 'd');
        CHECK(sl.tolower('e') == 'e');
        CHECK(sl.tolower('f') == 'f');
        CHECK(sl.tolower('g') == 'g');
        CHECK(sl.tolower('h') == 'h');
        CHECK(sl.tolower('i') == 'i');
        CHECK(sl.tolower('j') == 'j');
        CHECK(sl.tolower('k') == 'k');
        CHECK(sl.tolower('l') == 'l');
        CHECK(sl.tolower('m') == 'm');
        CHECK(sl.tolower('n') == 'n');
        CHECK(sl.tolower('o') == 'o');
        CHECK(sl.tolower('p') == 'p');
        CHECK(sl.tolower('q') == 'q');
        CHECK(sl.tolower('r') == 'r');
        CHECK(sl.tolower('s') == 's');
        CHECK(sl.tolower('t') == 't');
        CHECK(sl.tolower('u') == 'u');
        CHECK(sl.tolower('v') == 'v');
        CHECK(sl.tolower('w') == 'w');
        CHECK(sl.tolower('x') == 'x');
        CHECK(sl.tolower('y') == 'y');
        CHECK(sl.tolower('z') == 'z');

        CHECK(sl.tolower('_') == '_');
        CHECK(sl.tolower('.') == '.');
        CHECK(sl.tolower('0') == '0');
        CHECK(sl.tolower('1') == '1');
        CHECK(sl.tolower('2') == '2');
        CHECK(sl.tolower('3') == '3');
        CHECK(sl.tolower('4') == '4');
        CHECK(sl.tolower('5') == '5');
        CHECK(sl.tolower('6') == '6');
        CHECK(sl.tolower('7') == '7');
        CHECK(sl.tolower('8') == '8');
        CHECK(sl.tolower('9') == '9');
        }
    }

TEST_CASE("Volatile", "[volatile]")
    {
    te_parser tep;

    volatile te_parser& vTep = tep;

    const_cast<te_parser&>(vTep).set_variables_and_functions(
        { {"STRESS_L", static_cast<te_type>(10.1) },
          {"P_LEVEL", static_cast<te_type>(.5) } });
    const_cast<te_parser&>(vTep).compile(("STRESS_L*P_LEVEL"));
    CHECK_THAT(5.05, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(const_cast<te_parser&>(vTep).evaluate())));
    CHECK_THAT(5.05, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(const_cast<te_parser&>(vTep).evaluate("STRESS_L*P_LEVEL"))));
    const_cast<te_parser&>(vTep).set_constant("P_LEVEL", static_cast<te_type>(.9));
    CHECK_THAT(9.09, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(const_cast<te_parser&>(vTep).evaluate())));
    const_cast<te_parser&>(vTep).compile(("IF(STRESS_L >= P_LEVEL, 1, 0)"));
    CHECK(const_cast<te_parser&>(vTep).evaluate() == 1);
    CHECK(vTep.get_result() == 1);
    CHECK(vTep.success());
    CHECK(const_cast<te_parser&>(vTep).get_variables_and_functions().size() == 2);
#ifndef TE_NO_BOOKKEEPING
    CHECK_FALSE(const_cast<te_parser&>(vTep).is_function_used("sum"));
    CHECK(const_cast<te_parser&>(vTep).is_variable_used("P_LEVEL"));
#endif
    // just make sure we can call these
    vTep.set_list_separator(',');
    vTep.set_decimal_separator('.');
    }

TEST_CASE("Bad separators", "[separators]")
    {
    te_parser tep;

    // these are acceptable
    tep.set_list_separator(',');
    tep.set_list_separator(';');
    tep.set_decimal_separator('.');
    tep.set_decimal_separator(',');

    CHECK_THROWS(tep.set_list_separator(' '));
    CHECK_THROWS(tep.set_decimal_separator('#'));

    // will cause an error when we actually try to use this
    tep.set_list_separator(',');
    tep.set_decimal_separator(',');
    CHECK_THROWS(tep.evaluate("2.2 + 5.9"));
    }

TEST_CASE("Comments", "[comments]")
    {
    te_parser tep;

    SECTION("Multiline")
        {
        tep.compile(("COMBIN(15/*The first argument*/, 3)"));
        CHECK(tep.get_expression() == "COMBIN(15, 3)");
        CHECK(455 == tep.evaluate());
        CHECK(2'730 == tep.evaluate("/*Permutation*//*Another comment*/PERMUT(15, \n/*Seccond argument*/3)/*End of the formula*/"));
        CHECK(tep.get_expression() == "PERMUT(15, \n3)");

        tep.set_constant("SALARY", 15.25);
        CHECK(2'730 == tep.evaluate());
        CHECK(tep.evaluate("SALARY/*Income*/") == 15.25);
        CHECK(tep.get_expression() == "SALARY");
        CHECK(std::isnan(tep.evaluate("SALARY/*Income/")));
        CHECK(tep.get_last_error_position() == 6);
        }

    SECTION("Single line")
        {
        tep.compile((
R"(//Combination
COMBIN(15,
//The first argument
3)
//End of formula)"));
        CHECK(455 == tep.evaluate());
        CHECK(tep.get_expression() ==
R"(
COMBIN(15,

3)
)");

        tep.compile((
            R"(//
//Combination
COMBIN(15,
//
3)
//)"));
        CHECK(455 == tep.evaluate());
        CHECK(tep.get_expression() ==
            R"(

COMBIN(15,

3)
)");

        // stray '/' at the end, bounds check
        tep.compile((
            R"(//Combination
COMBIN(15,
//The first argument
3)
/)"));
        CHECK(std::isnan(tep.evaluate()));
        CHECK(tep.get_expression() ==
            R"(
COMBIN(15,

3)
/)");

        tep.compile((
            R"(21 / 7 // division)"));
        CHECK(3 == tep.evaluate());

        tep.compile((
            R"(21 / /* division */ 7 // division)"));
        CHECK(3 == tep.evaluate());
        }
    }

TEST_CASE("NaN Comparison", "[nan]")
    {
    te_parser tep;

    CHECK(std::isnan(tep.evaluate("NAN()")));
    CHECK(std::isnan(tep.evaluate("NAN() == NAN()")));
    CHECK(std::isnan(tep.evaluate("NAN() != NAN()")));
    CHECK(std::isnan(tep.evaluate("NAN() <> NAN()")));
    CHECK(std::isnan(tep.evaluate("NAN() < NAN()")));
    CHECK(std::isnan(tep.evaluate("NAN() <= NAN()")));
    CHECK(std::isnan(tep.evaluate("NAN() >= NAN()")));
    CHECK(std::isnan(tep.evaluate("8 == NAN()")));
    CHECK(std::isnan(tep.evaluate("8 != NAN()")));
    CHECK(std::isnan(tep.evaluate("8 <> NAN()")));
    CHECK(std::isnan(tep.evaluate("8 < NAN()")));
    CHECK(std::isnan(tep.evaluate("8 <= NAN()")));
    CHECK(std::isnan(tep.evaluate("8 >= NAN()")));
    }

// Financial functions
// --------------------------------------------------

// IPMT
// --------------------------------------------------
TEST_CASE("PPMT", "[finance]")
    {
    te_parser tep;

    // Excel: Loan of $10,000, 5% annual interest, 60 monthly payments
    // Formula: =IPMT(0.05/12, 1, 60, 10000)
    // Result: -41.67
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 1, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-41.6666666667),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Same loan, second payment interest
    // Formula: =IPMT(0.05/12, 2, 60, 10000)
    // Result: -41.05
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 2, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-41.053976375944),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Beginning-of-period payments (type = 1)
    // First payment has no interest
    // Formula: =IPMT(0.05/12, 1, 60, 10000, 0, 1)
    // Result: 0.00
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 1, 60, 10000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(0.0),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Beginning-of-period payments, second payment
    // Formula: =IPMT(0.05/12, 2, 60, 10000, 0, 1)
    // Result: -40.88
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 2, 60, 10000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-40.8836279263),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel: Extreme negative rate uses linear interest regime
    // Formula: =IPMT(-1.1, 1, 60, 10000)
    // Result: 11000
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(-1.1, 1, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(11000.0),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Zero interest rate
    // Formula: =IPMT(0, 10, 60, 10000)
    // Result: 0.00
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0, 10, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(0.0),
            WITHIN_TYPE_CAST(0.00001)));

    // Excel Help: Loan of $2,000, 10% annual interest, 2-year term, monthly payments
    // Principal payment for month 1
    // Formula: =PPMT(10%/12, 1, 2*12, 2000)
    // Result: -75.62
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0.10/12, 1, 2*12, 2000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-75.62),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel Help: Loan of $200,000, 8% annual interest, 10-year term, annual payments
    // Principal payment for year 10 (final year)
    // Formula: =PPMT(0.08, 10, 10, 200000)
    // Result: -27598.05
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0.08, 10, 10, 200000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-27598.05),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Period out of range returns #NUM!
    // Formula: =IPMT(0.05/12, 0, 60, 10000)
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 0, 60, 10000)"))));

    // Excel: Period greater than total periods returns #NUM!
    // Formula: =IPMT(0.05/12, 61, 60, 10000)
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 61, 60, 10000)"))));

    // Excel: Period less than 1 returns #NUM!
    // Formula: =PPMT(0.05/12, 0, 60, 10000)
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0.05/12, 0, 60, 10000)"))));

    // Excel: Period greater than total periods returns #NUM!
    // Formula: =PPMT(0.05/12, 61, 60, 10000)
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0.05/12, 61, 60, 10000)"))));
    
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(-1.1, 1, 60, 10000)"))));

    // Excel: Zero interest rate — entire payment is principal
    // Formula: =PPMT(0, 5, 10, 1000)
    // Result: -100.00
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0, 5, 10, 1000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-100.0),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Beginning-of-period payments
    // Loan: $10,000, 5% annual, 60 months
    // Formula: =PPMT(0.05/12, 1, 60, 10000, 0, 1)
    // Result: -188.93
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0.05/12, 1, 60, 10000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-187.929297699694),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Sign symmetry — flipping PV flips PPMT
    // Formula: =PPMT(0.05/12, 10, 60, -10000)
    // Result: 155.65
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0.05/12, 10, 60, -10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(152.652685047979),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: Final period principal payment
    // Formula: =PPMT(0.05/12, 60, 60, 10000)
    // Result: -187.93
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PPMT(0.05/12, 60, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-187.929297699694),
            WITHIN_TYPE_CAST(0.0001)));
    }

    // CUMPRINC
// --------------------------------------------------
TEST_CASE("CUMPRINC", "[finance]")
    {
    te_parser tep;

    // Excel Help example:
    // 9% annual interest rate, 30-year loan, $125,000 present value
    // Principal paid in year 2 (months 13–24), payments at END of period
    // Formula: =CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 0)
    // Result: -934.11
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 0)")
        ),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-934.107123420898),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel Help example:
    // Same loan, payments at BEGINNING of period
    // Formula: =CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 1)
    // Result: -$927.15
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-927.153472378064),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: single-period principal equals PPMT
    // Formula: =CUMPRINC(0.05/12, 60, 10000, 1, 1, 0)
    // Result: -147.05
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 1, 1, 0)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-147.045669773443),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel: CUMPRINC does NOT support zero interest
    // Formula: =CUMPRINC(0, 10, 1000, 1, 10, 0)
    // Result: ERR / #NUM!
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0, 10, 1000, 1, 10, 0)"))));

    // LibreOffice / Excel: CUMPRINC does NOT support linear-interest regime
    // Formula: =CUMPRINC(-1.1, 60, 10000, 1, 1, 0)
    // Result: ERR / #NUM!
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(-1.1, 60, 10000, 1, 1, 0)"))));

    // Excel: start period < 1 → #NUM!
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 0, 10, 0)"))));

    // Excel: end period > total periods → #NUM!
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 1, 61, 0)"))));

    // Excel: start period > end period → #NUM!
    CHECK(std::isnan(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 10, 5, 0)"))));

    // Excel:
    // 9% annual interest, 30-year loan, $125,000
    // Principal paid in year 2 (months 13–24), payments at END of period
    // Formula: =CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 0)
    // Result: -$934.11
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 0)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-934.107123420898),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel:
    // Same loan, payments at BEGINNING of period
    // Formula: =CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 1)
    // Result: -$927.15
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.09/12, 30*12, 125000, 13, 24, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-927.153472378064),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel:
    // Single period cumulative principal equals PPMT
    // Formula: =CUMPRINC(0.05/12, 60, 10000, 1, 1, 0)
    // Result: -147.05
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 1, 1, 0)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-147.045669773443),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel:
    // Early loan principal (month 1)
    // Formula: =CUMPRINC(0.05/12, 60, 10000, 1, 1, 0)
    // Result: -147.05
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 1, 1, 0)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-147.045669773443),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel:
    // Late loan principal (month 60)
    // Formula: =CUMPRINC(0.05/12, 60, 10000, 60, 60, 0)
    // Result: -$187.93
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 60, 60, 0)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-187.929297699694),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel:
    // Principal paid in first year (months 1–12)
    // Formula: =CUMPRINC(0.05/12, 60, 10000, 1, 12, 0)
    // Result: -$1,805.55
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 1, 12, 0)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-1805.55252981598),
            WITHIN_TYPE_CAST(0.0001)));

    // LibreOffice / Excel:
    // Beginning-of-period payments: first payment is mostly principal
    // Formula: =CUMPRINC(0.05/12, 60, 10000, 1, 1, 1)
    // Result: -187.93
    CHECK_THAT(
        WITHIN_TYPE_CAST(
            tep.evaluate("CUMPRINC(0.05/12, 60, 10000, 1, 1, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-187.929297699694),
            WITHIN_TYPE_CAST(0.0001)));
    }

// CUMIPMT
// --------------------------------------------------
TEST_CASE("CUMIPMT", "[finance]")
    {
    te_parser tep;

    // Excel / docs example:
    // 9% annual interest rate, 30-year loan, $125,000 PV
    // Total interest paid in the 2nd year (periods 13 through 24), payments at END (type=0)
    // =CUMIPMT(0.09/12, 30*12, 125000, 13, 24, 0) -> -11135.23
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("CUMIPMT(0.09/12, 30*12, 125000, 13, 24, 0)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(-11135.23), WITHIN_TYPE_CAST(0.00001)));

    // Microsoft example (beginning-of-period payments):
    // =CUMIPMT(0.09/12, 30*12, 125000, 13, 24, 1) -> -11052.34
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("CUMIPMT(0.09/12, 30*12, 125000, 13, 24, 1)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(-11052.34), WITHIN_TYPE_CAST(0.00001)));

    // Single-period sanity check:
    // =CUMIPMT(0.09/12, 30*12, 125000, 1, 1, 0) -> -937.50
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("CUMIPMT(0.09/12, 30*12, 125000, 1, 1, 0)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(-937.50), WITHIN_TYPE_CAST(0.00001)));
    }

// IPMT
// --------------------------------------------------
TEST_CASE("IPMT", "[finance]")
    {
    te_parser tep;

    // --------------------------------------------------
    // Excel Online Help example
    //
    // Data:
    // Annual interest rate: 10%
    // Number of years: 3
    // Present value: 8000
    //
    // Excel formula:
    // =IPMT(0.10/12, 1, 3*12, 8000)
    //
    // Excel result: -66.67
    // --------------------------------------------------
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.10/12, 1, 3*12, 8000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-66.67),
            WITHIN_TYPE_CAST(0.0001)));

    // --------------------------------------------------
    // Excel: =IPMT(0.10/12, 2, 3*12, 8000)
    // Interest portion for second period
    // Excel result: -65.0710764092997
    // --------------------------------------------------
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.10/12, 2, 3*12, 8000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-65.0710764092997),
            WITHIN_TYPE_CAST(0.0001)));

    // --------------------------------------------------
    // Excel: =IPMT(0.05/12, 1, 60, 10000)
    // First month's interest on a 5-year loan
    // Excel result: -41.67
    // --------------------------------------------------
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 1, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-41.67),
            WITHIN_TYPE_CAST(0.0001)));

    // --------------------------------------------------
    // Excel: =IPMT(0.05/12, 12, 60, 10000)
    // Interest portion after one year
    // Excel result: -34.12
    // --------------------------------------------------
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 12, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-34.7848954631707),
            WITHIN_TYPE_CAST(0.0001)));

    // --------------------------------------------------
    // Payments at beginning of period
    //
    // Excel: =IPMT(0.05/12, 1, 60, 10000, 0, 1)
    // First period interest is zero
    // --------------------------------------------------
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 1, 60, 10000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(0.0)));

    // --------------------------------------------------
    // Excel: =IPMT(0.05/12, 2, 60, 10000, 0, 1)
    // Interest starts accruing in second period
    // Excel result: -40.88
    // --------------------------------------------------
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 2, 60, 10000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-40.8836279262513),
            WITHIN_TYPE_CAST(0.00001)));

    // --------------------------------------------------
    // Zero interest rate
    //
    // Excel: =IPMT(0, 10, 60, 10000)
    // Excel result: 0
    // --------------------------------------------------
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("IPMT(0, 10, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(0.0)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("=IPMT(0.05/12, 1.5, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-41.3606399677465),
            WITHIN_TYPE_CAST(0.0000001)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("=IPMT(-1, 1, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(10000),
            WITHIN_TYPE_CAST(0.0000001)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("=IPMT(-1.1, 1, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(11000),
            WITHIN_TYPE_CAST(0.0000001)));

    // --------------------------------------------------
    // Invalid inputs
    // --------------------------------------------------

    // period < 1
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 0, 60, 10000)"))));

    // period > periods
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 61, 60, 10000)"))));

    // non-finite args
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("IPMT(NaN, 1, 60, 10000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, NaN, 60, 10000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 1, NaN, 10000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("IPMT(0.05/12, 1, 60, NaN)"))));
    }

// --------------------------------------------------
// PV
// --------------------------------------------------
TEST_CASE("PV", "[finance]")
    {
    te_parser tep;

    // Excel: =PV(0.05/12, 60, -200)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05/12, 60, -200)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(10598.14), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0.05/12, 60, -200, 0, 1)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05/12, 60, -200, 0, 1)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(10642.30), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0.1, 1, -100)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.1, 1, -100)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(90.91), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0, 60, -200)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0, 60, -200)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(12000)));

    // Excel: =PV(0, 10, 0, 1000)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0, 10, 0, 1000)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(-1000)));

    // Excel: =PV(0.05, 10, -100)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, 10, -100)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(772.17), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0.05, 10, -100, 0)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, 10, -100, 0)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(772.17), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0.05, 10, -100, 0, 0)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, 10, -100, 0, 0)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(772.17), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0.05, 10, -100, 0, 2)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, 10, -100, 0, 2)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(810.78), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0.05, 10, -100, 0, -1)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, 10, -100, 0, -1)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(810.78), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(-0.5, 5, -100)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(-0.5, 5, -100)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(6200), WITHIN_TYPE_CAST(0.0001)));

    CHECK_THAT(
        WITHIN_TYPE_CAST((tep.evaluate("PV(0.05, 0, -100)"))),
        Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(0), WITHIN_TYPE_CAST(0.0001)));

    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, -10, -100)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(-1257.78925355488), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(-1, 10, -100) -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PV(-1, 10, -100)"))));

    // Excel: =PV(NaN, 10, -100) -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PV(NaN, 10, -100)"))));

    // Excel: =PV(0.05, NaN, -100) -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, NaN, -100)"))));

    // Excel: =PV(0.05, 10, NaN) -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PV(0.05, 10, NaN)"))));

    // Excel: =PV(0.08/12, 360, -1000)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.08/12, 360, -1000)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(136283.35), WITHIN_TYPE_CAST(0.0001)));

    // Excel: =PV(0.03, 1, 0, 1000)
    CHECK_THAT(WITHIN_TYPE_CAST(tep.evaluate("PV(0.03, 1, 0, 1000)")),
               Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(-970.87), WITHIN_TYPE_CAST(0.0001)));

    // Excel example:
    // Money paid out of an insurance annuity at the end of every month: $500
    // Interest rate: 8% annually
    // Term: 20 years
    //
    // Excel formula:
    // =PV(A3/12, 12*A4, A2, , 0)
    // =PV(0.08/12, 240, 500, 0, 0)
    //
    // Excel result = -59,775.15
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PV(0.08/12, 12*20, 500, 0, 0)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-59775.15),
            WITHIN_TYPE_CAST(0.0001)));
    }

TEST_CASE("PMT", "[finance]")
    {
    te_parser tep;

    // Excel: =PMT(0.05/12, 60, 10000)
    // Monthly payment on a $10,000 loan at 5% for 5 years
    // Excel result ~ -188.71
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.05/12, 60, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-188.71),
            WITHIN_TYPE_CAST(0.00002)));

    // Excel: =PMT(0.05/12, 60, 10000, 0, 1)
    // Payments at beginning of period -> slightly smaller payment
    // Excel result ~ -187.93
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.05/12, 60, 10000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-187.93),
            WITHIN_TYPE_CAST(0.001)));

    // Excel: =PMT(0, 60, 12000)
    // Zero interest: straight-line repayment
    // Excel result = -200
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0, 60, 12000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-200)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(-1, 60, 12000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(0)));

    // Excel: =PMT(0.1, 1, 100)
    // One-period loan at 10%
    // Excel result = -110
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.1, 1, 100)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-110),
            WITHIN_TYPE_CAST(0.00001)));

    // Excel: =PMT(0.05/12, 60, 10000, 1000)
    // Loan with balloon payment
    // Excel result ~ -203.42
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.05/12, 60, 10000, 1000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-203.42),
            WITHIN_TYPE_CAST(0.001)));

    // Excel data:
    // Annual interest rate: 8%
    // Number of months: 10
    // Loan amount: $10,000

    // Excel: =PMT(A2/12, A3, A4)
    // Monthly payment
    // Excel result: ($1,037.03)
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.08/12, 10, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-1037.03),
            WITHIN_TYPE_CAST(0.00002)));

    // Excel: =PMT(A2/12, A3, A4, , 1)
    // Payments at beginning of period
    // Excel result: ($1,030.16)
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.08/12, 10, 10000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-1030.16),
            WITHIN_TYPE_CAST(0.00002)));

    // Excel data:
    // Annual interest rate: 6%
    // Term: 18 years
    // Target future value: $50,000

    // Excel: =PMT(A9/12, A10*12, 0, A11)
    // Monthly savings required
    // Excel result ~ ($129.08)
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.06/12, 18*12, 0, 50000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-129.08),
            WITHIN_TYPE_CAST(0.00005)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("PMT(0.05, -10, 1000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(79.5045749654567),
            WITHIN_TYPE_CAST(0.00001)));

    // Excel: rate <= -1 -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PMT(-1.5, 10, 1000)"))));

    // Excel: nper <= 0 -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PMT(0.05, 0, 1000)"))));

    // Non-finite args -> NaN
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PMT(NaN, 10, 1000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PMT(0.05, NaN, 1000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("PMT(0.05, 10, NaN)"))));
    }

// --------------------------------------------------
// NPER
// --------------------------------------------------
TEST_CASE("NPER", "[finance]")
    {
    te_parser tep;

    // Excel: =NPER(0.05/12, -188.71, 10000)
    // Loan paid off in 60 months
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("NPER(0.05/12, -188.71, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(60),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: =NPER(0.05/12, -200, 10000)
    // Higher payment -> fewer periods
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("NPER(0.05/12, -200, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(56.18429076),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: =NPER(0, -200, 12000)
    // Zero interest
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("NPER(0, -200, 12000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(60)));

    // --------------------------------------------------
    // Excel example (provided)
    // --------------------------------------------------

    // Excel data:
    // Annual interest rate: 12%
    // Payment each period: -100
    // Present value: -1000
    // Future value: 10000
    // Payments at beginning of period

    // Excel: =NPER(A2/12, A3, A4, A5, 1)
    // Excel result: 59.67386567

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("NPER(0.12/12, -100, -1000, 10000, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(59.67386567),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: =NPER(A2/12, A3, A4, A5)
    // Payments at end of period
    // Excel result: 60.08212285
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("NPER(0.12/12, -100, -1000, 10000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(60.08212285),
            WITHIN_TYPE_CAST(0.0001)));

    // Excel: =NPER(A2/12, A3, A4)
    // Future value defaults to 0
    // Excel result: -9.7859404
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("NPER(0.12/12, -100, -1000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-9.57859404),
            WITHIN_TYPE_CAST(0.0001)));

    // --------------------------------------------------
    // Invalid inputs
    // --------------------------------------------------

    // Excel: rate <= -1 -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NPER(-1, -100, 1000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NPER(-1.2, -100, 1000)"))));

    // Excel: pmt == 0 with rate == 0 -> #NUM!
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NPER(0, 0, 1000)"))));

    // Non-finite args -> NaN
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NPER(NaN, -100, 1000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NPER(0.05, NaN, 1000)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NPER(0.05, -100, NaN)"))));
    }

TEST_CASE("FV", "[finance]")
    {
    te_parser tep;

    // Excel: =FV(0.05/12, 60, -200)
    // Savings $200/month at 5% for 5 years
    // Excel result ~ $13,601.22 
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.05/12, 60, -200)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(13601.22),
            WITHIN_TYPE_CAST(0.00005)));

    // Excel: =FV(0.05/12, 60, -200, 0, 1)
    // Payments at beginning of period
    // Excel result ~ $13,657.89
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.05/12, 60, -200, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(13657.89),
            WITHIN_TYPE_CAST(0.00005)));

    // Excel: =FV(0, 60, -200)
    // Zero interest
    // Excel result = 12,000
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0, 60, -200)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(12000)));

    // Excel: =FV(0.08/12, 360, -1000)
    // Long-horizon compounding
    // Excel result ~ $1,490,359.45
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.08/12, 360, -1000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(1490359.45),
            WITHIN_TYPE_CAST(0.0001)));

    // --------------------------------------------------
    // FV – Excel examples
    // --------------------------------------------------

    // Example 1
    // Excel data:
    // Annual interest rate: 6%
    // Number of payments: 10
    // Payment: -200
    // Present value: -500
    // Payments at beginning of period
    //
    // Excel: =FV(A2/12, A3, A4, A5, A6)
    // Excel result: $2,581.40
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.06/12, 10, -200, -500, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(2581.40),
            WITHIN_TYPE_CAST(0.00005)));

    // Example 2
    // Excel data:
    // Annual interest rate: 12%
    // Number of payments: 12
    // Payment: -1000
    //
    // Excel: =FV(A2/12, A3, A4)
    // Excel result: $12,682.50
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.12/12, 12, -1000)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(12682.50),
            WITHIN_TYPE_CAST(0.00005)));

    // Example 3
    // Excel data:
    // Annual interest rate: 11%
    // Number of payments: 35
    // Payment: -2000
    // Payments at beginning of period
    //
    // Excel: =FV(A2/12, A3, A4, , A5)
    // Excel result: $82,846.25
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.11/12, 35, -2000, 0, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(82846.25),
            WITHIN_TYPE_CAST(0.00005)));

    // Example 4
    // Excel data:
    // Annual interest rate: 6%
    // Number of payments: 12
    // Payment: -100
    // Present value: -1000
    // Payments at beginning of period
    //
    // Excel: =FV(A2/12, A3, A4, A5, A6)
    // Excel result: $2,301.40
    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.06/12, 12, -100, -1000, 1)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(2301.40),
            WITHIN_TYPE_CAST(0.00005)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(-1, 10, -100)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(100),
            WITHIN_TYPE_CAST(0.00005)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(-1.5, 10, -100)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(66.6015625),
            WITHIN_TYPE_CAST(0.00005)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.05, 0, -100)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(0),
            WITHIN_TYPE_CAST(0.00005)));

    CHECK_THAT(
        WITHIN_TYPE_CAST(tep.evaluate("FV(0.05, -10, -100)")),
        Catch::Matchers::WithinRel(
            WITHIN_TYPE_CAST(-772.173492918482),
            WITHIN_TYPE_CAST(0.00005)));

    // Non-finite args -> NaN
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("FV(NaN, 10, -100)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("FV(0.05, NaN, -100)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("FV(0.05, 10, NaN)"))));
    }

TEST_CASE("Nominal", "[finance]")
    {
    te_parser tep;

    CHECK_THAT(4, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("NOMINAL(8, 2)"))));
    CHECK_THAT(0.05250032, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("NOMINAL(0.053543, 4)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(0.00995132100969354, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("=NOMINAL(0.01,50)")), WITHIN_TYPE_CAST(0.001)));
    CHECK_THAT(0.20744331009791, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("=NOMINAL(0.23,50)")), WITHIN_TYPE_CAST(0.00001)));

    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NOMINAL(8, 0)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NOMINAL(0, 4)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("NOMINAL(-.1, 4)"))));
    }

TEST_CASE("Effect", "[finance]")
    {
    te_parser tep;

    CHECK_THAT(0.0535427, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("EFFECT(0.0525, 4)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(0.127340987166906, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("EFFECT(0.12, 52)")), WITHIN_TYPE_CAST(0.0001)));

    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("EFFECT(8, 0)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("EFFECT(0, 4)"))));
    CHECK(std::isnan(WITHIN_TYPE_CAST(tep.evaluate("EFFECT(-.1, 4)"))));
    }

TEST_CASE("DB", "[finance]")
    {
    te_parser tep;

    CHECK_THAT(186083.33, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,1,7)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(259639.42, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,2,7)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(176814.44, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,3,7)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(120410.64, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,4,7)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(81999.64, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,5,7)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(55841.76, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,6,7)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(15845.10, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,7,7)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(23632.18, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,7,5)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(23632.18, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,7,5.9)")), WITHIN_TYPE_CAST(0.00001)));

    CHECK_THAT(319000.00, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,1)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(217239.00, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,2)")), WITHIN_TYPE_CAST(0.00001)));
    CHECK_THAT(100746.98, Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(tep.evaluate("DB(1000000,100000,6,4)")), WITHIN_TYPE_CAST(0.00001)));

    CHECK(std::isnan(tep.evaluate("DB(1000000,100000,6,1,0)")));
    CHECK(std::isnan(tep.evaluate("DB(1000000,100000,6,1,13)")));
    CHECK(std::isnan(tep.evaluate("DB(0,100000,6,1,7)")));
    CHECK(std::isnan(tep.evaluate("DB(1000000,0,6,1,13)")));
    CHECK(std::isnan(tep.evaluate("DB(1000000,100000,0,1,13)")));
    CHECK(std::isnan(tep.evaluate("DB(1000000,100000,6,7.5,5)")));
    CHECK(std::isnan(tep.evaluate("DB(1000000,100000,6.5,7,5)")));
    CHECK(std::isnan(tep.evaluate("DB(1000000,100000,6,8)")));
    }

// These cover node ownership: te_parser owns its compiled tree and frees it via
// te_free(), while contexts and variables are borrowed from the caller.
TEST_CASE("Large expression trees", "[memory]")
    {
    te_type xVal{ 2 };
    te_parser tep;
    tep.set_variables_and_functions({ { "x", &xVal } });

    constexpr int termCount{ 250 };
    std::string bigExpr{ "x" };
    for (int i = 1; i < termCount; ++i)
        {
        bigExpr += "+x";
        }

    CHECK(tep.evaluate(bigExpr) == termCount * xVal);
    CHECK(tep.success());
    CHECK(tep.evaluate() == termCount * xVal);

    SECTION("Small expression after a large one")
        {
        // the previous tree must be freed, not leaked or double-freed
        CHECK(tep.evaluate("x+1") == 3);
        CHECK(tep.success());
        CHECK(tep.evaluate() == 3);
        }

    SECTION("Repeatedly recompiling a large expression")
        {
        for (int i = 0; i < 10; ++i)
            {
            CHECK(tep.evaluate(bigExpr) == termCount * xVal);
            }
        }

    SECTION("Variable rebinding in a large tree")
        {
        xVal = 3;
        CHECK(tep.evaluate() == termCount * xVal);
        }
    }

TEST_CASE("Parser reuse after failed compile", "[memory]")
    {
    te_type xVal{ 3 };
    te_parser tep;
    tep.set_variables_and_functions({ { "x", &xVal } });

    // every node is allocated before the trailing syntax error is reached,
    // so this exercises discarding a large, partially built tree
    std::string badExpr;
    for (int i = 0; i < 250; ++i)
        {
        badExpr += "x+";
        }
    badExpr += "(";

    CHECK(std::isnan(tep.evaluate(badExpr)));
    CHECK_FALSE(tep.success());

    CHECK(tep.evaluate("x*2") == 6);
    CHECK(tep.success());
    CHECK(tep.evaluate() == 6);

    SECTION("Failure directly after a successful compile")
        {
        CHECK(tep.evaluate("x+x+x") == 9);
        CHECK(std::isnan(tep.evaluate("x+*")));
        CHECK_FALSE(tep.success());
        CHECK(tep.evaluate("x-1") == 2);
        }

    SECTION("Math error while folding constants")
        {
        // throws from inside optimize(), which is a separate cleanup path
        // from failing during the parse
        CHECK(std::isnan(tep.evaluate("1+2+3+sqrt(-1)")));
        CHECK_FALSE(tep.success());
        CHECK(tep.evaluate("x+4") == 7);
        CHECK(tep.success());
        }
    }

TEST_CASE("Compiled expression outlives its source parser", "[memory]")
    {
    te_type xVal{ 4 };
    te_type yVal{ 5 };

    SECTION("Copy CTOR")
        {
        std::unique_ptr<te_parser> copied;
            {
            te_parser tep;
            tep.set_variables_and_functions({ { "x", &xVal }, { "y", &yVal } });
            CHECK(tep.evaluate("(x+y)*2") == 18);
            copied = std::make_unique<te_parser>(tep);
            }
        // source parser (and its tree) is gone
        CHECK(copied->evaluate() == 18);
        CHECK(copied->success());
        xVal = 5;
        CHECK(copied->evaluate() == 20);
        }

    SECTION("Assignment")
        {
        te_parser copyTarget;
            {
            te_parser tep;
            tep.set_variables_and_functions({ { "x", &xVal }, { "y", &yVal } });
            CHECK(tep.evaluate("(x+y)*2") == 18);
            copyTarget = tep;
            }
        CHECK(copyTarget.evaluate() == 18);
        CHECK(copyTarget.success());
        }

    SECTION("Assigning over a parser that already has a compiled expression")
        {
        te_parser first;
        first.set_variables_and_functions({ { "x", &xVal } });
        CHECK(first.evaluate("x*100") == 400);

        te_parser second;
        second.set_variables_and_functions({ { "y", &yVal } });
        CHECK(second.evaluate("y+1") == 6);

        first = second;
        CHECK(first.evaluate() == 6);
        CHECK(second.evaluate() == 6);
        }
    }

TEST_CASE("Parsers relocated in a container", "[memory]")
    {
    te_type xVal{ 7 };

    // growing the vector copies every parser, so each copy must own its own
    // tree rather than share the original's nodes
    std::vector<te_parser> parsers;
    for (int i = 0; i < 32; ++i)
        {
        te_parser tep;
        tep.set_variables_and_functions({ { "x", &xVal } });
        CHECK(tep.compile("x*" + std::to_string(i + 1)));
        parsers.push_back(tep);
        }

    for (size_t i = 0; i < parsers.size(); ++i)
        {
        CHECK(parsers[i].evaluate() == xVal * static_cast<te_type>(i + 1));
        }

    parsers.erase(parsers.begin());
    CHECK(parsers.front().evaluate() == xVal * 2);
    }

TEST_CASE("Closure context outlives the parser", "[memory]")
    {
    // the context object is owned by the caller; te_free_parameters() must skip
    // the trailing context pointer that closure nodes carry
    te_expr_array teArray{ TE_DEFAULT };

        {
        te_parser tep;
        tep.set_variables_and_functions({ { "cell", cell, TE_DEFAULT, &teArray },
                                          { "cellmax", cell_max, TE_DEFAULT, &teArray } });
        CHECK(tep.evaluate("cell 0 + cellmax()") == 14);
        }

    // still intact after the parser is gone
    CHECK(teArray.m_data[0] == 5);
    CHECK(teArray.m_data[4] == 9);

    // and still usable by another parser
    te_parser tep2;
    tep2.set_variables_and_functions({ { "cell", cell, TE_DEFAULT, &teArray } });
    CHECK(tep2.evaluate("cell 4") == 9);

    // a pure closure is constant folded at compile time, which frees the node's
    // arguments but must leave the borrowed context alone
    te_parser tep3;
    tep3.set_variables_and_functions({ { "pcell", cell, TE_PURE, &teArray } });
    CHECK(tep3.evaluate("pcell 2") == 7);
    CHECK(tep3.evaluate() == 7);
    CHECK(teArray.m_data[2] == 7);
    }

TEST_CASE("Custom functions and data in large expressions", "[memory]")
    {
    te_type extra{ 10 };
    te_expr teContext{ TE_DEFAULT, &extra };
    te_type xVal{ 1 };

    te_parser tep;
    tep.set_variables_and_functions(
        { { "x", &xVal }, { "s7", sum7 }, { "c7", clo7, TE_DEFAULT, &teContext } });

    SECTION("High-arity custom function")
        {
        std::string expr{ "0" };
        for (int i = 0; i < 40; ++i)
            {
            expr += "+s7(x,x,x,x,x,x,x)";
            }
        CHECK(tep.evaluate(expr) == 40 * 7);
        CHECK(tep.success());
        CHECK(tep.evaluate() == 40 * 7);

        xVal = 2;
        CHECK(tep.evaluate() == 40 * 14);
        }

    SECTION("High-arity closure")
        {
        // each closure node carries the borrowed context pointer in its
        // parameter list alongside its arguments
        std::string expr{ "0" };
        for (int i = 0; i < 40; ++i)
            {
            expr += "+c7(x,x,x,x,x,x,x)";
            }
        // clo7 adds the context value (10) to its 7 arguments
        CHECK(tep.evaluate(expr) == 40 * 17);
        CHECK(tep.success());

        // the context is only borrowed, so updating it is still seen
        extra = 20;
        CHECK(tep.evaluate() == 40 * 27);
        }

    SECTION("Context object outlives the parser")
        {
        std::string expr{ "0" };
        for (int i = 0; i < 40; ++i)
            {
            expr += "+c7(x,x,x,x,x,x,x)";
            }
            {
            te_parser scopedParser;
            scopedParser.set_variables_and_functions(
                { { "x", &xVal }, { "c7", clo7, TE_DEFAULT, &teContext } });
            CHECK(scopedParser.evaluate(expr) == 40 * 17);
            }
        // the tree is freed, the caller's context is not
        CHECK(std::get<const te_type*>(teContext.m_value) == &extra);
        CHECK(extra == 10);
        CHECK(tep.evaluate(expr) == 40 * 17);
        }

    SECTION("Lambdas")
        {
        te_parser lambdaParser;
        lambdaParser.set_variables_and_functions(
            { { "x", &xVal },
              { "twice", [](te_type a) noexcept { return a * 2; } },
              { "addall", [](te_type a, te_type b, te_type c) noexcept { return a + b + c; } } });

        std::string expr{ "0" };
        for (int i = 0; i < 60; ++i)
            {
            expr += "+twice(addall(x,x,x))";
            }
        CHECK(lambdaParser.evaluate(expr) == 60 * 6);
        CHECK(lambdaParser.success());
        CHECK(lambdaParser.evaluate() == 60 * 6);
        }

    SECTION("Unknown symbol resolver")
        {
        te_parser usrParser;
        usrParser.set_unknown_symbol_resolver(
            [](std::string_view str) -> te_type
            { return str.starts_with("VAR") ? static_cast<te_type>(2) : te_parser::te_nan; });

        std::string expr{ "VAR1" };
        for (int i = 2; i <= 120; ++i)
            {
            expr += "+VAR" + std::to_string(i);
            }

        CHECK(usrParser.evaluate(expr) == 120 * 2);
        CHECK(usrParser.success());
        // the resolved symbols are purged afterwards, but their values were
        // already folded into the tree
        CHECK(usrParser.evaluate() == 120 * 2);
        }

    SECTION("Function removed after compiling")
        {
        CHECK(tep.evaluate("s7(x,x,x,x,x,x,x)") == 7);
        // the compiled tree holds the function itself, not a lookup into
        // the parser's symbol table
        tep.remove_variable_or_function("s7");
        CHECK(tep.evaluate() == 7);
        // ...but recompiling it now fails, and leaves the parser usable
        CHECK(std::isnan(tep.evaluate("s7(x,x,x,x,x,x,x)")));
        CHECK_FALSE(tep.success());
        CHECK(tep.evaluate("x+1") == 2);
        }
    }

TEST_CASE("Discarded negate wrapper", "[memory]")
    {
    // factor() deletes a redundant negate node mid-parse and keeps its child,
    // so the child must not be freed along with the wrapper
    te_type xVal{ 3 };
    te_parser tep;
    tep.set_variables_and_functions({ { "x", &xVal } });

    CHECK(tep.evaluate("-x") == -3);
    CHECK(tep.evaluate("--x") == 3);
    CHECK(tep.evaluate("---x") == -3);
    CHECK(tep.evaluate("----x") == 3);
    CHECK(tep.evaluate("-(-(-(-x)))") == 3);
    CHECK(tep.evaluate("1 - -x") == 4);
    CHECK(tep.evaluate("-x*-x") == 9);
    CHECK(tep.evaluate("--x+--x") == 6);
    // re-evaluating the last tree still works
    CHECK(tep.evaluate() == 6);
    }

TEST_CASE("Constant folding with a large foldable subtree", "[memory]")
    {
    te_type xVal{ 1 };
    te_parser tep;
    tep.set_variables_and_functions({ { "x", &xVal } });

    // the parenthesized part folds to a single constant, which frees the 100+
    // child nodes that were built for it
    std::string expr{ "x + (0" };
    for (int i = 1; i <= 100; ++i)
        {
        expr += "+" + std::to_string(i);
        }
    expr += ")";

    CHECK(tep.evaluate(expr) == 5051); // 1 + 5050
    CHECK(tep.success());
    CHECK(tep.evaluate() == 5051);

    xVal = 2;
    CHECK(tep.evaluate() == 5052);

    // and the parser still works normally afterwards
    CHECK(tep.evaluate("x*3") == 6);
    }

TEST_CASE("String arguments", "[strings]")
    {
    te_parser tep;
    tep.set_variables_and_functions({
        { "strlenplus", static_cast<te_arg_fun>(str_len_plus), TE_PURE },
        { "strpair", static_cast<te_arg_fun>(str_pair), TE_PURE },
        { "strtotal", static_cast<te_arg_fun>(str_total), TE_PURE },
        // same function, not pure, so the call survives optimize()
        { "strlive", static_cast<te_arg_fun>(str_len_plus), TE_DEFAULT } });

    SECTION("Basic")
        {
        CHECK(tep.evaluate("STRLENPLUS(\"abc\")") == 3);
        CHECK(tep.success());
        CHECK(tep.evaluate("STRLENPLUS(\"abc\", 3)") == 6);
        CHECK(tep.evaluate("STRLENPLUS(\"\")") == 0);
        CHECK(tep.evaluate("STRLENPLUS(\"a b c\")") == 5);
        }

    SECTION("Argument order")
        {
        // any position can be a string or a number
        CHECK(tep.evaluate("STRTOTAL(\"abc\")") == 3);
        CHECK(tep.evaluate("STRTOTAL(1, \"abc\")") == 4);
        CHECK(tep.evaluate("STRTOTAL(\"ab\", 1, \"c\")") == 4);
        CHECK(tep.evaluate("STRTOTAL(1, 2, 3)") == 6);
        CHECK(tep.evaluate("STRTOTAL(\"a\", \"bb\", \"ccc\")") == 6);
        }

    SECTION("Arity is unbounded")
        {
        CHECK(tep.evaluate("STRTOTAL()") == 0);
        CHECK(tep.success());
        CHECK(tep.evaluate("STRTOTAL(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)") == 24);
        // beyond the 24-argument ceiling of the te_fun family
        CHECK(tep.evaluate("STRTOTAL(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)")
              == 30);
        CHECK(tep.success());
        }

    SECTION("Wrong arity is the function's problem, not the parser's")
        {
        // strpair wants exactly two arguments; the parse still succeeds
        CHECK(tep.compile("STRPAIR(\"abc\")"));
        CHECK(tep.success());
        CHECK(std::isnan(tep.evaluate()));
        CHECK(tep.compile("STRPAIR(\"abc\", 2, 3)"));
        CHECK(std::isnan(tep.evaluate()));
        CHECK(tep.evaluate("STRPAIR(\"abc\", 2)") == 6);
        }

    SECTION("Wrong argument type")
        {
        // strlenplus needs a string first
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(1)")));
        CHECK(tep.success());
        // and numbers after
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"a\", \"b\")")));
        }

    SECTION("Numeric expressions as arguments")
        {
        tep.add_variable_or_function({ "x", static_cast<te_type>(5) });
        CHECK(tep.evaluate("STRLENPLUS(\"abc\", 2*x+1)") == 14);
        CHECK(tep.evaluate("STRLENPLUS(\"abc\", MAX(1, 2, 3))") == 6);
        CHECK(tep.evaluate("STRLENPLUS(\"abc\", STRLENPLUS(\"de\"))") == 5);
        // and the result feeds back into numeric code
        CHECK(tep.evaluate("STRLENPLUS(\"abc\") * 2") == 6);
        CHECK(tep.evaluate("IF(STRLENPLUS(\"abcd\") > 3, 100, 200)") == 100);
        CHECK(tep.evaluate("SUM(STRLENPLUS(\"ab\"), STRLENPLUS(\"cde\"))") == 5);
        }

    SECTION("Literal contents are passed through untouched")
        {
        CHECK(tep.evaluate("STRLENPLUS(\"a,b\")") == 3);
        CHECK(tep.evaluate("STRLENPLUS(\"(((\")") == 3);
        CHECK(tep.evaluate("STRLENPLUS(\"1+1\")") == 3);
        CHECK(tep.evaluate("STRLENPLUS(\"  \")") == 2);
        CHECK(tep.evaluate("STRLENPLUS(\"=\")") == 1);
        // a leading '=' is only stripped from the expression, not from a literal
        CHECK(tep.evaluate("=STRLENPLUS(\"=abc\")") == 4);
        }

    SECTION("Whitespace around literals")
        {
        CHECK(tep.evaluate("STRLENPLUS( \"abc\" )") == 3);
        CHECK(tep.evaluate("STRLENPLUS(\t\"abc\"\t,\t3\t)") == 6);
        CHECK(tep.evaluate("STRLENPLUS\n(\n\"abc\"\n)") == 3);
        }

    SECTION("Literals are only legal as arguments")
        {
        CHECK(std::isnan(tep.evaluate("\"abc\"")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("1 + \"abc\"")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("\"abc\" + 1")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("sin(\"abc\")")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("MAX(1, \"abc\")")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("-\"abc\"")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("(\"abc\")")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("\"a\" \"b\"")));
        CHECK_FALSE(tep.success());
        // a string result can't be produced, so this is still an error
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"a\") + \"b\"")));
        CHECK_FALSE(tep.success());
        }

    SECTION("Malformed literals")
        {
        // unterminated
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"abc")));
        CHECK_FALSE(tep.success());
        CHECK(tep.get_last_error_position() != te_parser::npos);
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"")));
        CHECK_FALSE(tep.success());
        // stray closing quote
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(abc\")")));
        CHECK_FALSE(tep.success());
        // a quote swallows the rest of the call
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"abc\", \"3)")));
        CHECK_FALSE(tep.success());
        // missing close paren after a good literal
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"abc\"")));
        CHECK_FALSE(tep.success());
        // separator with nothing after it
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"abc\",)")));
        CHECK_FALSE(tep.success());
        // no parentheses at all
        CHECK(std::isnan(tep.evaluate("strlenplus")));
        CHECK_FALSE(tep.success());
        CHECK(std::isnan(tep.evaluate("strlenplus \"abc\"")));
        CHECK_FALSE(tep.success());
        }

    SECTION("Error positions")
        {
        // the reported position should land at or after the offending quote
        tep.compile("1 + \"abc\"");
        CHECK_FALSE(tep.success());
        CHECK(tep.get_last_error_position() >= 4);
        tep.compile("STRLENPLUS(\"ok\") + \"abc\"");
        CHECK_FALSE(tep.success());
        CHECK(tep.get_last_error_position() >= 19);
        // a successful parse clears it
        CHECK(tep.compile("STRLENPLUS(\"abc\")"));
        CHECK(tep.get_last_error_position() == te_parser::npos);
        }

    SECTION("Recovery after a failed parse")
        {
        CHECK(std::isnan(tep.evaluate("STRLENPLUS(\"abc")));
        CHECK_FALSE(tep.success());
        // the parser must still be usable
        CHECK(tep.evaluate("STRLENPLUS(\"abcd\")") == 4);
        CHECK(tep.success());
        }

    SECTION("What the function actually receives")
        {
        lastArgs.clear();
        CHECK(tep.evaluate("STRLENPLUS(\"abc\", 2, 3)") == 8);
        REQUIRE(lastArgs.size() == 3);
        REQUIRE(std::holds_alternative<std::string_view>(lastArgs[0]));
        CHECK(std::get<std::string_view>(lastArgs[0]) == "abc");
        REQUIRE(std::holds_alternative<te_type>(lastArgs[1]));
        CHECK(std::get<te_type>(lastArgs[1]) == 2);
        CHECK(std::get<te_type>(lastArgs[2]) == 3);

        // the view must point at the literal's own bytes, not a truncated
        // or over-long slice of the surrounding expression
        lastArgs.clear();
        CHECK(tep.evaluate("STRLENPLUS(\"a\\b/c\")") == 5);
        REQUIRE(lastArgs.size() == 1);
        CHECK(std::get<std::string_view>(lastArgs[0]) == "a\\b/c");

        lastArgs.clear();
        CHECK(tep.evaluate("STRLENPLUS(\"\")") == 0);
        REQUIRE(lastArgs.size() == 1);
        REQUIRE(std::holds_alternative<std::string_view>(lastArgs[0]));
        CHECK(std::get<std::string_view>(lastArgs[0]).empty());

        // and it stays valid for the life of the compiled expression.
        // strlive is not pure, so these re-evaluations really do call through.
        CHECK(tep.compile("STRLIVE(\"persistent\")"));
        lastArgs.clear();
        CHECK(tep.evaluate() == 10);
        REQUIRE(lastArgs.size() == 1);
        CHECK(std::get<std::string_view>(lastArgs[0]) == "persistent");
        lastArgs.clear();
        CHECK(tep.evaluate() == 10);
        REQUIRE(lastArgs.size() == 1);
        CHECK(std::get<std::string_view>(lastArgs[0]) == "persistent");
        }

    SECTION("Recompiling from the stored expression keeps literals intact")
        {
        // set_constant() recompiles from m_expression, which the literals point into
        tep.add_variable_or_function({ "k", static_cast<te_type>(1) });
        CHECK(tep.evaluate("STRLIVE(\"abcde\") + k") == 6);
        tep.set_constant("k", 10);
        lastArgs.clear();
        CHECK(tep.evaluate() == 15);
        REQUIRE(lastArgs.size() == 1);
        CHECK(std::get<std::string_view>(lastArgs[0]) == "abcde");
        }

    SECTION("Separator settings are respected")
        {
        te_parser euro;
        euro.set_decimal_separator(',');
        euro.set_list_separator(';');
        euro.set_variables_and_functions(
            { { "strlenplus", static_cast<te_arg_fun>(str_len_plus), TE_PURE } });
        // ',' decimal numbers are left out; they also need the C locale set
        CHECK(euro.evaluate("STRLENPLUS(\"abc\"; 2)") == 5);
        CHECK(euro.evaluate("STRLENPLUS(\"abc\"; 2; 3)") == 8);
        // a ',' inside a literal is neither a list nor a decimal separator
        CHECK(euro.evaluate("STRLENPLUS(\"a,b\")") == 3);
        CHECK(euro.evaluate("STRLENPLUS(\"1,5\")") == 3);
        }
    }

TEST_CASE("String arguments and comments", "[strings][comments]")
    {
    te_parser tep;
    tep.set_variables_and_functions(
        { { "strlenplus", static_cast<te_arg_fun>(str_len_plus), TE_PURE } });

    SECTION("Comment markers inside a literal survive")
        {
        CHECK(tep.evaluate("STRLENPLUS(\"http://example.com\")") == 18);
        CHECK(tep.get_expression() == "STRLENPLUS(\"http://example.com\")");
        CHECK(tep.evaluate("STRLENPLUS(\"//\")") == 2);
        CHECK(tep.evaluate("STRLENPLUS(\"/* not a comment */\")") == 19);
        CHECK(tep.evaluate("STRLENPLUS(\"/*\")") == 2);
        CHECK(tep.evaluate("STRLENPLUS(\"*/\")") == 2);
        // an unterminated /* inside a literal must not fail the compile
        CHECK(tep.success());
        }

    SECTION("Real comments still strip")
        {
        CHECK(tep.evaluate("STRLENPLUS(\"abc\") // trailing") == 3);
        CHECK(tep.evaluate("STRLENPLUS(/* inline */\"abc\")") == 3);
        CHECK(tep.evaluate("/* lead */ STRLENPLUS(\"abc\")") == 3);
        }

    SECTION("Comments around and between literals")
        {
        CHECK(tep.evaluate("STRLENPLUS(\"ab\" /* x */, 1)") == 3);
        CHECK(tep.evaluate("STRLENPLUS(\"a//b\") /* tail */") == 4);
        }
    }

TEST_CASE("String arguments and optimization", "[strings][optimize]")
    {
    SECTION("Pure functions fold literal arguments")
        {
        te_parser tep;
        tep.set_variables_and_functions(
            { { "strlenplus", static_cast<te_arg_fun>(str_len_plus), TE_PURE } });
        CHECK(tep.evaluate("STRLENPLUS(\"abcd\")") == 4);
        CHECK(tep.evaluate("STRLENPLUS(\"abcd\") + 1") == 5);
        }

    SECTION("Non-pure functions are re-evaluated")
        {
        te_parser tep;
        strCallCount = 0;
        tep.set_variables_and_functions(
            { { "counted", static_cast<te_arg_fun>(str_counted) } });
        CHECK(tep.compile("COUNTED(\"abc\")"));
        const auto afterCompile = strCallCount;
        CHECK(tep.evaluate() == 3);
        CHECK(tep.evaluate() == 3);
        // each evaluate() must call through, not read a folded constant
        CHECK(strCallCount == afterCompile + 2);
        }

    SECTION("A pure function of a variable is not folded away")
        {
        te_type x{ 2 };
        te_parser tep;
        tep.set_variables_and_functions({
            { "strlenplus", static_cast<te_arg_fun>(str_len_plus), TE_PURE },
            { "x", &x } });
        CHECK(tep.compile("STRLENPLUS(\"abc\", x)"));
        CHECK(tep.evaluate() == 5);
        x = 10;
        // if the call had been folded, this would still report 5
        CHECK(tep.evaluate() == 13);
        }
    }

TEST_CASE("String arguments and bookkeeping", "[strings][functions]")
    {
#ifndef TE_NO_BOOKKEEPING
    te_parser tep;
    tep.set_variables_and_functions({
        { "strlenplus", static_cast<te_arg_fun>(str_len_plus), TE_PURE },
        { "strpair", static_cast<te_arg_fun>(str_pair), TE_PURE } });

    CHECK(tep.evaluate("STRLENPLUS(\"abc\")") == 3);
    CHECK(tep.is_function_used("strlenplus"));
    CHECK_FALSE(tep.is_variable_used("strlenplus"));
    CHECK_FALSE(tep.is_function_used("strpair"));

    tep.remove_unused_variables_and_functions();
    CHECK(tep.evaluate("STRLENPLUS(\"abcd\")") == 4);
    CHECK(std::isnan(tep.evaluate("STRPAIR(\"a\", 1)")));
    CHECK_FALSE(tep.success());
#endif
    }

TEST_CASE("String arguments with a context object", "[strings][closure]")
    {
    te_expr_array teArray{ TE_DEFAULT };

    te_parser tep;
    tep.set_variables_and_functions({
        { "cellnamed", static_cast<te_arg_confun>(cell_named), TE_DEFAULT, &teArray },
        { "celloffset", static_cast<te_arg_confun>(cell_offset), TE_DEFAULT, &teArray } });

    SECTION("Context is delivered")
        {
        CHECK(tep.evaluate("CELLNAMED(\"first\")") == 5);
        CHECK(tep.evaluate("CELLNAMED(\"last\")") == 9);
        CHECK(std::isnan(tep.evaluate("CELLNAMED(\"middle\")")));
        CHECK(tep.success());
        }

    SECTION("Mixed string and numeric arguments")
        {
        CHECK(tep.evaluate("CELLOFFSET(\"cell\", 0)") == 5);
        CHECK(tep.evaluate("CELLOFFSET(\"cell\", 4)") == 9);
        CHECK(tep.evaluate("CELLOFFSET(\"cell\", 2*1)") == 7);
        CHECK(std::isnan(tep.evaluate("CELLOFFSET(\"cell\", 99)")));
        CHECK(std::isnan(tep.evaluate("CELLOFFSET(\"nope\", 0)")));
        }

    SECTION("Wrong arity still returns cleanly")
        {
        CHECK(tep.compile("CELLNAMED(\"first\", 2)"));
        CHECK(std::isnan(tep.evaluate()));
        CHECK(tep.compile("CELLNAMED()"));
        CHECK(std::isnan(tep.evaluate()));
        }

    SECTION("Combined with numeric operators")
        {
        CHECK(tep.evaluate("CELLNAMED(\"first\") + CELLNAMED(\"last\")") == 14);
        CHECK(tep.evaluate("MAX(CELLNAMED(\"first\"), CELLNAMED(\"last\"))") == 9);
        }

    SECTION("Parse failure with a context function")
        {
        CHECK(std::isnan(tep.evaluate("CELLNAMED(\"first\"")));
        CHECK_FALSE(tep.success());
        CHECK(tep.evaluate("CELLNAMED(\"first\")") == 5);
        }
    }

TEST_CASE("Database lookup example", "[strings][usr]")
    {
    SECTION("Free function")
        {
        te_parser tep;
        tep.set_variables_and_functions(
            { { "dbquery", static_cast<te_arg_fun>(db_query), TE_PURE } });

        CHECK_THAT(tep.evaluate("DBQUERY(\"/Equipment/Temp\")"),
                   Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(21.5)));
        CHECK_THAT(tep.evaluate("DBQUERY(\"/Equipment/Pressure\")"),
                   Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(101.3)));
        CHECK(tep.evaluate("DBQUERY(\"/Equipment/Humidity\")") == 44);

        // used in a real formula
        CHECK_THAT(tep.evaluate("DBQUERY(\"/Equipment/Temp\") * 9 / 5 + 32"),
                   Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(70.7)));
        CHECK(tep.evaluate("IF(DBQUERY(\"/Equipment/Temp\") > 20, 1, 0)") == 1);
        CHECK_THAT(tep.evaluate("(DBQUERY(\"/Equipment/Temp\") + DBQUERY(\"/Equipment/Humidity\")) / 2"),
                   Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(32.75)));

        // unknown key
        CHECK(std::isnan(tep.evaluate("DBQUERY(\"/Equipment/Nope\")")));
        CHECK(tep.success());
        // optional default for a missing key
        CHECK(tep.evaluate("DBQUERY(\"/Equipment/Nope\", 0)") == 0);
        CHECK(tep.evaluate("DBQUERY(\"/Equipment/Nope\", -1)") == -1);
        CHECK_THAT(tep.evaluate("DBQUERY(\"/Equipment/Temp\", 0)"),
                   Catch::Matchers::WithinRel(WITHIN_TYPE_CAST(21.5)));
        }

    SECTION("Bound to a client object")
        {
        te_database db{ TE_DEFAULT };
        te_parser tep;
        tep.set_variables_and_functions(
            { { "query", static_cast<te_arg_confun>(query_db), TE_DEFAULT, &db } });

        CHECK(tep.evaluate("QUERY(\"voltage\")") == 240);
        CHECK(tep.evaluate("QUERY(\"current\")") == 13);
        CHECK(tep.evaluate("QUERY(\"voltage\") * QUERY(\"current\")") == 3120);
        CHECK(std::isnan(tep.evaluate("QUERY(\"missing\")")));

        // the object really was consulted each time: 1 + 1 + 2 + 1
        CHECK(db.m_readCount == 5);
        }
    }



TEST_CASE("Benchmarks", "[!benchmark]")
    {
    te_type benchmarkVar{ 9 };
    te_parser tep;
    tep.set_variables_and_functions({ {"a", &benchmarkVar} });

    BENCHMARK("a+5 Compile")
        { return tep.compile("a+5"); };
    tep.compile("a+5");
    BENCHMARK("a+5 Compiled")
        { return tep.evaluate(); };
    BENCHMARK("a+5 Native")
        { return bench_a5(benchmarkVar); };

    BENCHMARK("5+a+5 Compile")
        { return tep.compile("5+a+5"); };
    tep.compile("5+a+5");
    BENCHMARK("5+a+5 Compiled")
        { return tep.evaluate(); };
    BENCHMARK("5+a+5 Native")
        { return bench_a55(benchmarkVar); };

    BENCHMARK("abs(a+5) Compile")
        { return tep.compile("abs(a+5)"); };
    tep.compile("abs(a+5)");
    BENCHMARK("abs(a+5) Compiled")
        { return tep.evaluate(); };
    BENCHMARK("abs(a+5) Native")
        { return bench_a5abs(benchmarkVar); };

    BENCHMARK("sqrt(a^1.5+a^2.5) Compile")
        { return tep.compile("sqrt(a^1.5+a^2.5)"); };
    tep.compile("sqrt(a^1.5+a^2.5)");
    BENCHMARK("sqrt(a^1.5+a^2.5) Compiled")
        { return tep.evaluate(); };
    BENCHMARK("sqrt(a^1.5+a^2.5) Native")
        { return bench_as(benchmarkVar); };

    BENCHMARK("a+(5*2) Compile")
        { return tep.compile("a+(5*2)"); };
    tep.compile("a+(5*2)");
    BENCHMARK("a+(5*2) Compiled")
        { return tep.evaluate(); };
    BENCHMARK("a+(5*2) Native")
        { return bench_a10(benchmarkVar); };

    BENCHMARK("(a+5)*2 Compile")
        { return tep.compile("(a+5)*2"); };
    tep.compile("(a+5)*2");
    BENCHMARK("(a+5)*2 Compiled")
        { return tep.evaluate(); };
    BENCHMARK("(a+5)*2 Native")
        { return bench_a52(benchmarkVar); };

    BENCHMARK("(1/(a+1)+2/(a+2)+3/(a+3)) Compile")
        { return tep.compile("(1/(a+1)+2/(a+2)+3/(a+3))"); };
    tep.compile("(1/(a+1)+2/(a+2)+3/(a+3))");
    BENCHMARK("(1/(a+1)+2/(a+2)+3/(a+3)) Compiled")
        { return tep.evaluate(); };
    BENCHMARK("(1/(a+1)+2/(a+2)+3/(a+3)) Native")
        { return bench_al(benchmarkVar); };
    }
}

// clang-format on
// NOLINTEND
