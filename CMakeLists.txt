# SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.16)

# Define the application name and version.
project (app-template LANGUAGES CXX VERSION 1.0.0)

## Provides possible dependencies
include (cmake/CPM.cmake)

CPMAddPackage("gh:SGSSGene/CMakeUseCCache@1.0.0")
require_ccache()

CPMAddPackage("gh:seqan/hibf#2075a68d10f571399b5ff885f0b4cb2c94845601")
CPMAddPackage("gh:seqan/sharg-parser#3e96d37387125bd876ace3fdd11a20039ed0d21c")
CPMAddPackage("gh:seqan/seqan3#ee718d0d3bbf07a894b5208d37ddf71ba5a5bf44")
CPMAddPackage("gh:SGSSGene/fmindex-collection#432d00176ef872e55fc58d6506a48030b8a32239")


# Add all translation units (cpp files) of your program
add_executable (fmindex-tool
    src/main.cpp
    src/index.cpp
    src/search.cpp
)
target_link_libraries (fmindex-tool PRIVATE
    seqan3::seqan3
    seqan::hibf
    sharg::sharg
    fmindex-collection::fmindex-collection
)
