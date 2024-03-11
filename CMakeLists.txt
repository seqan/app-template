# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.25)

# Define the application name and version.
project (app-template VERSION 1.0.0)

# Allow to include CMake scripts from the app-template.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Use ccache.
include (ccache)

# Specify the directories where to store the built archives, libraries and executables
include (output_directories)

# Add packages.
include (CPM)
CPMUsePackageLock (${CMAKE_CURRENT_LIST_DIR}/cmake/package-lock.cmake)

CPMGetPackage (hibf)
CPMGetPackage (sharg)
CPMGetPackage (seqan3)

add_subdirectory (src)

## TEST
option (${PROJECT_NAME}_TEST "Enable testing for ${PROJECT_NAME}." ON)

if (${PROJECT_NAME}_TEST)
    add_subdirectory (test EXCLUDE_FROM_ALL)
endif ()
