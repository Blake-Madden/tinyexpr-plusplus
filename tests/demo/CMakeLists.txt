#############################################################################
# Name:        CMakeListst.txt
# Purpose:     Demo for tinyexpr++
# Author:      Blake Madden
# Created:     2023-05-30
# Copyright:   (c) 2023 Blake Madden
# Licence:     3-Clause BSD licence
#############################################################################

PROJECT(TEDemo)

CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ../../tinyexpr.cpp tedemo.cpp)

