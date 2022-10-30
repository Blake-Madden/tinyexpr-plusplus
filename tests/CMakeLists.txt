#############################################################################
# Name:        CMakeListst.txt
# Purpose:     Unit test runner for tinyexpr++
# Author:      Blake Madden
# Created:     2022-10-29
# Copyright:   (c) 2022 Blake Madden
# Licence:     3-Clause BSD licence
#############################################################################

PROJECT(TETestRunner)

CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

# place Catch2 at the same folder level as this repo if it isn't installed
# (you will need to do this on Windows or macOS or if version 3 of Catch2 isn't installed)
GET_FILENAME_COMPONENT(_fullpath "${_dir}" REALPATH)
IF(EXISTS "${_fullpath}" AND EXISTS "${_fullpath}/../../Catch2")
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/../../Catch2 ${CMAKE_CURRENT_BINARY_DIR}/Catch2)
ELSE()
    # ...otherwise, see if it is installed
    FIND_PACKAGE(Catch2 3 REQUIRED)
ENDIF()

ADD_EXECUTABLE(TETestRunner ../tinyexpr.cpp tetests.cpp)
TARGET_LINK_LIBRARIES(TETestRunner PRIVATE Catch2::Catch2WithMain)

# load the test cases into the runner
INCLUDE(CTest)
INCLUDE(Catch)
CATCH_DISCOVER_TESTS(TETestRunner)