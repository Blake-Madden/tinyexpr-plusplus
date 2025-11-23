#############################################################################
# Name:        CMakeListst.txt
# Purpose:     Demo for tinyexpr++
# Author:      Blake Madden
# Created:     2023-05-30
# Copyright:   (c) 2024 Blake Madden
# Licence:     3-Clause BSD licence
#############################################################################

project(TEDemo)

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${CMAKE_PROJECT_NAME} tinyexpr.cpp tedemo.cpp)
