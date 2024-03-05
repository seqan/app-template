# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.16)

add_executable ("hibf_tutorial" main.cpp build.cpp count.cpp search.cpp)
target_link_libraries ("hibf_tutorial" PRIVATE "${PROJECT_NAME}_interface")
