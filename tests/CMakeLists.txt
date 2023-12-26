#############################################################################
# Name:        CMakeListst.txt
# Purpose:     Unit test runner for tinyexpr++
# Author:      Blake Madden
# Created:     2022-10-29
# Copyright:   (c) 2023 Blake Madden
# Licence:     3-Clause BSD licence
#############################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

PROJECT(TETestRunner)

# https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
IF(CMAKE_COMPILER_IS_GNUCXX)
    LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
    INCLUDE(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    SETUP_TARGET_FOR_COVERAGE_LCOV(NAME ${CMAKE_PROJECT_NAME}_coverage
                                   EXECUTABLE ${CMAKE_PROJECT_NAME}
                                   DEPENDENCIES ${CMAKE_PROJECT_NAME})
ENDIF()

find_program(CLANG_TIDY_COMMAND
      NAMES
         clang-tidy
      NO_CACHE)
if(CLANG_TIDY_COMMAND AND MSVC)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_COMMAND} --extra-arg=/EHsc)
endif()

IF(TE_FLOAT)
    ADD_DEFINITIONS(-DTE_FLOAT)
ENDIF(TE_FLOAT)
IF(TE_POW_FROM_RIGHT)
    ADD_DEFINITIONS(-DTE_POW_FROM_RIGHT)
ENDIF(TE_POW_FROM_RIGHT)

# place Catch2 at the same folder level as this repo if it isn't installed
# (you will need to do this on Windows or macOS or if version 3 of Catch2 isn't installed)
GET_FILENAME_COMPONENT(_fullpath "${_dir}" REALPATH)
IF(EXISTS "${_fullpath}" AND EXISTS "${_fullpath}/../../Catch2")
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/../../Catch2 ${CMAKE_CURRENT_BINARY_DIR}/Catch2)
ELSE()
    # ...otherwise, see if it is installed
    FIND_PACKAGE(Catch2 3 REQUIRED)
ENDIF()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ../tinyexpr.cpp tetests.cpp testingmain.cpp)
IF(MSVC)
    TARGET_COMPILE_DEFINITIONS(${CMAKE_PROJECT_NAME} PUBLIC
                               $<$<CONFIG:Release>:NDEBUG>)
    TARGET_COMPILE_OPTIONS(${CMAKE_PROJECT_NAME} PUBLIC /MP /W3 /WX /wd4554
                           $<$<CONFIG:Debug>:/Od> $<$<CONFIG:Release>:/O2>)
ENDIF()
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} PRIVATE Catch2::Catch2)

# load the test cases into the runner
INCLUDE(CTest)
INCLUDE(Catch)
CATCH_DISCOVER_TESTS(${CMAKE_PROJECT_NAME})
