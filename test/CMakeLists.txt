# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.25)

include (test/config)
include (data/datasources.cmake)

add_app_test (api_fastq_coversion_test.cpp)
add_app_test (cli_fastq_coversion_test.cpp)

message (STATUS "You can run `make check` to build and run tests.")
