# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.16)

## CUSTOMISE

# Define the application name and version.
project (app-template VERSION 1.0.0)

# Needed for CPM
find_package (Git REQUIRED)

## BUILD

# Make Release default build type
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE
         Release
         CACHE STRING "Choose the type of build, options are: Debug Release Coverage RelWithDebInfo MinSizeRel." FORCE
    )
endif ()

# Specify the directories where to store the built archives, libraries and executables
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Messages
string (ASCII 27 Esc)
set (FontBold "${Esc}[1m")
set (FontReset "${Esc}[m")

# Allow to include CMake scripts from the app-template.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Use ccache.
include (ccache)
require_ccache ()

# Add packages.
set (CPM_INDENT "  CMake Package Manager CPM: ")
include (CPM)
include (CPMGetSystemPackage)
CPMUsePackageLock (${CMAKE_CURRENT_LIST_DIR}/cmake/package-lock.cmake)

CPMGetSystemPackage (hibf)
CPMGetSystemPackage (sharg)
CPMGetSystemPackage (seqan3)

# Add the application.
add_subdirectory (src)
message (STATUS "${FontBold}You can run `make` to build the application.${FontReset}")

## TEST
option (${PROJECT_NAME}_TEST "Enable testing for ${PROJECT_NAME}." ON)
if (${PROJECT_NAME}_TEST)
    list (APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure") # Must be before `enable_testing ()`.
    enable_testing ()
    add_subdirectory (test EXCLUDE_FROM_ALL)
endif ()
