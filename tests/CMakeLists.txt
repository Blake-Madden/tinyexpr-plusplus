#############################################################################
# Name:        CMakeListst.txt
# Purpose:     Unit test runner for tinyexpr++
# Author:      Blake Madden
# Created:     2022-10-29
# Copyright:   (c) 2024 Blake Madden
# Licence:     3-Clause BSD licence
#############################################################################

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Options:
# - USE_ADDRESS_SANITIZE to use ASAN
# - USE_CLANG_TIDY to run clang-tidy
# - TE_FLOAT, TE_LONG_DOUBLE to use float or long double as the internal datatype
# - TE_POW_FROM_RIGHT to enable parsing exponents from the right
# - TE_BITWISE_OPERATORS to parse ^, &, and | as bitwise operators

project(TETestRunner)

# https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
if(CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
    include(CodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_lcov(NAME ${CMAKE_PROJECT_NAME}_coverage
                                   EXECUTABLE ${CMAKE_PROJECT_NAME}
                                   DEPENDENCIES ${CMAKE_PROJECT_NAME})
endif()

find_program(CLANG_TIDY_COMMAND
      NAMES
         clang-tidy
      NO_CACHE)
if(CLANG_TIDY_COMMAND AND USE_CLANG_TIDY)
    if(MSVC)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_COMMAND} --extra-arg=/EHsc)
    else()
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_COMMAND})
    endif()
endif()

if(TE_FLOAT)
    message(STATUS "Datatype: float")
    add_definitions(-DTE_FLOAT)
elseif(TE_LONG_DOUBLE)
    message(STATUS "Datatype: long double")
    add_definitions(-DTE_LONG_DOUBLE)
else()
    message(STATUS "Datatype: double")
endif(TE_FLOAT)

if(TE_POW_FROM_RIGHT)
    message(STATUS "Power from right: enabled")
    add_definitions(-DTE_POW_FROM_RIGHT)
else()
    message(STATUS "Power from right: disabled")
endif(TE_POW_FROM_RIGHT)

if(TE_BITWISE_OPERATORS)
    message(STATUS "Extended bitwise operators: enabled")
    add_definitions(-DTE_BITWISE_OPERATORS)
else()
    message(STATUS "Extended bitwise operators: disabled")
endif(TE_BITWISE_OPERATORS)

if(TE_BRACKETS_AS_PARENS)
    message(STATUS "[] being treats as (): enabled")
    add_definitions(-DTE_BRACKETS_AS_PARENS)
else()
    message(STATUS "[] being treats as (): disabled")
endif(TE_BRACKETS_AS_PARENS)

# place Catch2 at the same folder level as this repo if it isn't installed
# (you will need to do this on Windows or macOS or if version 3 of Catch2 isn't installed)
get_filename_component(_fullpath "${_dir}" REALPATH)
if(EXISTS "${_fullpath}" AND EXISTS "${_fullpath}/../../Catch2")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Catch2 ${CMAKE_CURRENT_BINARY_DIR}/Catch2)
else()
    # ...otherwise, see if it is installed
    find_package(Catch2 3 REQUIRED)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${CMAKE_PROJECT_NAME} ../tinyexpr.cpp tetests.cpp testingmain.cpp)
if(MSVC)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION
                               $<$<CONFIG:Release>:NDEBUG>)
    if(USE_ADDRESS_SANITIZE)
        target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC /Zc:__cplusplus /MP /W3 /WX /wd4554
                           $<$<CONFIG:Debug>:/Od /fsanitize=address> $<$<CONFIG:Release>:/O2>)
    else()
        target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC /Zc:__cplusplus /MP /W3 /WX /wd4554
                           $<$<CONFIG:Debug>:/Od> $<$<CONFIG:Release>:/O2>)
    endif()
endif()
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Catch2::Catch2)

# load the test cases into the runner
include(CTest)
include(Catch)
catch_discover_tests(${CMAKE_PROJECT_NAME})
